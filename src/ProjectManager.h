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
class CProjectManager// : CProjectManagerInterface
{
public:
    CProjectManager();
    virtual ~CProjectManager();
    //    uint8_t GetOrder(void);
    uint8_t GetOrder(CCommantLineArgumentCustomer* pxCommantLineArgumentCustomer);

    void SetCommantLineArgumentCustomer(CCommantLineArgumentCustomer* pxCommantLineArgumentCustomer)
    {
        m_pxCommantLineArgumentCustomer = pxCommantLineArgumentCustomer;
    }
    CCommantLineArgumentCustomer* GetCommantLineArgumentCustomer(void)
    {
        return m_pxCommantLineArgumentCustomer;
    }

private:
    const char* m_pccMode;
    const char* m_pccGooseInterfaceName;
    const char* m_pccEthernetAddress;
    const char* m_pccCommInterfaceName;
    uint32_t m_uiCalculationPeriodTime;
    uint8_t m_uiLoadPercent;

    CCommantLineArgumentCustomer* m_pxCommantLineArgumentCustomer;
};

//-----------------------------------------------------------------------------------------








////-----------------------------------------------------------------------------------------
//class CProjectManager : CProjectManagerInterface
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
