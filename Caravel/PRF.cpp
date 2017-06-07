#include "PRF.h"
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>

using namespace std;

#define DEF_SHA256_LEN 32

namespace caravel{

uint32_t PRF::Sha256(char *pKey, uint32_t uiKeyLen, char *pData, uint32_t uiDataLen, char *pOut, uint32_t uiOutLen)
{
    if(NULL != pOut)
    {
        memset(pOut, 0, uiOutLen);
    }
    //It places the result in md (which must have space for the output of the hash function, which is no more than EVP_MAX_MD_SIZE bytes). If md is NULL, the digest is placed in a static array. The size of the output is placed in md_len, unless it is NULL.
    assert(uiOutLen <= DEF_SHA256_LEN);
    if(uiOutLen == DEF_SHA256_LEN)
    {
        HMAC(EVP_sha256(), pKey, uiKeyLen, (unsigned char*)pData, uiDataLen, (unsigned char*)pOut, &uiOutLen);
    }
    else
    {
        char szBuf[DEF_SHA256_LEN];
        memset(szBuf, 0, sizeof(szBuf));
        uint32_t uiBufLen = DEF_SHA256_LEN;
        HMAC(EVP_sha256(), pKey, uiKeyLen, (unsigned char*)pData, uiDataLen, (unsigned char*)szBuf, &uiBufLen);
        memcpy(pOut, szBuf, uiOutLen);
    }
    
    return uiOutLen;
}

}
