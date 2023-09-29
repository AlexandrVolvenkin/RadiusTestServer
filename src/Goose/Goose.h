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



/* Function codes */
#define _FC_READ_COILS                0x01
#define _FC_READ_DISCRETE_INPUTS      0x02
#define _FC_READ_HOLDING_REGISTERS    0x03
#define _FC_READ_INPUT_REGISTERS      0x04
#define _FC_WRITE_SINGLE_COIL         0x05
#define _FC_WRITE_SINGLE_REGISTER     0x06
#define _FC_READ_EXCEPTION_STATUS     0x07
#define _FC_WRITE_MULTIPLE_COILS      0x0F
#define _FC_WRITE_MULTIPLE_REGISTERS  0x10
#define _FC_REPORT_SLAVE_ID           0x11
#define _FC_WRITE_AND_READ_REGISTERS  0x17

#define _FC_PROGRAMMING_COMPLETION_REQUEST  0x0E
#define _FC_CONFIGURATION_REQUEST  0x11
#define _FC_DATA_BASE_ARCHIVE_BLOCK_READ  0x43
#define _FC_DATA_BASE_READ  0x44
#define _FC_DATA_BASE_WRITE  0x45
#define _FC_TIME_SET  0x46
#define _FC_ONLINE_DATA_READ  0x47

#define _FC_PROGRAMMING 0x46
#define _FC_WRITE_DATA  0x41
#define _FC_READ_DATA  0x42
#define _FC_DATA_EXCHANGE  0x41

/* Protocol exceptions */
typedef enum
{
    MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
    MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
    MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
    MODBUS_EXCEPTION_ACKNOWLEDGE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
    MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
    MODBUS_EXCEPTION_MEMORY_PARITY,
    MODBUS_EXCEPTION_NOT_DEFINED,
    MODBUS_EXCEPTION_GATEWAY_PATH,
    MODBUS_EXCEPTION_GATEWAY_TARGET,
    MODBUS_EXCEPTION_MAX
};

//-----------------------------------------------------------------------------------------
class CGooseInterface : public CTask
{
public:
//    virtual void SlaveSet(uint8_t uiSlave) {};
    virtual uint16_t SetHeader(uint8_t *puiResponse) {};
    virtual int8_t MessengerIsReady(void) {};

    virtual uint16_t RequestBasis(uint8_t uiSlave,
                                  uint8_t uiFunctionCode,
                                  uint8_t *puiRequest) {};
    virtual uint16_t ResponseBasis(uint8_t uiSlave,
                                   uint8_t uiFunctionCode,
                                   uint8_t *puiResponse) {};
    virtual uint16_t ResponseException(uint8_t uiSlave,
                                       uint8_t uiFunctionCode,
                                       uint8_t uiExceptionCode,
                                       uint8_t *puiResponse) {};
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

    virtual CGooseServerObserver* GetGooseServerObserver(void) {};
    virtual void SetGooseServerObserver(CGooseServerObserver* pxPointer) {};

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
        REQUEST_ENABLE,
        WAITING_ACCEPT,
        START_REQUEST,
        WAITING_MESSAGE_REQUEST,
        RECEIVE_MESSAGE_REQUEST,
        REQUEST_PROCESSING_REQUEST,
        FRAME_TRANSMIT_CONFIRMATION,
        WAITING_FRAME_TRANSMIT_CONFIRMATION,
        END_WAITING_FRAME_TRANSMIT_CONFIRMATION,
        STOP_REQUEST,
        REQUEST_ERROR,

//-----------------------------------------------------------------------------------------
// GooseClient
        CONFIRMATION_ENABLE,
        WAITING_CONNECT,
        START_CONFIRMATION,
        WAITING_MESSAGE_CONFIRMATION,
        RECEIVE_MESSAGE_CONFIRMATION,
        ANSWER_PROCESSING_CONFIRMATION,
        FRAME_TRANSMIT_REQUEST,
        WAITING_FRAME_TRANSMIT_REQUEST,
        END_WAITING_FRAME_TRANSMIT_REQUEST,
        STOP_CONFIRMATION,
        CONFIRMATION_ERROR,

        RESTART,
    };

    CGoose();
    virtual ~CGoose();

//    void SlaveSet(uint8_t uiSlave);
    uint16_t ResponseException(uint8_t uiSlave,
                               uint8_t uiFunctionCode,
                               uint8_t uiExceptionCode,
                               uint8_t *puiResponse);
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

public:
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
    uint8_t m_uiOwnAddress;
    uint8_t m_uiSlaveAddress;
    uint8_t m_uiFunctionCode;
    uint16_t m_uiAttemptNumber;
    uint32_t m_uiPeriodTime;

//    uint32_t m_uiOwnAddress;
    uint32_t m_uiServerAddress;
    uint32_t m_uiMagicCode;
    uint16_t m_uiMessageLength;

    CGooseServerObserver* m_pxGooseServerObserver;

};

//-----------------------------------------------------------------------------------------
#endif // CGOOSE_H
