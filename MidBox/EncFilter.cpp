#include "EncFilter.h"

#include <string>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <map>

#include "../Caravel/ShmCtl.h"
#include "../Caravel/Digest.h"
#include "../Caravel/PRF.h"
#include "../Caravel/TimeDiff.h"

#include "MidBox.h"

using namespace std;
using namespace caravel;

EncFilter::EncFilter(void)
{
    m_pPosTemp = NULL;
    srand(0);
}


EncFilter::~EncFilter(void)
{
    if(m_pPosTemp != NULL)
    {
        delete [] m_pPosTemp;
    }

}

int EncFilter::InitIndex(string strMstKey, key_t kShm, uint32_t uiPairNum, bool bAttach)
{

    //compute the size
    uint32_t uiRealNum = uiPairNum * DEF_PADDING_COUNT / DEF_INDEX_LOAD + 1;
    m_uiNum[IDX_FIRST] = m_uiNum[IDX_SECOND] = (uiRealNum / DEF_ENTITY_NUM + 1) / NR_IDX_LINE + 1;
    m_uiSize = DEF_BLOCK_NUM * NR_BLOCK * NR_IDX_LINE;

    //init the shm
    if (!ShmCtl::GetShm((void**)&m_pAll, kShm, m_uiSize))
    {
        return RET_INIT_ERRSHM;
    }

    if(!bAttach)
    {
        memset(m_pAll, 0, m_uiSize);
    }

    m_pLine[IDX_FIRST] = (Block*)m_pAll;
    m_pLine[IDX_SECOND] = m_pLine[IDX_FIRST] + DEF_BLOCK_NUM;

    if(!bAttach)
    {

        //Init the temp memory
        if(NULL != m_pPosTemp)
        {
            delete m_pPosTemp;
        }
        size_t szLen = DEF_BLOCK_NUM * DEF_ENTITY_NUM * NR_IDX_LINE;
        m_pPosTemp = new uint32_t[szLen];
        memset(m_pPosTemp, 0, szLen * sizeof(uint32_t));

    }

    //Init the Keys
    
    for(uint32_t uiCur = 0; uiCur < NR_KEY_TYPE; uiCur++)
    {
        string sKey = strMstKey + AppendInt('K', uiCur);
        Digest::Sha256(sKey, m_arKey[uiCur], NR_KEY_CHAR);
    }

    return RET_INIT_SUCCESS;

}

bool EncFilter::m_Insert(Entity *pEntity, uint32_t uiLine, uint32_t uiPos, uint32_t uiOffset, uint32_t uiKickTimes)
{
    //Check the kcik out times
    if(uiKickTimes == 0)
    {
        return false;
    }

    uint32_t arLine[NR_INS_LINE];
    //the victim 's line
    arLine[INS_SAME_LINE] = uiLine;
    arLine[INS_DIFF_LINE] = (uiLine + 1) % NR_IDX_LINE;

    uint32_t arPos[NR_INS_LINE];
    arPos[arLine[INS_SAME_LINE]] = uiPos;
    arPos[arLine[INS_DIFF_LINE]] = m_pPosTemp[(DEF_BLOCK_NUM * uiLine + uiPos) * DEF_ENTITY_NUM + uiOffset];

    Block *arpBlock[NR_INS_LINE];
    arpBlock[arLine[INS_SAME_LINE]] = m_pLine[arLine[INS_SAME_LINE]] + uiPos;
    arpBlock[arLine[INS_DIFF_LINE]] = m_pLine[arLine[INS_DIFF_LINE]] + arPos[arLine[INS_DIFF_LINE]];
    uint32_t uiTmpOffset;
    Entity *pNextEntity = m_GetEmpty(arpBlock[arLine[INS_DIFF_LINE]], uiTmpOffset);
    if(pNextEntity != NULL)
    {
        //It has a empty place. So it can be here.
        m_pPosTemp[(DEF_BLOCK_NUM * arLine[INS_DIFF_LINE] + arPos[arLine[INS_DIFF_LINE]]) * DEF_ENTITY_NUM + uiTmpOffset] = uiPos;
        
        memcpy(pNextEntity, pEntity, NR_ENTITY);
        
        return true;
    }
    //still full, prepare to kick out again
    uint32_t uiRand;
    //0 means same line as victim. 1 means the different line as victim
    uint32_t uiKickSameLine;
    uint32_t uiKickOffset;
    //select a victim
    do
    {
        uiRand = rand();
        uiKickSameLine = uiRand % NR_INS_LINE;
        uiKickOffset = uiRand % DEF_ENTITY_NUM;
    } 
    while (uiKickOffset == uiOffset && INS_SAME_LINE == uiKickSameLine);
    Entity *pKickEntity = arpBlock[arLine[uiKickSameLine]]->arEntity + uiKickOffset;
    //Do the kick out
    if(!m_Insert(pKickEntity, arLine[uiKickSameLine], arPos[arLine[uiKickSameLine]], uiKickOffset, uiKickTimes - 1))
    {
        //ERROR on m_Insert; probably reach the max kick out times.
        return false;
    }

    //set the temp
    m_pPosTemp[(DEF_BLOCK_NUM * arLine[uiKickSameLine] + arPos[arLine[uiKickSameLine]]) * DEF_ENTITY_NUM + uiKickOffset] = arPos[(arLine[uiKickSameLine] + 1) % NR_INS_LINE];

    memcpy(pKickEntity, pEntity, NR_ENTITY);

    return true;

}

uint32_t EncFilter::Insert(Pair *pPair, uint32_t uiPairNum)
{
    //For the rule count
    typedef struct{
        uint32_t uiCur; //Current the Counter
        uint32_t uiAll; //The Max Counter
    }RuleCount;
    map<string, RuleCount> mapRuleCount;

    for(uint32_t uiCur = 0; uiCur < uiPairNum; uiCur++)
    {
        Pair *p = pPair + uiCur;

        //PRF with the RuleID
        char szBuf[NR_KEY_CHAR];
        PRF::Sha256(m_arKey[KEY_PRF_RULEID], NR_KEY_CHAR, (char*)&p->uiRuleID, sizeof(p->uiRuleID), szBuf, NR_KEY_CHAR);
        p->uiRuleID = *(uint32_t*)szBuf;

        mapRuleCount[p->strkey].uiAll++;
        mapRuleCount[p->strkey].uiCur = 0;
    }

    //Generate Trapdoor and Insert into Index
    Trapdoor trapdoor;
    QueryKey queryKey;
    for(uint32_t uiCur = 0; uiCur < uiPairNum; uiCur++)
    {
        Pair *p = pPair + uiCur;
        RuleCount ruleCount = mapRuleCount[p->strkey];

        for(uint32_t uiP = 0; uiP < DEF_PADDING_COUNT; uiP++)
        {

            string sKey = p->strkey + AppendInt('P', uiP);

            PRF::Sha256(m_arKey[KEY_TYPE_TRAPDOOR], NR_KEY_CHAR, (char*)sKey.c_str(), sKey.length(), queryKey.pTd, NR_TRAPDOOR_CHAR);
            PRF::Sha256(m_arKey[KEY_TYPE_MASK], NR_KEY_CHAR, (char*)sKey.c_str(), sKey.length(), queryKey.pMask, NR_TRAPDOOR_CHAR);

            BuildTrapdoor(&trapdoor, &queryKey, m_arKey, ruleCount.uiCur);

            uint32_t uiLine;
            Entity *pEntity = Insert(trapdoor, uiLine);

            if(pEntity == NULL)
            {
                cout<<"Get the Max Kickout !"<<endl;
                cout<<"uiCur = "<<uiCur<<endl;
                return 0;
            }

            pEntity->uiAction = p->uiAction; 
            pEntity->uiRuleID = p->uiRuleID;
            pEntity->uiSolidID = p->uiRuleID;
            pEntity->uiFlag = (ruleCount.uiCur == ruleCount.uiAll - 1) ? ENTITY_FLAG_END : ENTITY_FLAG_NEXT;

            BinaryXor((char*)pEntity, (char*)pEntity, trapdoor.arMask[uiLine], NR_TRAPDOOR_CHAR);

        }

        
        
        ruleCount.uiCur++;
        mapRuleCount[p->strkey] = ruleCount;
    }

    return 0;
}

Entity *EncFilter::Insert(Trapdoor &trapdoor, uint32_t &uiRetLine)
{
    
    //Compute the first POSITION
    uint32_t arPos[NR_IDX_LINE];
    arPos[IDX_FIRST] = m_GetPos(trapdoor.arTd[IDX_FIRST], IDX_FIRST);

    Block *arpBlock[NR_IDX_LINE];
    arpBlock[IDX_FIRST] = m_pLine[IDX_FIRST] + arPos[IDX_FIRST];

    Entity *arpEntity[NR_IDX_LINE];
    uint32_t uiOffset;
    arpEntity[IDX_FIRST] = m_GetEmpty(arpBlock[IDX_FIRST], uiOffset);

    if(arpEntity[IDX_FIRST] != NULL)
    {
        //Cache the Second Position
        m_pPosTemp[arPos[IDX_FIRST] * DEF_ENTITY_NUM + uiOffset] = m_GetPos(trapdoor.arTd[IDX_SECOND], IDX_SECOND);
        uiRetLine = IDX_FIRST;
        return arpEntity[IDX_FIRST];
    }
    //First is Full Check The Second
    arPos[IDX_SECOND] = m_GetPos(trapdoor.arTd[IDX_SECOND], IDX_SECOND);
    arpBlock[IDX_SECOND] = m_pLine[IDX_SECOND] + arPos[IDX_SECOND];
    arpEntity[IDX_SECOND] = m_GetEmpty(arpBlock[IDX_SECOND], uiOffset);
    if(arpEntity[IDX_SECOND] != NULL)
    {
        //Cache the First Position
        m_pPosTemp[(DEF_BLOCK_NUM + arPos[IDX_SECOND]) * DEF_ENTITY_NUM + uiOffset] = arPos[IDX_FIRST];
        uiRetLine = IDX_SECOND;
        return arpEntity[IDX_SECOND];
    }
    //All is Full, prepare to kick out
    uint32_t uiRand = rand();
    uint32_t uiLine = uiRand % NR_IDX_LINE;
    uiOffset = uiRand % DEF_ENTITY_NUM;
    Entity *pEntity = arpBlock[uiLine]->arEntity + uiOffset;
    if(!m_Insert(pEntity, uiLine, arPos[uiLine], uiOffset, DEF_MAX_KICKOUT))
    {
        //fail kick out
        return NULL;
    }
    //success kick out
    m_pPosTemp[(DEF_BLOCK_NUM * uiLine + arPos[uiLine]) * DEF_ENTITY_NUM + uiOffset] = arPos[(uiLine + 1) % NR_IDX_LINE];
    uiRetLine = uiLine;
    return pEntity;
}

void EncFilter::Query(QueryKey *pQueryKey, uint32_t uiNum)
{
    m_mapShareAction.clear();

    for(uint32_t uiCur = 0; uiCur < uiNum; uiCur++)
    {
        QueryKey *p = pQueryKey + uiCur;

        uint32_t uiC = 0;
        Trapdoor trapdoor;
        uint32_t uiAction = 0;

        do
        {
            BuildTrapdoor(&trapdoor, p, m_arKey, uiC++);
        }
        while(Query(trapdoor, uiAction));

        if(uiAction != 0)
        {
            cout<<"Action Hit "<<uiAction<<endl;
        }

    }

    //cout<<"Map.Size = "<<m_mapShareAction.size()<<endl;

}

bool EncFilter::Query(Trapdoor &trapdoor, uint32_t &uiAction)
{
    //Check the first line
    uint32_t uiPos = m_GetPos(trapdoor.arTd[IDX_FIRST], IDX_FIRST);

    Block *pBlock;
    pBlock = m_pLine[IDX_FIRST] + uiPos;

    Entity *pEntity;
    Entity entity;

    for(uint32_t uiCur = 0; uiCur < DEF_ENTITY_NUM; uiCur++)
    {
        pEntity = pBlock->arEntity + uiCur;
        //XOR
        BinaryXor((char*)&entity, (char*)pEntity, trapdoor.arMask[IDX_FIRST], NR_TRAPDOOR_CHAR);

        //check the flag
        if(entity.uiFlag == ENTITY_FLAG_NEXT || entity.uiFlag == ENTITY_FLAG_END)
        {
            if(m_mapShareAction.find(entity.uiRuleID) == m_mapShareAction.end())
            {
                m_mapShareAction[entity.uiRuleID] = entity.uiAction;
            }
            else
            {
                m_mapShareAction[entity.uiRuleID] ^= entity.uiAction;
            }

            if(m_mapShareAction[entity.uiRuleID] < NR_ENUM_ACTION)
            {
                uiAction = m_mapShareAction[entity.uiRuleID];
            }

            return entity.uiFlag == ENTITY_FLAG_NEXT;
        }

    }

    //Check the second line
    uiPos = m_GetPos(trapdoor.arTd[IDX_SECOND], IDX_SECOND);
    pBlock = m_pLine[IDX_SECOND] + uiPos;

    for(uint32_t uiCur = 0; uiCur < DEF_ENTITY_NUM; uiCur++)
    {
        pEntity = pBlock->arEntity + uiCur;
        //XOR
        BinaryXor((char*)&entity, (char*)pEntity, trapdoor.arMask[IDX_SECOND], NR_TRAPDOOR_CHAR);

        //check the flag
        if(entity.uiFlag == ENTITY_FLAG_NEXT || entity.uiFlag == ENTITY_FLAG_END)
        {
            if(m_mapShareAction.find(entity.uiRuleID) == m_mapShareAction.end())
            {
                m_mapShareAction[entity.uiRuleID] = entity.uiAction;
            }
            else
            {
                m_mapShareAction[entity.uiRuleID] ^= entity.uiAction;
            }

            if(m_mapShareAction[entity.uiRuleID] < NR_ENUM_ACTION)
            {
                uiAction = m_mapShareAction[entity.uiRuleID];
            }

            return entity.uiFlag == ENTITY_FLAG_NEXT;
        }
    }

    return false;

}



Entity *EncFilter::m_GetEmpty(Block *pBlock, uint32_t &uiOffset)
{
    for(uint32_t uiCur = 0; uiCur < DEF_ENTITY_NUM; uiCur++)
    {
        if(pBlock->arEntity[uiCur].uiRuleID == 0)
        {
            //It's empty
            uiOffset = uiCur;
            return pBlock->arEntity + uiCur;
        }
    }

    return NULL;

}

uint32_t EncFilter::m_GetPos(char *p, int iLine)
{
    return (U32(p, 0) ^ U32(p, 4) ^ U32(p, 8) ^ U32(p, 12)) % DEF_BLOCK_NUM;
}



