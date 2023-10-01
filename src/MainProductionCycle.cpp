
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <iostream>
#include <string.h>

#include "Platform.h"
#include "MainProductionCycle.h"

//-----------------------------------------------------------------------------------------
CMainProductionCycle::CMainProductionCycle()
{
//    std::cout << "CMainProductionCycle constructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
CMainProductionCycle::~CMainProductionCycle()
{
//    std::cout << "CMainProductionCycle destructor"  << std::endl;
    delete m_pxGooseEthernet;
    delete m_pxGooseThreadProduction;

    delete m_pxRte;
    delete m_pxRteThreadProduction;
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Init(void)
{

    // создадим объект "Goose задачи"
    m_pxGooseEthernet = new CGooseEthernet();
//    // создадим и добавим объект "наблюдатель"
//    m_pxGooseEthernet -> SetGooseServerObserver(new CGooseServerObserver());
    // установим имя интерфейса
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetPortName(GetProjectManager() -> GetGooseInterfaceName());
    // установим mac адрес назначения
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetDestinationMacAddress(
        ether_aton(GetProjectManager() -> GetEthernetAddress()) ->
        ether_addr_octet);
    // установим период
    m_pxGooseEthernet ->
    SetPeriodTime(GetProjectManager() -> GetCalculationPeriodTime());
    // установим период вывода статистики
    m_pxGooseEthernet ->
    GetTimerPointer() -> Set(1000);

    m_pxGooseEthernet -> WorkingArraysInit(m_aucRtuCoilsArray,
                                           m_aucRtuDiscreteInputsArray,
                                           m_aucRtuHoldingRegistersArray,
                                           m_aucRtuInputRegistersArray,
                                           COILS_WORK_ARRAY_LENGTH,
                                           DISCRETE_INPUTS_ARRAY_LENGTH,
                                           HOLDING_REGISTERS_ARRAY_LENGTH,
                                           INPUT_REGISTERS_ARRAY_LENGTH
                                          );
    // создадим объект "производственная площадка Goose задачи"
    m_pxGooseThreadProduction = new CGooseThreadProduction();




    // установим имя интерфейса
    m_pxRte ->
    GetCommunicationDevice() ->
    SetPortName(GetProjectManager() -> GetGooseInterfaceName());
    m_pxRte ->
    GetCommunicationDevice() -> SetBaudRate(115200);
    m_pxRte ->
    GetCommunicationDevice() -> SetDataBits(8);
    m_pxRte ->
    GetCommunicationDevice() -> SetParity('N');
    m_pxRte ->
    GetCommunicationDevice() -> SetStopBit(1);
    // установим период вычислений
    m_pxRte ->
    SetPeriodTime(GetProjectManager() ->
                  GetCalculationPeriodTime());
    // установим процент нагрузки
    m_pxRte ->
    SetLoadPercent(GetProjectManager() ->
                   GetLoadPercent());
    // установим начальное состояние автомата задачи, режим работы
    m_pxRte -> SetFsmState(CRte::START);

//    // создадим объект "производственная площадка Rte задачи"
//    pxRteThreadProduction = new CRteThreadProduction();
//    // разместим задачу на производственной площадке
//    pxRteThreadProduction -> Place(m_pxRte);

}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::ServerInit(void)
{
    // создадим объект "Goose задачи"
    m_pxGooseEthernet = new CGooseEthernet();
//    // создадим и добавим объект "наблюдатель"
//    m_pxGooseEthernet -> SetGooseServerObserver(new CGooseServerObserver());
    // установим имя интерфейса
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetPortName(GetProjectManager() -> GetGooseInterfaceName());
    // установим mac адрес назначения
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetDestinationMacAddress(
        ether_aton(GetProjectManager() -> GetEthernetAddress()) ->
        ether_addr_octet);
    // установим период
    m_pxGooseEthernet ->
    SetPeriodTime(GetProjectManager() -> GetCalculationPeriodTime());
    // установим период вывода статистики
    m_pxGooseEthernet ->
    GetTimerPointer() -> Set(1000);

    m_pxGooseEthernet ->
    WorkingArraysInit(m_aucRtuCoilsArray,
                      m_aucRtuDiscreteInputsArray,
                      m_aucRtuHoldingRegistersArray,
                      m_aucRtuInputRegistersArray,
                      COILS_WORK_ARRAY_LENGTH,
                      DISCRETE_INPUTS_ARRAY_LENGTH,
                      HOLDING_REGISTERS_ARRAY_LENGTH,
                      INPUT_REGISTERS_ARRAY_LENGTH
                     );
    // создадим объект "производственная площадка Goose задачи"
    m_pxGooseThreadProduction = new CGooseThreadProduction();
    m_pxGooseEthernet ->
    SetOwnAddress(GetProjectManager() -> GetOwnAddress());
    // установим начальное состояние автомата задачи, режим работы - сервер
    m_pxGooseEthernet ->
    SetFsmState(CGooseEthernet::REQUEST_ENABLE);
    // разместим задачу на производственной площадке
    m_pxGooseThreadProduction -> Place(m_pxGooseEthernet);




    // создадим объект "Rte задачи"
    m_pxRte = new CRte();
    // установим имя интерфейса
    m_pxRte ->
    GetCommunicationDevice() ->
    SetPortName(GetProjectManager() -> GetGooseInterfaceName());
    m_pxRte ->
    GetCommunicationDevice() -> SetBaudRate(115200);
    m_pxRte ->
    GetCommunicationDevice() -> SetDataBits(8);
    m_pxRte ->
    GetCommunicationDevice() -> SetParity('N');
    m_pxRte ->
    GetCommunicationDevice() -> SetStopBit(1);
    // установим период вычислений
    m_pxRte ->
    SetPeriodTime(GetProjectManager() ->
                  GetCalculationPeriodTime());
    // установим процент нагрузки
    m_pxRte ->
    SetLoadPercent(GetProjectManager() ->
                   GetLoadPercent());
    // установим начальное состояние автомата задачи, режим работы
    m_pxRte -> SetFsmState(CRte::START);

    // создадим объект "производственная площадка Rte задачи"
    pxRteThreadProduction = new CRteThreadProduction();
    // разместим задачу на производственной площадке
    pxRteThreadProduction -> Place(m_pxRte);

}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::ClientInit(void)
{
    // создадим объект "Goose задачи"
    m_pxGooseEthernet = new CGooseEthernet();
//    // создадим и добавим объект "наблюдатель"
//    m_pxGooseEthernet -> SetGooseServerObserver(new CGooseServerObserver());
    // установим имя интерфейса
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetPortName(GetProjectManager() -> GetGooseInterfaceName());
    // установим mac адрес назначения
    m_pxGooseEthernet ->
    GetCommunicationDevice() ->
    SetDestinationMacAddress(
        ether_aton(GetProjectManager() -> GetEthernetAddress()) ->
        ether_addr_octet);
    // установим период
    m_pxGooseEthernet ->
    SetPeriodTime(GetProjectManager() -> GetCalculationPeriodTime());
    // установим период вывода статистики
    m_pxGooseEthernet ->
    GetTimerPointer() -> Set(1000);

    m_pxGooseEthernet -> WorkingArraysInit(m_aucRtuCoilsArray,
                                           m_aucRtuDiscreteInputsArray,
                                           m_aucRtuHoldingRegistersArray,
                                           m_aucRtuInputRegistersArray,
                                           COILS_WORK_ARRAY_LENGTH,
                                           DISCRETE_INPUTS_ARRAY_LENGTH,
                                           HOLDING_REGISTERS_ARRAY_LENGTH,
                                           INPUT_REGISTERS_ARRAY_LENGTH
                                          );
    // создадим объект "производственная площадка Goose задачи"
    m_pxGooseThreadProduction = new CGooseThreadProduction();
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Fsm(void)
{
    switch (GetFsmState())
    {
    case MAIN_CYCLE_START:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_START"  << std::endl;
        // режим работы - сервер?
        if (strcmp(GetProjectManager() -> GetMode(), "server") == 0)
        {
            std::cout << "main mode server"  << std::endl;
            SetFsmState(MAIN_CYCLE_SERVER_INIT);
        }
        // режим работы - клиент?
        else if (strcmp(GetProjectManager() -> GetMode(), "client") == 0)
        {
            std::cout << "main mode client"  << std::endl;
            SetFsmState(MAIN_CYCLE_CLIENT_INIT);
        }
        else
        {
            SetFsmState(MAIN_CYCLE_STOP_STATE_PREPARE);
        }
        break;

    case MAIN_CYCLE_SERVER_INIT:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        ServerInit();
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_CLIENT_INIT:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        ClientInit();
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_IDDLE_STATE_PREPARE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_IDDLE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE"  << std::endl;
        break;

    case MAIN_CYCLE_STOP_STATE_PREPARE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_STOP_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_STOPED);
        break;

    case MAIN_CYCLE_STOPED:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_STOPED"  << std::endl;
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
