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
    virtual void SlaveSet(uint8_t uiSlave) {};

    virtual uint16_t ResponseException(uint8_t uiSlave, uint8_t uiFunctionCode, uint8_t uiExceptionCode, uint8_t *puiResponse) {};
    virtual uint16_t ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength) {};

    virtual void SetOwnAddress(uint32_t uiAddress) {};
    virtual uint32_t GetOwnAddress(void) {};

    virtual void SetServerAddress(uint32_t uiAddress) {};
    virtual uint32_t GetServerAddress(void) {};

    virtual void SetMagicCode(uint32_t uiMagicCode) {};
    virtual uint32_t GetMagicCode(void) {};

    virtual void SetMessageLength(uint16_t uiLength) {};
    virtual uint16_t GetMessageLength(void) {};

    virtual CEthernetCommunicationDevice* GetCommunicationDevice(void) {};

    virtual uint16_t HEADER_LENGTH(void) {};

private:
    virtual uint16_t RequestProcessing(uint8_t *puiRequest,
                                       uint8_t *puiResponse,
                                       uint16_t uiFrameLength) {};
    virtual uint16_t AnswerProcessing(uint8_t *puiResponse,
                                      uint16_t uiFrameLength) {};
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

    };

    CGoose();
    virtual ~CGoose();

    void SlaveSet(uint8_t uiSlave);
    uint16_t ResponseException(uint8_t uiSlave, uint8_t uiFunctionCode, uint8_t uiExceptionCode, uint8_t *puiResponse);
    uint16_t ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength);
    uint16_t RequestProcessing(uint8_t *puiRequest,
                               uint8_t *puiResponse,
                               uint16_t uiFrameLength);
    uint16_t AnswerProcessing(uint8_t *puiResponse,
                              uint16_t uiFrameLength);

public:
    void SetOwnAddress(uint32_t uiAddress)
    {
        m_uiOwnAddress = uiAddress;
    };
    uint32_t GetOwnAddress(void)
    {
        return m_uiOwnAddress;
    };

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

//-----------------------------------------------------------------------------------------
private:
    uint32_t m_uiOwnAddress;
    uint32_t m_uiServerAddress;
    uint32_t m_uiMagicCode;
    uint16_t m_uiMessageLength;

};

//-----------------------------------------------------------------------------------------
#endif // CGOOSE_H
