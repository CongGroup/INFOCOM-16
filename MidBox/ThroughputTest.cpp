#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdint.h>

//getch
#include <termios.h>
#include <unistd.h>

#include "../Caravel/TimeDiff.h"

#include "EncFilter.h"
#include "RulePairs.h"
#include "RuleQuery.h"
#include "MidBox.h"

using namespace std;
using namespace caravel;

#define DEF_PARAMS_NUM 5

//ipcs -m|grep -v key|grep -v -|awk {'print "ipcrm -m " $2";"'}|grep -v " ;"|bash

int main(int argc, char **argv)
{

    if(argc != DEF_PARAMS_NUM)
    {
        cout<<"usage : ThroughputTest [SHMKEY] [Time to Query] [PairPath] [QueryPath]"<<endl;
        return -1;
    }

    int iKey;
    sscanf(argv[1], "%d", &iKey);
    key_t kShm = iKey;
    //cout<<"ShmKey = ["<<kShm<<"]"<<endl;

    uint32_t uiBeg;
    sscanf(argv[2], "%u", &uiBeg);
    //cout<<"BegTime = ["<<uiBeg<<"]"<<endl;

    string sPairPath(argv[3]);
    //cout<<"PairPath = ["<<sPairPath<<"]"<<endl;

    string sQueryPath(argv[4]);
    //cout<<"QueryPath = ["<<sQueryPath<<"]"<<endl;

    //Begin to Init the Index
    RulePairs rulePairs;
    uint32_t uiPairNum = rulePairs.Init(sPairPath);
    Pair *pPair = rulePairs.GetPairs();

    //cout<<"Finish process the RulePairs"<<endl;

    TimeDiff::DiffTimeInMicroSecond();

    EncFilter encFilter;
    EncFilter *pEncFilter = &encFilter;
    //Init the Index
    pEncFilter->InitIndex(DEF_MASTER_KEY ,kShm, uiPairNum);
    
    //Insert the Pairs into Index
    pEncFilter->Insert(pPair, uiPairNum);

    uint32_t uiTime = TimeDiff::DiffTimeInMicroSecond();
    //cout<<"Index Build Time"<<uiTime<<endl;

    RuleQuery ruleQuery;
    uint32_t uiNum = ruleQuery.ReadQueryFile(sQueryPath);

    //cout<<"Find ["<<uiNum<<"] Query Token"<<endl;

    QueryKey *pQueryKey = new QueryKey[uiNum];
    memset(pQueryKey, 0, sizeof(uiNum * sizeof(QueryKey)));

    ruleQuery.InitKey(DEF_MASTER_KEY);

    ruleQuery.GenQueryKey(pQueryKey);

    //cout<<"Finish GenQuery Key"<<endl;

    uint32_t uiCurTime;
    uint32_t uiBegTime = uiBeg;
    uint32_t uiEndTime = uiBegTime + 30;
    uint32_t uiNumPerConn = 30;

    uint32_t uiAllQueryNum = 0;

    while(true)
    {

        uiCurTime = time(NULL);

        if(uiCurTime < uiBegTime)
        {
            continue;
        }

        if(uiCurTime >= uiEndTime)
        {
            break;
        }

        pEncFilter->Query(pQueryKey, uiNumPerConn);

        //uiAllQueryNum += uiNumPerConn;
    
    }

    //cout<<uiAllQueryNum<<endl;

    uint32_t uiQueryTime = TimeDiff::DiffTimeInMicroSecond();
    //cout<<"For "<<uiNum<<" QueryKey Cost "<<uiQueryTime<<endl;

    delete [] pQueryKey;

    return 0;
}
