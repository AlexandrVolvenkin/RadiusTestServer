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

//-----------------------------------------------------------------------------------------
class CGooseInterface
{
public:
    virtual void Fsm(void);

};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGoose
{
public:
    enum
    {
//        OWN_ADDRESS_OFFSET = 0,
//        OWN_ADDRESS_OFFSET = 0,

    };

    CGoose();
    virtual ~CGoose();

//-----------------------------------------------------------------------------------------
public:
    virtual void SetOwnAddress(uint32_t uiAddress)
    {
        m_uiOwnAddress = uiAddress;
    };
    virtual uint32_t GetOwnAddress(void)
    {
        return m_uiOwnAddress;
    };

    virtual void SetServerAddress(uint32_t uiAddress)
    {
        m_uiServerAddress = uiAddress;
    };
    virtual uint32_t GetServerAddress(void)
    {
        return m_uiServerAddress;
    };

    virtual void SetMagicCode(uint32_t uiMagicCode)
    {
        m_uiMagicCode = uiMagicCode;
    };
    virtual uint32_t GetMagicCode(void)
    {
        return m_uiMagicCode;
    };

    virtual void SetMessageLength(uint16_t uiLength)
    {
        m_uiMessageLength = uiLength;
    };
    virtual uint16_t GetMessageLength(void)
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
