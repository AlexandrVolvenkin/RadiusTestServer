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
#include "Production.h"
#include "Timer.h"
#include "Goose.h"

//-----------------------------------------------------------------------------------------
class CGooseEthernetInterface : public CGoose
{
public:

//    virtual uint16_t MIN_MESSAGE_LENGTH(void) {};
//    virtual void CommunicationDeviceInit(const char* pccIpAddress,
//                                 uint16_t uiPort) {};
//    virtual void ReceiveEnable(void) {};
//    virtual void ReceiveDisable(void) {};
//    virtual void TransmitEnable(void) {};
//    virtual void TransmitDisable(void) {};
//    virtual uint16_t Send(uint8_t* puiDestination, uint16_t uiLength) {};
//    virtual int16_t Receive(uint8_t* puiSource, uint16_t uiLength) {};
////    uint16_t GetFrameLength(void) {};
//    virtual int8_t FrameCheck(uint8_t * , uint16_t ) {};
//    virtual bool IsDataWrited(void) {};
//    virtual int8_t MessengerIsReady(void) {};

};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseEthernet : public CGooseEthernetInterface
{
public:
    enum
    {
        GOOSE_ETHERNET_MAX_FRAME_LENGTH = 1024,
//        GOOSE_ETHERNET_HEADER_LENGTH = 0,
//        GOOSE_ETHERNET_PRESET_REQ_LENGTH = 0,
//        GOOSE_ETHERNET_PRESET_RSP_LENGTH = 0,
//        GOOSE_ETHERNET__CHECKSUM_LENGTH = 0,
    };

    uint16_t MIN_MESSAGE_LENGTH(void)
    {
        return 4;
    };

    uint16_t HEADER_LENGTH(void)
    {
        // два байта - номер пакета и один адрес слейва
        return sizeof(struct ether_header) + 3;
    };

    CGooseEthernet();
    virtual ~CGooseEthernet();

    void Fsm(void);

private:
    void CommunicationDeviceInit(const char* pccIpAddress,
                                 uint16_t uiPort);
    void WorkingArraysInit(uint8_t *puiCoils,
                           uint8_t *puiDiscreteInputs,
                           uint16_t *pui16HoldingRegisters,
                           uint16_t *pui16InputRegisters,
                           uint16_t uiCoilsNumber,
                           uint16_t uiDiscreteInputsNumber,
                           uint16_t uiHoldingRegistersNumber,
                           uint16_t uiInputRegistersNumber);
    void ReceiveEnable(void);
    void ReceiveDisable(void);
    void TransmitEnable(void);
    void TransmitDisable(void);
    uint16_t CheckHeader(uint8_t *puiRequest);
    uint16_t SetHeader(uint8_t *puiResponse);
    uint16_t RequestBasis(uint8_t uiSlave,
                          uint8_t uiFunctionCode,
                          uint8_t *puiRequest);
//    uint16_t RequestBasis(uint8_t uiSlave,
//                          uint8_t uiFunctionCode,
//                          uint16_t uiAddress,
//                          uint16_t uiBitNumber,
//                          uint8_t *puiRequest);
    uint16_t ResponseBasis(uint8_t uiSlave,
                           uint8_t uiFunctionCode,
                           uint8_t *puiResponse);
    uint16_t Send(uint8_t* puiDestination, uint16_t uiLength);
    int16_t Receive(uint8_t* puiSource, uint16_t uiLength);
//    uint16_t GetFrameLength(void);
    int8_t FrameCheck(uint8_t *, uint16_t );

    bool IsDataWrited(void)
    {
        return m_pxCommunicationDevice -> IsDataWrited();
    };
    int8_t MessengerIsReady(void);

    CTimer* GetTimerPointer(void)
    {
        return &m_xTimer;
    };

    CEthernetCommunicationDevice* GetCommunicationDevice(void)
    {
        return m_pxCommunicationDevice;
    };

    uint8_t* GetRxBuffer(void)
    {
        return m_puiRxBuffer;
    };

    uint8_t* GetTxBuffer(void)
    {
        return m_puiTxBuffer;
    };


    void SetProductionSite(CProductionInterface* pxProductionSite)
    {
        m_pxProductionSite = pxProductionSite;
    };
    CProductionInterface* GetProductionSite(void)
    {
        return m_pxProductionSite;
    };

    void Sleep(void);
    void Wakeup(void);

private:
    // указатель на объект "производственная площадка задачи"
    CProductionInterface* m_pxProductionSite;
    uint8_t* m_puiRxBuffer;
    uint8_t* m_puiTxBuffer;

    CEthernetCommunicationDevice* m_pxCommunicationDevice;
    uint16_t m_uiRequestTransactionId = 0;
    uint16_t m_uiResponseTransactionId = 0;
    CTimer m_xTimer;
    // таймоут по отсутствию запроса.
    const static uint16_t m_uiReceiveTimeout = 15000;
    // таймоут по отсутствию подтверждения.
    const static uint16_t m_uiConfirmationTimeout = 500;
    const static uint16_t m_uiTransmitDelayTimeout = 5;

};

//-----------------------------------------------------------------------------------------
#endif // CGOOSEETHERNET_H
