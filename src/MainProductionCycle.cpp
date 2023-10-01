
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <iostream>
#include <string.h>

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
}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Init(void)
{
//    // создадим объект "Goose задачи"
//    m_pxGooseEthernet = new CGooseEthernet();
//    // создадим и добавим объект "наблюдатель"
//    m_pxGooseEthernet -> SetGooseServerObserver(new CGooseServerObserver());
//    // установим имя интерфейса
//    m_pxGooseEthernet -> GetCommunicationDevice() -> SetPortName(pccGooseInterfaceName);
//    // установим mac адрес назначения
//    m_pxGooseEthernet -> GetCommunicationDevice() -> SetDestinationMacAddress(ether_aton(pccEthernetAddress) -> ether_addr_octet);
//    // установим период
//    m_pxGooseEthernet -> SetPeriodTime(uiCalculationPeriodTime);
//    // установим период вывода статистики
//    m_pxGooseEthernet -> GetTimerPointer() -> Set(1000);
//
//    m_pxGooseEthernet -> WorkingArraysInit(m_aucRtuCoilsArray,
//                                         m_aucRtuDiscreteInputsArray,
//                                         m_aucRtuHoldingRegistersArray,
//                                         m_aucRtuInputRegistersArray,
//                                         COILS_WORK_ARRAY_LENGTH,
//                                         DISCRETE_INPUTS_ARRAY_LENGTH,
//                                         HOLDING_REGISTERS_ARRAY_LENGTH,
//                                         INPUT_REGISTERS_ARRAY_LENGTH
//                                        );
//    // создадим объект "производственная площадка Goose задачи"
//    m_pxGooseThreadProduction = new CGooseThreadProduction();

}

//-----------------------------------------------------------------------------------------
void CMainProductionCycle::Fsm(void)
{
    switch (GetFsmState())
    {
    case MAIN_CYCLE_START:
//        std::cout << "CGooseEthernet::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        // установим начальное состояние автомата задачи, режим работы - клиент
        m_pxGooseEthernet -> SetFsmState(CGooseEthernet::CLIENT_START);
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_IDDLE_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm MAIN_CYCLE_IDDLE_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_IDDLE);
        break;

    case MAIN_CYCLE_IDDLE:
//        std::cout << "CGooseEthernet::Fsm MAIN_CYCLE_IDDLE"  << std::endl;
        break;

    case MAIN_CYCLE_STOP_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm MAIN_CYCLE_STOP_STATE_PREPARE"  << std::endl;
        SetFsmState(MAIN_CYCLE_STOPED);
        break;

    case MAIN_CYCLE_STOPED:
//        std::cout << "CGooseEthernet::Fsm MAIN_CYCLE_STOPED"  << std::endl;
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
