//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Production.h"

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

}

//-----------------------------------------------------------------------------------------
CMainThreadProduction::~CMainThreadProduction()
{

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
    while (1)
    {
        pxMainProductionCycleInterface -> Fsm();
        std::cout << "CMainThreadProduction id" << " " << std::this_thread::get_id() << std::endl;
        usleep(1000000);
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

    m_xThread.join();
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
    std::thread m_xThread(CGooseThreadProduction::Process, pxGooseInterface);
    std::thread::id th_id = m_xThread.get_id();
    std::cout << "CGooseThreadProduction th_id" << " " << th_id << std::endl;
    // не ждем завершения работы функции
    m_xThread.detach();
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
        usleep(1000);
    }
}

//-----------------------------------------------------------------------------------------
