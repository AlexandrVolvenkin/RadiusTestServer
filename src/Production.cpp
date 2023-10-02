//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Production.h"
#include "MainProductionCycle.h"

using namespace std;

//-----------------------------------------------------------------------------------------
CProduction::CProduction()
{

}

//-----------------------------------------------------------------------------------------
CProduction::~CProduction()
{

}

////-----------------------------------------------------------------------------------------
//void CProduction::Create(void)
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CProduction::Place(void)
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CProduction::Start(void)
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CProduction::Stop(void)
//{
//
//}

//-----------------------------------------------------------------------------------------
void CProduction::Sleep(void)
{
//    GetThread() -> sleep_for(std::chrono::milliseconds(1000));
}

//-----------------------------------------------------------------------------------------
void CProduction::Wakeup(void)
{
    GetThread() -> detach();
}
//
////-----------------------------------------------------------------------------------------
//void CProduction::Process(void)
//{
//
//}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CMainThreadProduction::CMainThreadProduction()
{
//    std::cout << "CMainThreadProduction constructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
CMainThreadProduction::~CMainThreadProduction()
{
//    std::cout << "CMainThreadProduction desstructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
void CMainThreadProduction::Place(CMainProductionCycleInterface* pxMainProductionCycleInterface)
{

//    std::thread th(CMainThreadProduction::Process, pxMainProductionCycleInterface);
//    std::thread::id th_id = th.get_id();
//    std::cout << "CMainThreadProduction th_id" << " " << th_id << std::endl;
//    // не ждем завершения работы функции
//    th.detach();
}

//-----------------------------------------------------------------------------------------
void CMainThreadProduction::Process(CMainProductionCycleInterface* pxMainProductionCycleInterface)
{
//    std::cout << "CMainThreadProduction Process"  << std::endl;
    while (1)
    {
//    std::cout << "CMainThreadProduction Process 2"  << std::endl;
        pxMainProductionCycleInterface -> Fsm();
//        std::cout << "CMainThreadProduction id" << " " << std::this_thread::get_id() << std::endl;
//        usleep(100000);
    }
}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CGooseThreadProduction::CGooseThreadProduction()
{

}

//-----------------------------------------------------------------------------------------
CGooseThreadProduction::~CGooseThreadProduction()
{

    GetThread() -> join();
}

////-----------------------------------------------------------------------------------------
//void CGooseThreadProduction::Create(void)
//{
//
////    std::thread th(Process);
////    // не ждем завершения работы функции
////    th.detach();
//}

////-----------------------------------------------------------------------------------------
//void CGooseThreadProduction::Create(CGooseInterface* pxGooseInterface)
//{
//
//    std::thread th(CGooseThreadProduction::Process, pxGooseInterface);
//    std::thread::id th_id = th.get_id();
//    std::cout << "CGooseThreadProduction th_id" << " " << th_id << std::endl;
//    // не ждем завершения работы функции
//    th.detach();
//}

//-----------------------------------------------------------------------------------------
void CGooseThreadProduction::Place(CGooseInterface* pxGooseInterface)
{
//    std::thread m_xThread(CGooseThreadProduction::Process, pxGooseInterface);
//    SetThread(&m_xThread);
    SetThread(new std::thread(CGooseThreadProduction::Process, pxGooseInterface));
    std::thread::id th_id = GetThread() -> get_id();
//    std::cout << "CGooseThreadProduction th_id" << " " << th_id << std::endl;
    // не ждем завершения работы функции
    GetThread() -> detach();
}

////-----------------------------------------------------------------------------------------
//void CGooseThreadProduction::Start(void)
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CGooseThreadProduction::Stop(void)
//{
//
//}

//-----------------------------------------------------------------------------------------
void CGooseThreadProduction::Process(CGooseInterface* pxGooseInterface)
{
    while (1)
    {
        pxGooseInterface -> Fsm();
//        std::cout << "CGooseThreadProduction id" << " " << std::this_thread::get_id() << std::endl;
//        usleep(1000000);
//        usleep(1000);
    }
}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CRteThreadProduction::CRteThreadProduction()
{

}

//-----------------------------------------------------------------------------------------
CRteThreadProduction::~CRteThreadProduction()
{

    GetThread() -> join();
}

////-----------------------------------------------------------------------------------------
//void CRteThreadProduction::Create(void)
//{
//
////    std::thread th(Process);
////    // не ждем завершения работы функции
////    th.detach();
//}

////-----------------------------------------------------------------------------------------
//void CRteThreadProduction::Create(CRte* pxRte)
//{
//
//    std::thread th(CRteThreadProduction::Process, pxRte);
//    std::thread::id th_id = th.get_id();
//    std::cout << "CRteThreadProduction th_id" << " " << th_id << std::endl;
//    // не ждем завершения работы функции
//    th.detach();
//}

//-----------------------------------------------------------------------------------------
void CRteThreadProduction::Place(CRte* pxRte)
{
    std::thread m_xThread(CRteThreadProduction::Process, pxRte);
    std::thread::id th_id = m_xThread.get_id();
//    std::cout << "CRteThreadProduction th_id" << " " << th_id << std::endl;
    // не ждем завершения работы функции
    m_xThread.detach();
}

////-----------------------------------------------------------------------------------------
//void CRteThreadProduction::Start(void)
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CRteThreadProduction::Stop(void)
//{
//
//}

//-----------------------------------------------------------------------------------------
void CRteThreadProduction::Process(CRte* pxRte)
{
    while (1)
    {
        pxRte -> Fsm();
//        std::cout << "CRteThreadProduction id" << " " << std::this_thread::get_id() << std::endl;
//        usleep(1000000);
//        usleep(1000);

//        // Print Thread ID and Counter i
//        std::cout<<std::this_thread::get_id()<<" :: "<<std::endl;
//        // Sleep this thread for 200 MilliSeconds
//        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

//-----------------------------------------------------------------------------------------
