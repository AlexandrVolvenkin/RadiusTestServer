#ifndef CGOOSEETHERNET_H
#define CGOOSEETHERNET_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

#include "Platform.h"
#include "Goose.h"

//-----------------------------------------------------------------------------------------
class CGooseEthernetInterface
{
public:

};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseEthernet : public CGoose
{
public:
    enum
    {
        GOOSE_ETHERNET_MAX_FRAME_LENGTH = 1024,
    };

    CGooseEthernet();
    virtual ~CGooseEthernet();


private:

    CEthernetCommunicationDevice* m_pxCommunicationDevice;
    uint16_t m_uiRequestTransactionId = 0;
    uint16_t m_uiResponseTransactionId = 0;
    // таймоут по отсутствию запроса.
    const static uint16_t m_uiReceiveTimeout = 15000;
    // таймоут по отсутствию подтверждения.
    const static uint16_t m_uiConfirmationTimeout = 500;
    const static uint16_t m_uiTransmitDelayTimeout = 5;

    uint8_t* m_puiRxBuffer;
    uint8_t* m_puiTxBuffer;

};

//-----------------------------------------------------------------------------------------
#endif // CGOOSEETHERNET_H
