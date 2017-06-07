#ifndef __RULE_PAIRS_H__
#define __RULE_PAIRS_H__

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdint.h>

using namespace std;

#define NR_Pair sizeof(Pair)

typedef struct stShareMask
{
    int iCurNum;
    uint32_t uiMask;
}ShareMask;

typedef struct stPair
{
	string strkey;
	uint32_t uiAction;
	uint32_t uiRuleID;
	int iOffset;
	int iOffsetCount;
	int iField;
    int iConNum;
}Pair;


class RulePairs
{
public:
	RulePairs(void);
	~RulePairs(void);

	uint32_t Init(string sPath);


	Pair *GetPairs();


private:

	Pair *m_pPair;

};




#endif

