//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "GooseEthernet.h"

//-----------------------------------------------------------------------------------------
CGooseEthernet::CGooseEthernet()
{
    m_pxCommunicationDevice = new CEthernetCommunicationDevice();
    m_puiRxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    m_puiTxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
//    SetFsmState(IDDLE);
}

//-----------------------------------------------------------------------------------------
CGooseEthernet::~CGooseEthernet()
{
    delete[] m_puiTxBuffer;
    delete[] m_puiRxBuffer;
    delete m_pxCommunicationDevice;
}
