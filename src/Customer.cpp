//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <unistd.h>
#include <getopt.h>

#include "Customer.h"
#include "Platform.h"
#include "Configuration.h"

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
CCustomer::CCustomer()
{
//    std::cout << "CCustomer constructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
CCustomer::~CCustomer()
{
//    std::cout << "CCustomer desstructor"  << std::endl;
}
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CCommantLineArgumentCustomer::CCommantLineArgumentCustomer()
{
//    std::cout << "CCommantLineArgumentCustomer constructor"  << std::endl;
    m_pccMode = "server";//"client";//
    m_pccGooseInterfaceName = "eth0";
    m_pccEthernetAddress = "00:00:00:00:00:00";
    m_pccCommInterfaceName = "/dev/ttyO1";
    m_uiCalculationPeriodTime = 5000;//1000000;//
    m_uiLoadPercent = 50;
    m_uiOwnAddress = 7;
}

//-----------------------------------------------------------------------------------------
CCommantLineArgumentCustomer::~CCommantLineArgumentCustomer()
{
//    std::cout << "CCommantLineArgumentCustomer desstructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
void CCommantLineArgumentCustomer::Init(void)
{
//    m_pccMode = "server";//"client";//
//    m_pccGooseInterfaceName = "eth0";
//    m_pccEthernetAddress = "00:00:00:00:00:00";
//    m_pccCommInterfaceName = "ttyO1";
//    m_uiCalculationPeriodTime = 5000;//1000000;//
//    m_uiLoadPercent = 50;

}

//-----------------------------------------------------------------------------------------
uint8_t CCommantLineArgumentCustomer::GetOrder(int argc, char** argv)
{
//    std::cout << "CCommantLineArgumentCustomer GetOrder"  << std::endl;
//        cout << "CCommantLineArgumentCustomer GetOrder argc = " << (int)argc << endl;
//        cout << "CCommantLineArgumentCustomer GetOrder argv = " << argv[0] << endl;
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
//    std::cout << "CCommantLineArgumentCustomer GetOrder if (iOption == -1)"  << std::endl;
//            return 0;
            break;
        }

        switch(iOption)
        {
        case 'm':
//            cout << "case 'm' " << optarg << endl;
            // получим имя интекфейса ethernet
            m_pccMode = optarg;
            break;
        case 'e':
//            cout << "case 'e' " << optarg << endl;
            // получим имя интекфейса ethernet
            m_pccGooseInterfaceName = optarg;
            break;
        case 'a':
//            cout << "case 'a' " << optarg << endl;
            // получим mac адрес
            m_pccEthernetAddress = optarg;
            break;

        case 'c':
//            cout << "case 'c' " << optarg << endl;
            m_pccCommInterfaceName = optarg;
            break;

        case 'p':
//            cout << "case 'p' " << optarg << endl;
            // получим длину периода задачи
            m_uiCalculationPeriodTime = atol(optarg);
            break;

        case 'l':
//            cout << "case 'l' " << optarg << endl;
//            // получим длину периода задачи
            m_uiLoadPercent = atoi(optarg);
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
//            exit(EXIT_FAILURE);
            return 0;
        }
    }

    return 1;
}
