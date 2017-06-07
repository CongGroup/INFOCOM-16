#include "MidBox.h"
#include <stdint.h>
#include <string>
#include <string.h>

#include "../Caravel/PRF.h"
#include "../Caravel/Digest.h"

using namespace std;
using namespace caravel;

void BinaryXor(char *p, char *pSrc, char *pXor, uint32_t uiLen)
{
    for(uint32_t uiCur = 0; uiCur < uiLen; uiCur++)
    {
        p[uiCur] = pSrc[uiCur] ^ pXor[uiCur];
    }
}


void BuildTrapdoor(Trapdoor *pTrapdoor, QueryKey *pQuery, char arKey[NR_KEY_TYPE][NR_KEY_CHAR], uint32_t uiC)
{
    char szBuf[NR_TRAPDOOR_CHAR + sizeof(uiC)];
    
    //Build trapdoor
    memcpy(szBuf, pQuery->pTd, NR_TRAPDOOR_CHAR);
    
    //First Line
    *(uint32_t*)(szBuf + NR_TRAPDOOR_CHAR) = uiC;
    PRF::Sha256(arKey[KEY_TYPE_TRAPDOOR], NR_KEY_CHAR, szBuf, sizeof(szBuf), pTrapdoor->arTd[IDX_FIRST], NR_TRAPDOOR_CHAR);

    //Second Line
    *(uint32_t*)(szBuf + NR_TRAPDOOR_CHAR) = uiC + DEF_SECONDLINE_FLAG;
    PRF::Sha256(arKey[KEY_TYPE_TRAPDOOR], NR_KEY_CHAR, szBuf, sizeof(szBuf), pTrapdoor->arTd[IDX_SECOND], NR_TRAPDOOR_CHAR);

    //Build mask
    memcpy(szBuf, pQuery->pMask, NR_TRAPDOOR_CHAR);

    //First Line
    *(uint32_t*)(szBuf + NR_TRAPDOOR_CHAR) = uiC;
    PRF::Sha256(arKey[KEY_TYPE_MASK], NR_KEY_CHAR, szBuf, sizeof(szBuf), pTrapdoor->arMask[IDX_FIRST], NR_TRAPDOOR_CHAR);

    //Second Line
    *(uint32_t*)(szBuf + NR_TRAPDOOR_CHAR) = uiC + DEF_SECONDLINE_FLAG;
    PRF::Sha256(arKey[KEY_TYPE_MASK], NR_KEY_CHAR, szBuf, sizeof(szBuf), pTrapdoor->arMask[IDX_SECOND], NR_TRAPDOOR_CHAR);

}


string AppendInt(char c, int i)
{
    char szBuf[20];
    string strRet;
    snprintf(szBuf, sizeof(szBuf), "%c%d", c, i);
    strRet.assign(szBuf);
    return strRet;
}


