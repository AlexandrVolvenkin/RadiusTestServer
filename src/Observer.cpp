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
}

//-----------------------------------------------------------------------------------------
void CGooseServerObserver::CalculateLostPacketNumber(uint16_t uiIndex)
{
    SetLostPacketNumber(GetLostPacketNumber() +
                        ((uiIndex - 1) - GetLastReceivedPacketIndex()));
}

//-----------------------------------------------------------------------------------------
