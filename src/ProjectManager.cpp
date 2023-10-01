//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "ProjectManager.h"

//-----------------------------------------------------------------------------------------
CProjectManager::CProjectManager()
{
    //ctor
}

//-----------------------------------------------------------------------------------------
CProjectManager::~CProjectManager()
{
    //dtor
}

////-----------------------------------------------------------------------------------------
//uint8_t CProjectManager::GetOrder(void)
//{
//    m_pccMode = GetCommantLineArgumentCustomer() -> GetMode();
//    m_pccGooseInterfaceName = GetCommantLineArgumentCustomer() -> GetGooseInterfaceName();
//    m_pccEthernetAddress = GetCommantLineArgumentCustomer() -> GetEthernetAddress();
//    m_pccCommInterfaceName = GetCommantLineArgumentCustomer() -> GetCommInterfaceName();
//    m_uiCalculationPeriodTime = GetCommantLineArgumentCustomer() -> GetCalculationPeriodTime();
//    m_uiLoadPercent = GetCommantLineArgumentCustomer() -> GetLoadPercent();
//}

//-----------------------------------------------------------------------------------------
uint8_t CProjectManager::GetOrder(CCommantLineArgumentCustomer* pxCommantLineArgumentCustomer)
{
    m_pccMode = pxCommantLineArgumentCustomer -> GetMode();
    m_pccGooseInterfaceName = pxCommantLineArgumentCustomer -> GetGooseInterfaceName();
    m_pccEthernetAddress = pxCommantLineArgumentCustomer -> GetEthernetAddress();
    m_pccCommInterfaceName = pxCommantLineArgumentCustomer -> GetCommInterfaceName();
    m_uiCalculationPeriodTime = pxCommantLineArgumentCustomer -> GetCalculationPeriodTime();
    m_uiLoadPercent = pxCommantLineArgumentCustomer -> GetLoadPercent();
}
