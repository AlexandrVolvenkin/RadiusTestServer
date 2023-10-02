#ifndef CCUSTOMER_H
#define CCUSTOMER_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

//-----------------------------------------------------------------------------------------
class CCustomerInterface
{
public:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CCustomer : public CCustomerInterface
{
public:
    CCustomer();
    virtual ~CCustomer();

protected:

private:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CCommantLineArgumentCustomer// : public CCustomer
{
public:
    CCommantLineArgumentCustomer();
    virtual ~CCommantLineArgumentCustomer();
    void Init(void);
    uint8_t GetOrder(int argc, char** argv);

    void SetMode(const char* pccMode)
    {
        m_pccMode = pccMode;
    };
    const char* GetMode(void)
    {
        return m_pccMode;
    };

    void SetGooseInterfaceName(const char* pccGooseInterfaceName)
    {
        m_pccGooseInterfaceName = pccGooseInterfaceName;
    };
    const char* GetGooseInterfaceName(void)
    {
        return m_pccGooseInterfaceName;
    };

    void SetEthernetAddress(const char* pccEthernetAddress)
    {
        m_pccEthernetAddress = pccEthernetAddress;
    };
    const char* GetEthernetAddress(void)
    {
        return m_pccEthernetAddress;
    };

    void SetCommInterfaceName(const char* pccCommInterfaceName)
    {
        m_pccCommInterfaceName = pccCommInterfaceName;
    };
    const char* GetCommInterfaceName(void)
    {
        return m_pccCommInterfaceName;
    };

    void SetCalculationPeriodTime(uint32_t uiData)
    {
        m_uiCalculationPeriodTime = uiData;
    };
    uint32_t GetCalculationPeriodTime(void)
    {
        return m_uiCalculationPeriodTime;
    };

    void SetLoadPercent(uint8_t uiData)
    {
        m_uiLoadPercent = uiData;
    };
    uint8_t GetLoadPercent(void)
    {
        return m_uiLoadPercent;
    };

    void SetOwnAddress(uint8_t uiData)
    {
        m_uiOwnAddress = uiData;
    };
    uint8_t GetOwnAddress(void)
    {
        return m_uiOwnAddress;
    };

private:
    const char* m_pccMode;
    const char* m_pccGooseInterfaceName;
    const char* m_pccEthernetAddress;
    const char* m_pccCommInterfaceName;
    uint32_t m_uiCalculationPeriodTime;
    uint8_t m_uiLoadPercent;
    uint8_t m_uiOwnAddress;


};

//-----------------------------------------------------------------------------------------

#endif // CCUSTOMER_H
