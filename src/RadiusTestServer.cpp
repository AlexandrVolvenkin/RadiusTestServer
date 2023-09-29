//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------
// C Libraries:
#include <string>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <thread>

#include "Platform.h"
#include "Configuration.h"
#include "Goose.h"
#include "GooseEthernet.h"
#include "Production.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
static void help(char *progname)
{
    fprintf(stderr, "-----------------------------------------------------------------------\n");
    fprintf(stderr, "Usage: %s\n" \
            "  -m | --mode <mode> - set mode to <mode> (default is server)\n" \
            "  -e | --ethernet <name> - set ethernet to <name> (default is eth0)\n" \
            "  -a | --mac <mac> - set mac address to <mac> (default is 00:00:00:00:00:00)\n" \
            "  -c | --comport <name> - set comport to <name> (default is com0)\n" \
            "  -p | --period <time> - set task period  to <time> (default is 10mc)\n" \
            "  -l | --load <percent> - set load percent  to <percent> (default is 50)\n" \
            " [-h | --help ]........: display this help\n" \
            " [-v | --version ].....: display version information\n" \
            " [-b | --background]...: fork to the background, daemon mode\n", progname);
    fprintf(stderr, "-----------------------------------------------------------------------\n");
}

//-----------------------------------------------------------------------------------------
// test

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

//-----------------------------------------------------------------------------------------
// test

    uint8_t uiData = 56;
//    return 0;

////uint8_t ether_dhost[6];
//    const char* pcMacAddress = "64:cf:d9:55:ca:1e";
////    struct ether_addr *ether_aton(pcMacAddress);
//
//    struct ether_addr* pxEthernetAddress;
//    pxEthernetAddress = ether_aton(pcMacAddress);
//
//    cout << "Read" << endl;
//    unsigned char *pucSourceTemp;
//    pucSourceTemp = (unsigned char*)pxEthernetAddress -> ether_addr_octet;
//    for(int i=0; i<8; )
//    {
//        for(int j=0; j<8; j++)
//        {
//            cout << hex << uppercase << setw(2) << setfill('0') << (unsigned int)pucSourceTemp[i + j] << " ";
//        }
//        cout << endl;
//        i += 8;
//    }

//  struct ether_addr {
//        uint8_t ether_addr_octet[6];
//  }
//-----------------------------------------------------------------------------------------

    const char *pccMode = "server";//"client";//
    const char *pccGooseInterfaceName = "eth0";
    const char *pccEthernetAddress = "00:00:00:00:00:00";
    const char *pccCommInterfaceName = "ttyO1";
    uint32_t uiCalculationPeriodTime = 5000;//1000000;//
    uint8_t uiLoadPercent = 50;

    /* parameter parsing */
    while(1)
    {
        int iOption = 0;
        static struct option long_options[] =
        {
            {"help", no_argument, NULL, 'h'},
            {"mode", required_argument, NULL, 'm'},
            {"ethernet", required_argument, NULL, 'e'},
            {"mac", required_argument, NULL, 'a'},
            {"comport", required_argument, NULL, 'c'},
            {"period", required_argument, NULL, 'p'},
            {"load", required_argument, NULL, 'l'},
            {"version", no_argument, NULL, 'v'},
            {"background", no_argument, NULL, 'b'},
            {NULL, 0, NULL, 0}
        };

        iOption = getopt_long(argc, argv, "hm:e:a:c:p:l:vb", long_options, NULL);

//        cout << "iOption = " << iOption << endl;
        /* no more options to parse */
        if(iOption == -1)
        {
            break;
        }

        switch(iOption)
        {
        case 'm':
//            cout << "case 'm' " << optarg << endl;
            // получим имя интекфейса ethernet
            pccMode = optarg;
            break;
        case 'e':
//            cout << "case 'e' " << optarg << endl;
            // получим имя интекфейса ethernet
            pccGooseInterfaceName = optarg;
            break;
        case 'a':
//            cout << "case 'a' " << optarg << endl;
            // получим mac адрес
            pccEthernetAddress = optarg;
            break;

        case 'c':
//            cout << "case 'c' " << optarg << endl;
            pccCommInterfaceName = optarg;
            break;

        case 'p':
//            cout << "case 'p' " << optarg << endl;
            // получим длину периода задачи
            uiCalculationPeriodTime = atol(optarg);
            break;

        case 'l':
//            cout << "case 'l' " << optarg << endl;
//            // получим длину периода задачи
            uiLoadPercent = atoi(optarg);
            break;

        case 'v':
//            cout << "case 'v' " << optarg << endl;
            // опция -v версия
            printf("RadiusTestServer Version: %s\n",
#ifdef GIT_HASH
                   GIT_HASH
#else
                   SOURCE_VERSION
#endif
                  );
            return 0;
            break;

        case 'b':
//            cout << "case 'b' " << optarg << endl;
//            // опция - работать в фоновом режиме
//            daemon = 1;
            break;

        case 'h': /* fall through */
        default:
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    // создадим указатель на объект "производственная площадка главной задачи"
    CProductionInterface* pxMainThreadProduction;
    // создадим объект "производственная площадка главной задачи"
    pxMainThreadProduction = new CMainThreadProduction();

    // создадим указатель на объект "главной задачи"
    CMainProductionCycleInterface* pxMainProductionCycle;
    // создадим объект "главной задачи"
    pxMainProductionCycle = new CMainProductionCycle();
    // установим начальное состояние автомата задачи
    pxMainProductionCycle -> SetFsmState(CMainProductionCycle::IDDLE);
//    // разместим задачу на производственной площадке
//    pxMainThreadProduction -> Place(pxMainProductionCycle);


    // создадим указатель на объект "производственная площадка Goose задачи"
    CProductionInterface* pxGooseThreadProduction;
    // создадим объект "производственная площадка Goose задачи"
    pxGooseThreadProduction = new CGooseThreadProduction();

    // создадим указатель на объект "Goose задачи"
    CGooseInterface* pxGooseEthernet;
    // создадим объект "Goose задачи"
    pxGooseEthernet = new CGooseEthernet();
    // создадим и добавим объект "наблюдатель"
    pxGooseEthernet -> SetGooseServerObserver(new CGooseServerObserver());
    // установим имя интерфейса
    pxGooseEthernet -> GetCommunicationDevice() -> SetPortName(pccGooseInterfaceName);
    // установим mac адрес назначения
    pxGooseEthernet -> GetCommunicationDevice() -> SetDestinationMacAddress(ether_aton(pccEthernetAddress) -> ether_addr_octet);
    // установим период
    pxGooseEthernet -> SetPeriodTime(uiCalculationPeriodTime);
    // установим период вывода статистики
    pxGooseEthernet -> GetTimerPointer() -> Set(1000);


    // создадим указатель на объект "производственная площадка Rte задачи"
    CProductionInterface* pxRteThreadProduction;


    // режим работы - сервер?
    if (strcmp(pccMode, "server") == 0)
    {
        std::cout << "main mode server"  << std::endl;
        pxGooseEthernet -> SetOwnAddress(7);
        // установим начальное состояние автомата задачи, режим работы - сервер
        pxGooseEthernet -> SetFsmState(CGooseEthernet::REQUEST_ENABLE);
        // создадим объект "производственная площадка Rte задачи"
        pxRteThreadProduction = new CRteThreadProduction();

        // создадим указатель на объект "Rte задачи"
        CRte* pxRte;
        // создадим объект "Rte задачи"
        pxRte = new CRte();
        // установим имя интерфейса
        pxRte -> GetCommunicationDevice() -> SetPortName(pccCommInterfaceName);
        pxRte -> GetCommunicationDevice() -> SetBaudRate(115200);
        pxRte -> GetCommunicationDevice() -> SetDataBits(8);
        pxRte -> GetCommunicationDevice() -> SetParity('N');
        pxRte -> GetCommunicationDevice() -> SetStopBit(1);
        // установим период вычислений
        pxRte -> SetPeriodTime(uiCalculationPeriodTime);
        // установим процент нагрузки
        pxRte -> SetLoadPercent(uiLoadPercent);
        // установим начальное состояние автомата задачи, режим работы
        pxRte -> SetFsmState(CRte::START);
        // разместим задачу на производственной площадке
        pxRteThreadProduction -> Place(pxRte);
    }
    // режим работы - клиент?
    else if (strcmp(pccMode, "client") == 0)
    {
        std::cout << "main mode client"  << std::endl;
        pxGooseEthernet -> SetOwnAddress(7);
        pxGooseEthernet -> SetAttemptNumber(CGooseEthernet::PING_ATTEMPTS_NUMBER);
        pxGooseEthernet -> ReportSlaveIDRequest(7);
        pxGooseEthernet -> SetFsmState(CGooseEthernet::CONFIRMATION_ENABLE);
    }
    else
    {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }

//    std::cout << "main mode server"  << std::endl;
//    pxGooseEthernet -> SetOwnAddress(7);
//    // установим начальное состояние автомата задачи, режим работы - сервер
//    pxGooseEthernet -> SetFsmState(CGooseEthernet::REQUEST_ENABLE);

//        std::cout << "main mode client"  << std::endl;
//        pxGooseEthernet -> SetOwnAddress(7);
//        pxGooseEthernet -> SetAttemptNumber(CGooseEthernet::PING_ATTEMPTS_NUMBER);
//        pxGooseEthernet -> ReportSlaveIDRequest(1);
//        pxGooseEthernet -> SetFsmState(CGooseEthernet::CONFIRMATION_ENABLE);

    // разместим задачу на производственной площадке
    pxGooseThreadProduction -> Place(pxGooseEthernet);


//    pxMainProductionCycle -> SetFsmState(0);
//    pxMainProductionCycle -> SetOwnAddress(77);
////    pxMainProductionCycle -> GetOwnAddress();

//    pxGooseEthernet -> SetFsmState(0);
//    pxGooseEthernet -> SetOwnAddress(78);
//    pxGooseEthernet -> GetOwnAddress();

//    while (1)
//    {
////        pxGooseEthernet -> Fsm();
//
//        std::cout << "main FsmState" << " " << (int)pxGooseEthernet -> GetFsmState() << std::endl;
//        std::cout << "main OwnAddress" << " " << (int)pxGooseEthernet -> GetOwnAddress() << std::endl;
//        std::cout << "main uiData" << " " << (int)uiData << std::endl;
//        usleep(1000000);
//    }


    CMainThreadProduction::Process(pxMainProductionCycle);

    delete pxMainProductionCycle;
    delete pxMainThreadProduction;

    delete pxGooseEthernet;
    delete pxGooseThreadProduction;

//    delete pxRte;
    delete pxRteThreadProduction;

    return 0;
}


//-----------------------------------------------------------------------------------------


