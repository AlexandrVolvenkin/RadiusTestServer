
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------
#ifndef CMAINPRODUCTIONCYCLE_H
#define CMAINPRODUCTIONCYCLE_H

#include <iostream>
#include <string.h>

#include "Platform.h"
#include "Task.h"
#include "Production.h"
#include "Goose.h"
#include "GooseEthernet.h"
#include "ProjectManager.h"

//-----------------------------------------------------------------------------------------
class CMainProductionCycleInterface : public CTask
{
public:
    virtual void Init(void) {};

    virtual void SetProjectManager(CProjectManager* pxProjectManager) {};
    virtual CProjectManager* GetProjectManager(void) {};

};
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CMainProductionCycle : public CMainProductionCycleInterface
{
public:

    enum
    {
        IDDLE  = 0,
        START,

        MAIN_CYCLE_STOPED,
        MAIN_CYCLE_START,
        MAIN_CYCLE_IDDLE,
        MAIN_CYCLE_DATA_RECEIVE_PREPARE,
        MAIN_CYCLE_DATA_RECEIVE_WAITING,
        MAIN_CYCLE_RECEIVED_DATA_PROCESSING,
        MAIN_CYCLE_RECEIVED_DATA_ERROR_PROCESSING,
        MAIN_CYCLE_DATA_TRANSMIT_PREPARE,
        MAIN_CYCLE_DATA_TRANSMIT,
        MAIN_CYCLE_IDDLE_STATE_PREPARE,
        MAIN_CYCLE_STOP_STATE_PREPARE,
    };

    CMainProductionCycle();
    virtual ~CMainProductionCycle();
    void Init(void);
    void Fsm(void);

    void SetProjectManager(CProjectManager* pxProjectManager)
    {
        m_pxProjectManager = pxProjectManager;
    }
    CProjectManager* GetProjectManager(void)
    {
        return m_pxProjectManager;
    }

    void SetGooseEthernet(CGooseInterface* pxGooseEthernet)
    {
        m_pxGooseEthernet = pxGooseEthernet;
    };
    CGooseInterface* GetGooseEthernet(void)
    {
        return m_pxGooseEthernet;
    };

private:
    // указатель на объект "управляющий проектом"
    CProjectManager* m_pxProjectManager;
    // указатель на объект "Goose задачи"
    CGooseInterface* m_pxGooseEthernet;
    // указатель на объект "производственная площадка Goose задачи"
    CProductionInterface* m_pxGooseThreadProduction;

    // указатель на объект "Rte задачи"
    CRte* pxRte;
    // указатель на объект "производственная площадка Rte задачи"
    CProductionInterface* m_pxRteThreadProduction;
};

//-----------------------------------------------------------------------------------------
#endif // CMAINPRODUCTIONCYCLE_H
