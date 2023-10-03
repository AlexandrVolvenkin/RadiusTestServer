#ifndef CGOOSE_H
#define CGOOSE_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

#include "Platform.h"
#include "Task.h"
#include "Observer.h"

//-----------------------------------------------------------------------------------------
class CGooseInterface : public CTask
{
public:
    virtual void WorkingArraysInit(uint8_t *puiCoils,
                                   uint8_t *puiDiscreteInputs,
                                   uint16_t *pui16HoldingRegisters,
                                   uint16_t *pui16InputRegisters,
                                   uint16_t uiCoilsNumber,
                                   uint16_t uiDiscreteInputsNumber,
                                   uint16_t uiHoldingRegistersNumber,
                                   uint16_t uiInputRegistersNumber) {};
//    virtual void SlaveSet(uint8_t uiSlave) {};
    virtual uint16_t SetHeader(uint8_t *puiResponse) {};
    virtual int8_t MessengerIsReady(void) {};

    virtual uint16_t RequestBasis(uint8_t uiSlave,
                                  uint8_t uiFunctionCode,
                                  uint8_t *puiRequest) {};
//    virtual uint16_t RequestBasis(uint8_t uiSlave,
//                                  uint8_t uiFunctionCode,
//                                  uint16_t uiAddress,
//                                  uint16_t uiBitNumber,
//                                  uint8_t *puiRequest) {};
    virtual uint16_t ResponseBasis(uint8_t uiSlave,
                                   uint8_t uiFunctionCode,
                                   uint8_t *puiResponse) {};
    virtual uint16_t ResponseException(uint8_t uiSlave,
                                       uint8_t uiFunctionCode,
                                       uint8_t uiExceptionCode,
                                       uint8_t *puiResponse) {};

    virtual uint16_t ReadHoldingRegisters(uint8_t *puiRequest,
                                          uint8_t *puiResponse,
                                          uint16_t uiLength) {};
    virtual uint16_t ReportSlaveID(uint8_t *puiRequest,
                                   uint8_t *puiResponse,
                                   uint16_t uiLength) {};


    virtual void SetOwnAddress(uint8_t uiAddress) {};
    virtual uint8_t GetOwnAddress(void) {};
//    virtual void SetOwnAddress(uint32_t uiAddress) {};
//    virtual uint32_t GetOwnAddress(void) {};

    virtual void SetServerAddress(uint32_t uiAddress) {};
    virtual uint32_t GetServerAddress(void) {};

    virtual void SetMagicCode(uint32_t uiMagicCode) {};
    virtual uint32_t GetMagicCode(void) {};

    virtual void SetMessageLength(uint16_t uiLength) {};
    virtual uint16_t GetMessageLength(void) {};

    virtual void SetAttemptNumber(uint32_t uiAttemptNumber) {};
    virtual uint32_t GetAttemptNumber(void) {};

    virtual CEthernetCommunicationDevice* GetCommunicationDevice(void) {};

    virtual void SetGooseServerObserver(CGooseServerObserver* pxPointer) {};
    virtual CGooseServerObserver* GetGooseServerObserver(void) {};

    virtual void SetGooseClientObserver(CGooseClientObserver* pxPointer) {};
    virtual CGooseClientObserver* GetGooseClientObserver(void) {};

    virtual void SetPeriodTime(uint32_t uiValue) {};
    virtual uint32_t GetPeriodTime(void) {};

    virtual CTimer* GetTimerPointer(void) {};

    virtual uint8_t* GetRxBuffer(void) {};
    virtual uint8_t* GetTxBuffer(void) {};

    virtual uint16_t HEADER_LENGTH(void) {};

    virtual uint16_t RequestProcessing(uint8_t *puiRequest,
                                       uint8_t *puiResponse,
                                       uint16_t uiFrameLength) {};
    virtual uint16_t AnswerProcessing(uint8_t *puiResponse,
                                      uint16_t uiFrameLength) {};

//-----------------------------------------------------------------------------------------
// Client
    virtual int8_t ReportSlaveIDRequest(uint8_t uiSlaveAddress) {};
    virtual uint16_t ReportSlaveIDReceive(uint8_t *puiMessage,
                                          uint16_t uiLength) {};

    virtual int8_t ReadHoldingRegistersRequest(uint8_t uiSlaveAddress,
            uint16_t uiAddress,
            uint16_t uiNumber,
            uint16_t* puiDestination) {};
    virtual uint16_t ReadHoldingRegistersReceive(uint8_t *puiMessage,
            uint16_t uiLength) {};
};

//-----------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------
class CGoose : public CGooseInterface
{
public:
    enum
    {
//        OWN_ADDRESS_OFFSET = 0,
//        OWN_ADDRESS_OFFSET = 0,
        PING_ATTEMPTS_NUMBER = 100000,

    };

    enum
    {
        IDDLE  = 0,
        START,
//-----------------------------------------------------------------------------------------
// GooseServer
        SERVER_START,
        SERVER_DATA_RECEIVE_PREPARE,
        SERVER_DATA_RECEIVE_WAITING,
        SERVER_RECEIVED_DATA_PROCESSING,
        SERVER_RECEIVED_DATA_ERROR_PROCESSING,
        SERVER_DATA_TRANSMIT_PREPARE,
        SERVER_DATA_TRANSMIT,
        SERVER_IDDLE_STATE_PREPARE,
        SERVER_IDDLE,
        SERVER_STOP_STATE_PREPARE,
        SERVER_STOPED,

//-----------------------------------------------------------------------------------------
// GooseClient
        CLIENT_START,
        CLIENT_DATA_RECEIVE_PREPARE,
        CLIENT_DATA_RECEIVE_WAITING,
        CLIENT_RECEIVED_DATA_PROCESSING,
        CLIENT_RECEIVED_DATA_ERROR_PROCESSING,
        CLIENT_DATA_TRANSMIT_PREPARE,
        CLIENT_DATA_TRANSMIT,
        CLIENT_IDDLE_STATE_PREPARE,
        CLIENT_IDDLE,
        CLIENT_STOP_STATE_PREPARE,
        CLIENT_STOPED,

    };

    CGoose();
    virtual ~CGoose();

//    void SlaveSet(uint8_t uiSlave);
    uint16_t ResponseException(uint8_t uiSlave,
                               uint8_t uiFunctionCode,
                               uint8_t uiExceptionCode,
                               uint8_t *puiResponse);

    uint16_t ReadHoldingRegisters(uint8_t *puiRequest,
                                  uint8_t *puiResponse,
                                  uint16_t uiLength);
    uint16_t ReportSlaveID(uint8_t *puiRequest,
                           uint8_t *puiResponse,
                           uint16_t uiLength);
    uint16_t RequestProcessing(uint8_t *puiRequest,
                               uint8_t *puiResponse,
                               uint16_t uiFrameLength);
    uint16_t AnswerProcessing(uint8_t *puiResponse,
                              uint16_t uiFrameLength);


//-----------------------------------------------------------------------------------------
// Client
    int8_t ReportSlaveIDRequest(uint8_t uiSlaveAddress);
    uint16_t ReportSlaveIDReceive(uint8_t *puiMessage,
                                  uint16_t uiLength);

    int8_t ReadDiscreteInputsRequest(uint8_t uiSlaveAddress,
                                     uint16_t uiAddress,
                                     uint16_t uiBitNumber);
    uint16_t ReadDiscreteInputsReceive(uint8_t *puiMessage,
                                       uint16_t uiLength);

    int8_t ReadHoldingRegistersRequest(uint8_t uiSlaveAddress,
                                       uint16_t uiAddress,
                                       uint16_t uiNumber,
                                       uint16_t* puiDestination);
    uint16_t ReadHoldingRegistersReceive(uint8_t *puiMessage,
                                         uint16_t uiLength);

public:
//    uint8_t* GetRxBuffer(void)
//    {
//        return m_puiRxBuffer;
//    };
//
//    uint8_t* GetTxBuffer(void)
//    {
//        return m_puiTxBuffer;
//    };

    void SetOwnAddress(uint8_t uiAddress)
    {
        m_uiOwnAddress = uiAddress;
    };
    uint8_t GetOwnAddress(void)
    {
        return m_uiOwnAddress;
    };
//    void SetOwnAddress(uint32_t uiAddress)
//    {
//        m_uiOwnAddress = uiAddress;
//    };
//    uint32_t GetOwnAddress(void)
//    {
//        return m_uiOwnAddress;
//    };

    void SetServerAddress(uint32_t uiAddress)
    {
        m_uiServerAddress = uiAddress;
    };
    uint32_t GetServerAddress(void)
    {
        return m_uiServerAddress;
    };

    void SetMagicCode(uint32_t uiMagicCode)
    {
        m_uiMagicCode = uiMagicCode;
    };
    uint32_t GetMagicCode(void)
    {
        return m_uiMagicCode;
    };

    void SetMessageLength(uint16_t uiLength)
    {
        m_uiMessageLength = uiLength;
    };
    uint16_t GetMessageLength(void)
    {
        return m_uiMessageLength;
    };

    void SetAttemptNumber(uint32_t uiAttemptNumber)
    {
        m_uiAttemptNumber = uiAttemptNumber;
    };
    uint32_t GetAttemptNumber(void)
    {
        return m_uiAttemptNumber;
    };

    CGooseServerObserver* GetGooseServerObserver(void)
    {
        return m_pxGooseServerObserver;
    };
    void SetGooseServerObserver(CGooseServerObserver* pxPointer)
    {
        m_pxGooseServerObserver = pxPointer;
    };

    void SetGooseClientObserver(CGooseClientObserver* pxPointer)
    {
        m_pxGooseClientObserver = pxPointer;
    };
    CGooseClientObserver* GetGooseClientObserver(void)
    {
        return m_pxGooseClientObserver;
    };

    void SetPeriodTime(uint32_t uiValue)
    {
        m_uiPeriodTime = uiValue;
    };
    uint32_t GetPeriodTime(void)
    {
        return m_uiPeriodTime;
    };

//-----------------------------------------------------------------------------------------
private:
//    uint8_t* m_puiRxBuffer;
//    uint8_t* m_puiTxBuffer;

    uint8_t m_uiOwnAddress;
    uint8_t m_uiSlaveAddress;
    uint8_t m_uiFunctionCode;
    uint16_t* m_pui8Destination;
    uint16_t* m_pui16Destination;
    uint16_t m_uiAttemptNumber;
    uint32_t m_uiPeriodTime;

//    uint32_t m_uiOwnAddress;
    uint32_t m_uiServerAddress;
    uint32_t m_uiMagicCode;
    uint16_t m_uiMessageLength;

    CGooseServerObserver* m_pxGooseServerObserver;
    CGooseClientObserver* m_pxGooseClientObserver;

public:
    uint8_t *m_puiCoils;
    uint8_t *m_puiDiscreteInputs;
    uint16_t *m_pui16HoldingRegisters;
    uint16_t *m_pui16InputRegisters;
    uint16_t m_uiCoilsNumber;
    uint16_t m_uiDiscreteInputsNumber;
    uint16_t m_uiHoldingRegistersNumber;
    uint16_t m_uiInputRegistersNumber;

};

//-----------------------------------------------------------------------------------------
#endif // CGOOSE_H
