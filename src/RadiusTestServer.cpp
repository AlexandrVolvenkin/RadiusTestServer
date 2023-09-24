////============================================================================
//// Name        : RadiusTestServer.cpp
//// Author      : Alexandr Volvenkin
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//using namespace std;
//
//int main() {
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	return 0;
//}




//-----------------------------------------------------------------------------------------
// C Libraries:
#include <string>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <thread>

#include "Platform.h"
#include "Configuration.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
static void help(char *progname)
{
    fprintf(stderr, "-----------------------------------------------------------------------\n");
    fprintf(stderr, "Usage: %s\n" \
            "  -e | --ethernet <name> - set ethernet to <name> (default is eth0)\n" \
            "  -c | --comm <name> - set comm port to <name> (default is comm0)\n" \
            "  -p | --period <time> - set task period  to <time> (default is 10mc)\n" \
            " [-h | --help ]........: display this help\n" \
            " [-v | --version ].....: display version information\n" \
            " [-b | --background]...: fork to the background, daemon mode\n", progname);
    fprintf(stderr, "-----------------------------------------------------------------------\n");
}

//-----------------------------------------------------------------------------------------
// test


void thread_func(uint8_t* puiData)
{

    while (1)
    {
    std::cout << "thread_func puiData" << " " << (int)*puiData << std::endl;
//    std::cout << "thread_func uiData" << " " << (int)uiData << std::endl;
    std::cout << "thread_func" << " " << std::this_thread::get_id() << std::endl;
        usleep(1000000);
    }
}

//int main(int argc, char * argv[])
//{
//    std::thread th(thread_func);
//    std::thread::id th_id = th.get_id();
//    th.join();
//    std::cout << th_id << std::endl;
//    return 0;
//}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

//-----------------------------------------------------------------------------------------
// test

    uint8_t uiData = 56;

    std::thread th(thread_func, &uiData);
    std::thread::id th_id = th.get_id();
//    th.join(); // ждем завершения работы функции блокируем здесь
    th.detach(); // не ждем завершения работы функции



    while (1)
    {
        std::cout << "main uiData" << " " << (int)uiData << std::endl;
        std::cout << "main" << " " << th_id << std::endl;
        usleep(1000000);
    }

    return 0;

//-----------------------------------------------------------------------------------------


    /* parameter parsing */
    while(1)
    {
        int iOption = 0;
        static struct option long_options[] =
        {
            {"help", no_argument, NULL, 'h'},
            {"ethernet", required_argument, NULL, 'e'},
            {"comm", required_argument, NULL, 'c'},
            {"period", required_argument, NULL, 'p'},
            {"version", no_argument, NULL, 'v'},
            {"background", no_argument, NULL, 'b'},
            {NULL, 0, NULL, 0}
        };

        iOption = getopt_long(argc, argv, "he:c:p:vb", long_options, NULL);

//        cout << "iOption = " << iOption << endl;
        /* no more options to parse */
        if(iOption == -1)
        {
            break;
        }

        switch(iOption)
        {
        case 'e':
            cout << "case 'e' " << optarg << endl;
            // получим имя интекфейса ethernet
//            input[global.incnt++] = strdup(optarg);
//        cout << "e arg = " << strdup(optarg) << endl;
            break;

        case 'c':
            cout << "case 'c' " << optarg << endl;
            // получим имя интекфейса comm
//            output[global.outcnt++] = strdup(optarg);
            break;

        case 'p':
            cout << "case 'p' " << optarg << endl;
            // получим длину периода задачи
//            output[global.outcnt++] = strdup(optarg);
            break;

        case 'v':
            cout << "case 'v' " << optarg << endl;
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
            cout << "case 'b' " << optarg << endl;
//            // опция - работать в фоновом режиме
//            daemon = 1;
            break;

        case 'h': /* fall through */
        default:
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}


//-----------------------------------------------------------------------------------------



//    for (int i = 0; i < argc; i++) {
//        // Выводим список аргументов в цикле
//        cout << "Argument " << i << " : " << argv[i] << endl;
//    }

//    int opt;
//    string input = "";
//    bool flagA = false;
//    bool flagB = false;
//
//    // Retrieve the (non-option) argument:
//    if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') )    // there is NO input...
//    {
//        cerr << "No argument provided!" << endl;
//        //return 1;
//    }
//    else    // there is an input...
//    {
//        input = argv[argc-1];
//    }
//
//    // Debug:
//    cout << "input = " << input << endl;
//
//    // Shut GetOpt error messages down (return '?'):
//    opterr = 0;
//
//    // Retrieve the options:
//    while ( (opt = getopt(argc, argv, "ab")) != -1 )    // for each option...
//    {
//        switch ( opt )
//        {
//        case 'a':
//            flagA = true;
//            break;
//        case 'b':
//            flagB = true;
//            break;
//        case '?':  // unknown option...
//            cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
//            break;
//        }
//    }
//
//    // Debug:
//    cout << "flagA = " << flagA << endl;
//    cout << "flagB = " << flagB << endl;
//
//    return 0;



//    // Debug:
//    input = argv[argc-1];
//    cout << "input = " << input << endl;
