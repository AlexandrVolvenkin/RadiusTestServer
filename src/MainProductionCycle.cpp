
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
#include "Statistics.h"
#include "Representation.h"

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
    delete m_pxGooseServerObserver;
    delete m_pxGooseClientObserver;
    delete m_pxGooseServerStatistics;
    delete m_pxGooseConsoleRepresentation;

    delete m_pxRte;
    delete m_pxRteThreadProduction;
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Init(void)
{
    // создадим и добавим объект "наблюдатель"
    SetGooseServerObserver(new CGooseServerObserver());
    // создадим и добавим объект "наблюдатель"
    SetGooseClientObserver(new CGooseClientObserver());
    // создадим и добавим объект "статистика"
    SetGooseServerStatistics(new CGooseServerStatistics());
    // создадим и добавим объект "представление"
    SetGooseConsoleRepresentation(new CGooseConsoleRepresentation());

    // передадим указатель на объект "наблюдатель" объект "статистика"
    m_pxGooseServerStatistics ->
    SetGooseServerObserver(GetGooseServerObserver());
    // передадим указатель на объект "наблюдатель" объект "статистика"
    m_pxGooseServerStatistics ->
    SetGooseClientObserver(GetGooseClientObserver());
    // передадим указатель на объект "статистика" объект "представление"
    m_pxGooseConsoleRepresentation ->
    SetGooseServerStatistics(GetGooseServerStatistics());

    GetGooseConsoleRepresentationTimer() ->
    Set(MAIN_CYCLE_SHOW_STATISTICS_PERIOD_TIME);
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::ServerInit(void)
{
    // создадим объект "Goose задачи"
    m_pxGooseEthernet = new CGooseEthernet();
    // передадим указатель на объект "наблюдатель" объект "Goos задачи"
    m_pxGooseEthernet ->
    SetGooseServerObserver(GetGooseServerObserver());
    // передадим указатель на объект "наблюдатель" объект "Goos задачи"
    m_pxGooseEthernet ->
    SetGooseClientObserver(GetGooseClientObserver());
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
    SetFsmState(CGooseEthernet::SERVER_START);
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
    m_pxRteThreadProduction = new CRteThreadProduction();
    // разместим задачу на производственной площадке
    m_pxRteThreadProduction -> Place(m_pxRte);

}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::ClientInit(void)
{
    // создадим объект "Goose задачи"
    m_pxGooseEthernet = new CGooseEthernet();
    // передадим указатель на объект "наблюдатель" объект "Goos задачи"
    m_pxGooseEthernet ->
    SetGooseServerObserver(GetGooseServerObserver());
    // передадим указатель на объект "наблюдатель" объект "Goos задачи"
    m_pxGooseEthernet ->
    SetGooseClientObserver(GetGooseClientObserver());
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
    m_pxGooseEthernet ->
    SetOwnAddress(GetProjectManager() -> GetOwnAddress());
    // установим начальное состояние автомата задачи, режим работы - клиент
    m_pxGooseEthernet ->
    SetFsmState(CGooseEthernet::CLIENT_START);
    // разместим задачу на производственной площадке
    m_pxGooseThreadProduction -> Place(m_pxGooseEthernet);
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Fsm(void)
{
//    return;

    switch (GetFsmState())
    {
    case MAIN_CYCLE_START:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_START"  << std::endl;
        Init();

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
            std::cout << "main default mode server"  << std::endl;
            SetFsmState(MAIN_CYCLE_SERVER_INIT);
        }
        break;

    case MAIN_CYCLE_SERVER_INIT:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_SERVER_INIT"  << std::endl;
        ServerInit();
        usleep(100000);
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_CLIENT_INIT:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_CLIENT_INIT"  << std::endl;
        ClientInit();
        usleep(100000);
        SetFsmState(MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME);
//        SetFsmState(MAIN_CYCLE_IDDLE_STATE_PREPARE);

        break;

    case MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME"  << std::endl;
        if (GetGooseEthernet() ->
                ReportSlaveIDRequest(GetProjectManager() -> GetOwnAddress()))
        {
            SetFsmState(MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME_PERIOD_END_WAITING);
        }
        else
        {
            SetFsmState(MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME_PERIOD_END_WAITING);
        }
        break;

    case MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME_PERIOD_END_WAITING:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME_PERIOD_END_WAITING"  << std::endl;
        usleep(GetGooseEthernet() -> GetPeriodTime());
        SetFsmState(MAIN_CYCLE_IS_TIME_TO_SHOW_STATISTICS);
        break;

    case MAIN_CYCLE_IS_TIME_TO_SHOW_STATISTICS:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IS_TIME_TO_SHOW_STATISTICS"  << std::endl;
        // настало время отобразить статистику?
        if (GetGooseConsoleRepresentationTimer() -> IsOverflow())
        {
            GetGooseConsoleRepresentationTimer() ->
            Set(MAIN_CYCLE_SHOW_STATISTICS_PERIOD_TIME);
            SetFsmState(MAIN_CYCLE_SHOW_STATISTICS);
        }
        else
        {
            SetFsmState(MAIN_CYCLE_SEND_REQUEST_MEASURE_RESPONCE_TIME);
        }
        break;

    case MAIN_CYCLE_SHOW_STATISTICS:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_SHOW_STATISTICS"  << std::endl;
        GetGooseConsoleRepresentation() -> Show();
        SetFsmState(MAIN_CYCLE_IS_TIME_TO_SHOW_STATISTICS);
        break;




    case MAIN_CYCLE_IDDLE_STATE_PREPARE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_IDDLE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_IDDLE"  << std::endl;
        usleep(100000);
        break;

    case MAIN_CYCLE_STOP_STATE_PREPARE:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_STOP_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_STOPED);
        break;

    case MAIN_CYCLE_STOPED:
//        std::cout << "CMainProductionCycle::Fsm MAIN_CYCLE_STOPED"  << std::endl;
        usleep(100000);
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
