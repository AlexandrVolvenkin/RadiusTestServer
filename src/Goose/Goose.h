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

//-----------------------------------------------------------------------------------------
class CGooseInterface : public CTask
{
public:
    virtual void SlaveSet(uint8_t uiSlave) {};

    virtual void SetOwnAddress(uint32_t uiAddress) {};
    virtual uint32_t GetOwnAddress(void) {};

    virtual void SetServerAddress(uint32_t uiAddress) {};
    virtual uint32_t GetServerAddress(void) {};

    virtual void SetMagicCode(uint32_t uiMagicCode) {};
    virtual uint32_t GetMagicCode(void) {};

    virtual void SetMessageLength(uint16_t uiLength) {};
    virtual uint16_t GetMessageLength(void) {};

    virtual CEthernetCommunicationDevice* GetCommunicationDevice(void) {};

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
