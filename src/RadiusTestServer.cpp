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
#include "MainProductionCycle.h"
#include "ProjectManager.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

//-----------------------------------------------------------------------------------------
// test

//-----------------------------------------------------------------------------------------

    // создадим указатель на объект "главной задачи"
    CMainProductionCycleInterface* pxMainProductionCycle;
    // создадим объект "главной задачи"
    pxMainProductionCycle = new CMainProductionCycle();
    // установим начальное состояние автомата задачи
    pxMainProductionCycle ->
    SetFsmState(CMainProductionCycle::MAIN_CYCLE_START);
    // создадим указатель на объект "производственная площадка главной задачи"
    CProductionInterface* pxMainThreadProduction;
    // создадим объект "производственная площадка главной задачи"
    pxMainThreadProduction = new CMainThreadProduction();
//    // разместим задачу на производственной площадке
//    pxMainThreadProduction -> Place(pxMainProductionCycle);


    CProjectManager* pxProjectManager;
    pxProjectManager = new CProjectManager();
    pxProjectManager ->
    SetCommantLineArgumentCustomer(new CCommantLineArgumentCustomer());
    // получим параметры командной строки
    pxProjectManager ->
    GetCommantLineArgumentCustomer() -> GetOrder(argc, argv);
    // получим параметры командной строки от заказчика
    pxProjectManager ->
    GetOrder(pxProjectManager -> GetCommantLineArgumentCustomer());

    pxMainProductionCycle ->
    SetProjectManager(pxProjectManager);

    CMainThreadProduction::Process(pxMainProductionCycle);

    delete pxProjectManager;
    delete pxMainProductionCycle;
    delete pxMainThreadProduction;

    return 0;
}


//-----------------------------------------------------------------------------------------


