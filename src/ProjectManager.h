#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

#include "Customer.h"

//-----------------------------------------------------------------------------------------
class CProjectManagerInterface
{
public:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CProjectManager// : public CProjectManagerInterface
{
public:
    CProjectManager();
    virtual ~CProjectManager();
    //    uint8_t GetOrder(void);
    uint8_t GetOrder(CCommantLineArgumentCustomer* pxCommantLineArgumentCustomer);

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

    void SetCommantLineArgumentCustomer(CCommantLineArgumentCustomer* pxCommantLineArgumentCustomer)
    {
        m_pxCommantLineArgumentCustomer = pxCommantLineArgumentCustomer;
    };
    CCommantLineArgumentCustomer* GetCommantLineArgumentCustomer(void)
    {
        return m_pxCommantLineArgumentCustomer;
    };

private:
    const char* m_pccMode;
    const char* m_pccGooseInterfaceName;
    const char* m_pccEthernetAddress;
    const char* m_pccCommInterfaceName;
    uint32_t m_uiCalculationPeriodTime;
    uint8_t m_uiLoadPercent;
    uint8_t m_uiOwnAddress;

    CCommantLineArgumentCustomer* m_pxCommantLineArgumentCustomer;
};

//-----------------------------------------------------------------------------------------








////-----------------------------------------------------------------------------------------
//class CProjectManager : public CProjectManagerInterface
//{
//    public:
//        CProjectManager();
//        virtual ~CProjectManager();
//
//    protected:
//
//    private:
//};
//
////-----------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------
#endif // CPROJECTMANAGER_H
