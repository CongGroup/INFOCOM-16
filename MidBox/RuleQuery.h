#ifndef __RULE_QUERY_H__
#define __RULE_QUERY_H__

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <map>

#include "EncFilter.h"

#define DEF_HEADER_COUNT 4


using namespace std;

typedef struct stRequest
{
    string strMethod;
    string strUri;
    string strState;
    string strMsg;

    uint32_t uiMethodOffset;
    uint32_t uiUriOffset;
    uint32_t uiStateOffset;
    uint32_t uiMsgOffset;
    
    uint32_t uiPacketSize;

    vector<string> vecWords;

}Request;

class RuleQuery
{
public:
    RuleQuery(void);
    ~RuleQuery(void);

    uint32_t ReadQueryFile(string sPath);

    void InitKey(string strMstKey);

    void GenQueryKey(vector<QueryKey> &vecQueryKey, Request &request);

    void GenQueryKey(QueryKey *pQueryKey);

    vector<Request> *GetRequestVector();

private:

    //All the keys
    char m_arKey[NR_KEY_TYPE][NR_KEY_CHAR];

    vector<Request> m_vecRequest;

    void m_GenQueryKey(QueryKey *pQueryKey, string strKey, int iOffset, int iFiled);

    map<string, int> m_mapStrCount;

};



#endif

