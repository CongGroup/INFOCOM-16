#ifndef __ENC_FILTER_H__
#define __ENC_FILTER_H__

#include <stdio.h>
#include <stdint.h>
#include <map>
#include "RulePairs.h"
#include "MidBox.h"

using namespace std;

#define NR_ENTITY sizeof(Entity)
#define NR_BLOCK sizeof(Block)
#define NR_TRAPDOOR sizeof(Trapdoor)

//# of BLOCK per line
#define DEF_BLOCK_NUM m_uiNum[IDX_FIRST]

enum emInsertLine{
    INS_SAME_LINE = 0,
    INS_DIFF_LINE,
    NR_INS_LINE
};

enum emInitResp
{
    RET_INIT_SUCCESS = 0,
    RET_INIT_ERRSHM
};

typedef struct stEntity{
    uint32_t uiRuleID;  //PRF RuleID
    uint32_t uiAction;  //Action Enum
    uint32_t uiFlag; //Flag of Next Counter or NOT. And this flag will check SSE query entity
    uint32_t uiSolidID;   //for cross request rule
}Entity;

enum emEntityFlag
{
    ENTITY_FLAG_END = 0x123456,
    ENTITY_FLAG_NEXT = 0x456789,
    NR_ENTITY_FLAG
};

typedef struct stBlock{
    Entity arEntity[DEF_ENTITY_NUM];
}Block;


class EncFilter
{
public:
    EncFilter(void);
    ~EncFilter(void);

    int InitIndex(string strMstKey, key_t kShm, uint32_t uiPairNum, bool bAttach = false);

    Entity *Insert(Trapdoor &trapdoor, uint32_t &uiRetLine);

    bool Query(Trapdoor &trapdoor, uint32_t &uiAction);

    void Query(QueryKey *pQueryKey, uint32_t uiNum);

    uint32_t Insert(Pair *pPair, uint32_t uiPairNum);

private:

    map<uint32_t, uint32_t> m_mapShareAction;

    //the pointer of all memory
    char *m_pAll;

    //the pointer of each line
    Block *m_pLine[NR_IDX_LINE];

    //the # Block of each line
    uint32_t m_uiNum[NR_IDX_LINE];

    //the # of all entity
    uint32_t m_uiAllNum;

    //the size of all memory
    size_t m_uiSize;

    //a Temp memory for saving the position
    uint32_t *m_pPosTemp;

    //All the keys
    char m_arKey[NR_KEY_TYPE][NR_KEY_CHAR];


    //turn the trapdoor to Position
    inline uint32_t m_GetPos(char *p, int iLine);

    //check the block if has place
    inline Entity *m_GetEmpty(Block *pBlock, uint32_t &uiOffset);

    bool m_Insert(Entity *pEntity, uint32_t uiLine, uint32_t uiPos, uint32_t uiOffset, uint32_t uiKickTimes);

};




#endif
