
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Task.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------
CTask::CTask()
{
    std::cout << "CTask constructor"  << std::endl;

}


//-----------------------------------------------------------------------------------------
CTask::~CTask()
{
    std::cout << "CTask destructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------







////-----------------------------------------------------------------------------------------
//CMainProductionTask::CMainProductionTask()
//{
//    SetFsmState(TASK_START);
//}
//
////-----------------------------------------------------------------------------------------
//CMainProductionTask::~CMainProductionTask()
//{
//
//}
//
////-----------------------------------------------------------------------------------------
//void CMainProductionTask::Fsm(void)
//{
//    // какое событие обрабатываем?
//    switch (GetFsmState())
//    {
//    case TASK_IDDLE:
//        break;
//
//    case TASK_START:
//        break;
//
//    case TASK_IS_SOLVED:
//        break;
//
//    default:
//        break;
//    }
//}
//
////-----------------------------------------------------------------------------------------
//bool CMainProductionTask::IsSolved(void)
//{
//    if (GetFsmState() == TASK_IS_SOLVED)
//    {
//        SetFsmState(TASK_START);
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
////-----------------------------------------------------------------------------------------

