#include "RuleQuery.h"
#include <string>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <map>

#include "../Caravel/Digest.h"
#include "../Caravel/PRF.h"

#include "MidBox.h"

using namespace std;
using namespace caravel;

RuleQuery::RuleQuery(void)
{
    m_vecRequest.clear();
}


RuleQuery::~RuleQuery(void)
{

}


uint32_t RuleQuery::ReadQueryFile(string sPath)
{
    ifstream infile(sPath.c_str());

    //Get the Token Num
    string strTmp;
    uint32_t uiAllLineNum;

    while(getline(infile, strTmp))
    {
        Request request;
        uint32_t uiLineNum;

        sscanf(strTmp.c_str(), "%u", &uiLineNum);

        //Get the Http Payload Binary Size
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%u", &request.uiPacketSize);

        //Get Http_Method
        getline(infile, request.strMethod);
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%u", &request.uiMethodOffset);

        //Get Http_Uri
        getline(infile, request.strUri);
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%u", &request.uiUriOffset);

        //Get Http_State
        getline(infile, request.strState);
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%u", &request.uiStateOffset);

        //Get Http_Msg
        getline(infile, request.strMsg);
        getline(infile, strTmp);
        sscanf(strTmp.c_str(), "%u", &request.uiMsgOffset);

        for(uint32_t uiCur = 0; uiCur < uiLineNum; uiCur++)
        {
            getline(infile, strTmp);
            request.vecWords.push_back(strTmp);
        }

        m_vecRequest.push_back(request);


        uiAllLineNum += (DEF_HEADER_COUNT * 2 + uiLineNum);

    }


    //cout<<m_vecRequest.size()<<endl;

    //DEF_HEADER_COUNT has two situations : with Field and with Offset.
    return uiAllLineNum;

}

void RuleQuery::InitKey(string strMstKey)
{
    //Generate Keys
    for(uint32_t uiCur = 0; uiCur < NR_KEY_TYPE; uiCur++)
    {
        string sKey = strMstKey + AppendInt('K', uiCur);
        Digest::Sha256(sKey, m_arKey[uiCur], NR_KEY_CHAR);
    }
}

void RuleQuery::GenQueryKey(vector<QueryKey> &vecQueryKey, Request &request)
{
    //http_method field = 5
    QueryKey queryKey;
    m_GenQueryKey(&queryKey, request.strMethod, request.uiMethodOffset, 0);
    vecQueryKey.push_back(queryKey);

    m_GenQueryKey(&queryKey, request.strMethod, -1, 5);
    vecQueryKey.push_back(queryKey);

    //http_uri field = 11
    m_GenQueryKey(&queryKey, request.strUri, request.uiUriOffset, 0);
    vecQueryKey.push_back(queryKey);
    m_GenQueryKey(&queryKey, request.strUri, -1, 11);
    vecQueryKey.push_back(queryKey);

    //http_state 9
    m_GenQueryKey(&queryKey, request.strState, request.uiStateOffset, 0);
    vecQueryKey.push_back(queryKey);
    m_GenQueryKey(&queryKey, request.strState, -1, 9);
    vecQueryKey.push_back(queryKey);

    //http_msg 10
    m_GenQueryKey(&queryKey, request.strMsg, request.uiMsgOffset, 0);
    vecQueryKey.push_back(queryKey);
    m_GenQueryKey(&queryKey, request.strMsg, -1, 10);
    vecQueryKey.push_back(queryKey);

    for(vector<string>::iterator it = request.vecWords.begin(); it != request.vecWords.end(); it++)
    {
        m_GenQueryKey(&queryKey, *it, -1, 0);
        vecQueryKey.push_back(queryKey);
    }
}

vector<Request> *RuleQuery::GetRequestVector()
{
    return &m_vecRequest;
}

void RuleQuery::GenQueryKey(QueryKey *pQueryKey)
{

    m_mapStrCount.clear();

    for(vector<Request>::iterator it_req = m_vecRequest.begin(); it_req != m_vecRequest.end(); it_req++)
    {

        //http_method field = 5
        m_GenQueryKey(pQueryKey++, it_req->strMethod, it_req->uiMethodOffset, 0);
        m_GenQueryKey(pQueryKey++, it_req->strMethod, -1, 5);

        //http_uri field = 11
        m_GenQueryKey(pQueryKey++, it_req->strUri, it_req->uiUriOffset, 0);
        m_GenQueryKey(pQueryKey++, it_req->strUri, -1, 11);

        //http_state 9
        m_GenQueryKey(pQueryKey++, it_req->strState, it_req->uiStateOffset, 0);
        m_GenQueryKey(pQueryKey++, it_req->strState, -1, 9);

        //http_msg 10
        m_GenQueryKey(pQueryKey++, it_req->strMsg, it_req->uiMsgOffset, 0);
        m_GenQueryKey(pQueryKey++, it_req->strMsg, -1, 10);

        for(vector<string>::iterator it = it_req->vecWords.begin(); it != it_req->vecWords.end(); it++)
        {
            m_GenQueryKey(pQueryKey++, *it, -1, 0);
        }

    }

}


void RuleQuery::m_GenQueryKey(QueryKey *pQueryKey, string strKey, int iOffset, int iFiled)
{
    //Init first 4 * 2 Trapdoor
    if(iFiled > 0)
    {
        strKey += AppendInt('F', iFiled);
    }

    if(iOffset > -1)
    {
        strKey += AppendInt('O', iOffset);
    }
    
    int iP = m_mapStrCount[strKey]++ % DEF_PADDING_COUNT;
    
    strKey += AppendInt('P', iP);

    PRF::Sha256(m_arKey[KEY_TYPE_TRAPDOOR], NR_KEY_CHAR, (char*)strKey.c_str(), strKey.length(), pQueryKey->pTd, NR_TRAPDOOR_CHAR);
    PRF::Sha256(m_arKey[KEY_TYPE_MASK], NR_KEY_CHAR, (char*)strKey.c_str(), strKey.length(), pQueryKey->pMask, NR_TRAPDOOR_CHAR);

}


