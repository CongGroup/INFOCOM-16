#include "RulePairs.h"

#include <string>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <map>
#include <vector>

#include "MidBox.h"

using namespace std;


RulePairs::RulePairs(void)
{
    m_pPair = NULL;
}


RulePairs::~RulePairs(void)
{
}



Pair *RulePairs::GetPairs()
{

	return m_pPair;

}


uint32_t RulePairs::Init(string sPath)
{
    //Deal with the Pair
    vector<Pair> vecPairs;
    ifstream infile(sPath.c_str());

    string strTmp;
    getline(infile, strTmp);
    uint32_t uiPairNum;
    sscanf(strTmp.c_str(), "%u", &uiPairNum);
    while(getline(infile, strTmp))
    {
        Pair pair;
        //RuleID
        sscanf(strTmp.c_str(), "%d", &pair.uiRuleID);
        //ActionID
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%d", &pair.uiAction);
        //iField
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%d", &pair.iField);
        //Offset
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%d", &pair.iOffset);
        //OffsetCount
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%d", &pair.iOffsetCount);
        //ConditionNum
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%d", &pair.iConNum);
        //Key
        getline(infile, pair.strkey);
        
        vecPairs.push_back(pair);
    }

    uint32_t uiLineNum = vecPairs.size();
    //cout<<"Input Line : "<<uiLineNum<<endl;
    //cout<<"All Pair Num : "<<uiPairNum<<endl;

    //Init the memory

    if(m_pPair != NULL)
    {
        delete [] m_pPair;
    }

    m_pPair = new Pair[uiPairNum];

    //Secure Sharing and extension
    Pair *pPair = m_pPair;
    map<int, ShareMask> mapMask;
    map<int, ShareMask>::iterator it_mask = mapMask.end();

    for(vector<Pair>::iterator it = vecPairs.begin(); it != vecPairs.end(); it++)
    {
        if(it_mask == mapMask.end() || it_mask->first != it->uiRuleID)
        {
            ShareMask shareMask;
            shareMask.iCurNum = 0;
            pair<map<int, ShareMask>::iterator, bool> resul = mapMask.insert(make_pair(it->uiRuleID, shareMask));
            it_mask = resul.first;
        }

        //deal with the sharing XOR
        if(it->iConNum > 1)
        {
            //Need to sharing
            if(it_mask->second.iCurNum < it->iConNum - 1)
            {
                //Not last one
                uint32_t uiRand = rand();
                it_mask->second.uiMask = (it_mask->second.iCurNum == 0) ? uiRand : it_mask->second.uiMask ^ uiRand;
                it->uiAction ^= uiRand;
            }
            else if(it_mask->second.iCurNum == it->iConNum - 1)
            {
                //Last one
                it->uiAction ^= it_mask->second.uiMask;
            }
            it_mask->second.iCurNum++;
        }

        //deal with extension
        
        //in Field
        if(it->iField > 0)
        {
            it->strkey += AppendInt('F', it->iField);
        }

        //in Offset and depth
        if(it->iOffset != -1)
        {
            for(int i = 0; i < it->iOffsetCount; i++)
            {
                pPair->uiAction = it->uiAction;
                pPair->uiRuleID = it->uiRuleID;
                pPair->strkey = it->strkey + AppendInt('O', it->iOffset + i);
                pPair++;
            }
        }
        else
        {
            pPair->uiAction = it->uiAction;
            pPair->uiRuleID = it->uiRuleID;
            pPair->strkey = it->strkey;
            pPair++;
        }

        
    }


    return uiPairNum;



}




