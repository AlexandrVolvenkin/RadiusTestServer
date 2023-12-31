//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Observer.h"
#include "Platform.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
CObserver::CObserver()
{

}

//-----------------------------------------------------------------------------------------
CObserver::~CObserver()
{

}
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CGooseServerObserver::CGooseServerObserver()
{
//    std::cout << "CGooseServerObserver constructor"  << std::endl;
    m_uiTransmitPacketNumber = 0;
    m_uiReceivePacketNumber = 0;
    m_uiLostPacketNumber = 0;

    m_uiMinReceivePacketTimeout = 1000000000;
    m_uiMaxReceivePacketTimeout = 0;
    m_uiAverageReceivePacketTimeout = 0;
    m_uiCommonReceivePacketTimeout = 0;
    m_uiCommonReceivePacketNumber = 0;
    m_uiCommonStatisticsOutCounter = 0;
}

//-----------------------------------------------------------------------------------------
CGooseServerObserver::~CGooseServerObserver()
{
//    std::cout << "CGooseServerObserver destructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
void CGooseServerObserver::Reset(void)
{
    m_uiTransmitPacketNumber = 0;
    m_uiReceivePacketNumber = 0;
    m_uiLostPacketNumber = 0;

    m_uiMinReceivePacketTimeout = 1000000000;
    m_uiMaxReceivePacketTimeout = 0;
    m_uiAverageReceivePacketTimeout = 0;
    m_uiCommonReceivePacketTimeout = 0;
    m_uiCommonReceivePacketNumber = 0;
    m_uiCommonStatisticsOutCounter = 0;
}

//-----------------------------------------------------------------------------------------
void CGooseServerObserver::CalculateLostPacketNumber(uint16_t uiIndex)
{
    SetLostPacketNumber(GetLostPacketNumber() +
                        ((uint16_t)(uiIndex - 1) - (uint16_t)GetLastReceivedPacketIndex()));
}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CGooseClientObserver::CGooseClientObserver()
{
//    std::cout << "CGooseClientObserver constructor"  << std::endl;
    SetTransmitPacketNumber(0);
    SetReceivePacketNumber(0);
    SetLostPacketNumber(0);

    SetMinReceivePacketTimeout(1000000000);
    SetMaxReceivePacketTimeout(0);
    SetAverageReceivePacketTimeout(0);
    SetCommonReceivePacketTimeout(0);
    SetCommonReceivePacketNumber(0);
    SetCommonStatisticsOutCounter(0);
}

//-----------------------------------------------------------------------------------------
CGooseClientObserver::~CGooseClientObserver()
{
//    std::cout << "CGooseClientObserver destructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
