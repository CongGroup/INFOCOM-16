#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdint.h>

//getch
#include <termios.h>
#include <unistd.h>

#include "TMidboxService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "ThriftAdapt.h"
#include "RulePairs.h"
#include "EncFilter.h"
#include "MidBox.h"
#include "RuleQuery.h"
#include "../Caravel/TimeDiff.h"

using namespace std;
using namespace caravel;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::mb;

class TMidboxServiceHandler : virtual public TMidboxServiceIf {
 public:
  TMidboxServiceHandler() {
    // Your initialization goes here
  }

  void InitIndex(EncFilter *pEncFilter)
  {
      m_pEncFilter = pEncFilter;
  }

  /**
   * Send the QueryKey to Midbox.
   * 
   * @param trapdoors
   */
  void Query(const std::vector<TQueryKey> & trapdoors) {


      QueryKey *pQueryKey = new QueryKey[trapdoors.size()];

      QueryKey *p = pQueryKey;
      for (vector<TQueryKey>::const_iterator it = trapdoors.begin(); it != trapdoors.end(); it++)
      {
          memcpy(p->pTd, it->Trapdoor.c_str(), NR_TRAPDOOR_CHAR);
          memcpy(p->pMask, it->Mask.c_str(), NR_TRAPDOOR_CHAR);
          p++;
      }

      m_pEncFilter->Query(pQueryKey, trapdoors.size());

      delete [] pQueryKey;

  }

  /**
   * Send the Http Payload to Midbox.
   * 
   * @param sPayload
   */
  void WebRequest(const std::string& sPayload) {
    // Your implementation goes here
    //printf("WebRequest\n");
  }

 private:
  EncFilter *m_pEncFilter;


};


int getch(){
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

template<typename T>
T PrintAndGet(char *szMsg)
{
    T tRet;
    cout<<szMsg<<endl<<endl;
    cin>>tRet;
    return tRet;
}

void PrintCmdList(){
    system("clear");
    cout<<"©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©·"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                            MidBox Command List                                       ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§         Input Command Below :                                                                        ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§         0 Exit                                                                                       ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§         1 Init Index And Put Data                                                                    ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§         2 Setup Thrift Server                                                                        ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§         3 Test the Benchmark Data                                                                    ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©§                                                                                                      ©§"<<endl;
    cout<<"©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿"<<endl;
    return;
}

int main(int argc, char **argv)
{

    EncFilter encFilter;
    EncFilter *pEncFilter = &encFilter;

    system("clear");
    int iCmd;
    do{
        PrintCmdList();
        iCmd = getch();
        switch(iCmd)
        {
        case 49:
            {
                //1

				//Read the RulePairs file
				string sPairPath = PrintAndGet<string>("Please input the path of the Pairs file. [ Then Press Enter ]");
				
                RulePairs rulePairs;
                uint32_t uiPairNum = rulePairs.Init(sPairPath);
                Pair *pPair = rulePairs.GetPairs();

                cout<<"Finish process the RulePairs"<<endl;

                int iTest = PrintAndGet<int>("Please input the times you want to repeat the process of init index. [ Then Press Enter ]");

                //For test the average
                for(int i = 0; i < iTest; i++)
                {
                    TimeDiff::DiffTimeInMicroSecond();

                    //Init the Index
                    pEncFilter->InitIndex(DEF_MASTER_KEY, DEF_SHM_KEY, uiPairNum);

                    //Insert the Pairs into Index
                    pEncFilter->Insert(pPair, uiPairNum);

                    uint32_t uiTime = TimeDiff::DiffTimeInMicroSecond();
                    cout<<uiTime<<endl;
                }

                break;
            }
        case 50:
            {
                //2
                int port = DEF_THRIFT_PORT;
                boost::shared_ptr<TMidboxServiceHandler> handler(new TMidboxServiceHandler());

                handler->InitIndex(pEncFilter);

                boost::shared_ptr<TProcessor> processor(new TMidboxServiceProcessor(handler));
                boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
                boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
                boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

                TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
                
                cout<<"Server Begin !"<<endl;
                server.serve();

                break;
            }
        case 51:
            {
                //3
                string sQueryPath = PrintAndGet<string>("Please input the path of the Query file. [ Then Press Enter ]");

                RuleQuery ruleQuery;
                uint32_t uiNum = ruleQuery.ReadQueryFile(sQueryPath);

                //cout<<"Find ["<<uiNum<<"] Query Token"<<endl;

                QueryKey *pQueryKey = new QueryKey[uiNum];
                memset(pQueryKey, 0, sizeof(uiNum * sizeof(QueryKey)));

                ruleQuery.InitKey(DEF_MASTER_KEY);
                vector<Request> *pvecRequest = ruleQuery.GetRequestVector();

                ThriftAdapt<TMidboxServiceClient> adapt;
                adapt.Init(DEF_THRIFT_IP, (uint16_t)DEF_THRIFT_PORT);
                adapt.Open();
                TMidboxServiceClient *pMidboxClient = adapt.GetClient();

                string strHttpRequest;

                uint32_t uiStopCnt = 500;
                vector<TQueryKey> vecTQuery;
                vector<QueryKey> vecQueryKey;

                uint32_t uiRequestTime;
                uint32_t uiTrapdoorTime;

                for(vector<Request>::iterator it = pvecRequest->begin(); it != pvecRequest->end(); it++)
                {

                    //The time simulate the http request
                    TimeDiff::DiffTimeInMicroSecond();

                    strHttpRequest.assign('0', it->uiPacketSize);
                    pMidboxClient->WebRequest(strHttpRequest);

                    uiRequestTime = TimeDiff::DiffTimeInMicroSecond();
                    cout<<"Request:"<<uiRequestTime<<endl;

                    //generate trapdoor and send to server

                    vecTQuery.clear();
                    vecQueryKey.clear();
                    ruleQuery.GenQueryKey(vecQueryKey, *it);
                    for(vector<QueryKey>::iterator it_key = vecQueryKey.begin(); it_key != vecQueryKey.end(); it_key++)
                    {
                        TQueryKey tQuery;
                        tQuery.Trapdoor.assign('0', NR_TRAPDOOR_CHAR);
                        tQuery.Mask.assign('0', NR_TRAPDOOR_CHAR);

                        memcpy((char*)tQuery.Trapdoor.c_str(), it_key->pTd, NR_TRAPDOOR_CHAR);
                        memcpy((char*)tQuery.Mask.c_str(), it_key->pMask, NR_TRAPDOOR_CHAR);

                        vecTQuery.push_back(tQuery);
                    }

                    pMidboxClient->Query(vecTQuery);

                    uiTrapdoorTime = TimeDiff::DiffTimeInMicroSecond();
                    cout<<"Trapdoor:"<<uiTrapdoorTime<<endl;

                    if(uiStopCnt-- == 0)
                    {
                        break;
                    }

                }


                adapt.Close();

                break;
            }
        case 52:
            {
                //4
                break;
            }
        case 53:
            {
                //5
                break;
            }
        case 54:
            {
                //6
                break;
            }
        default:
            {
                continue;
                break;
            }
        };

        cout<<"Press [Enter] to continue..."<<endl;
        getch();
        getch();

    }while(48 != iCmd);

    cout<<"Good Bye !"<<endl;

    return 0;
}