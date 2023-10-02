//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Platform.h"
#include "ProjectManager.h"

using namespace std;

//-----------------------------------------------------------------------------------------
CProjectManager::CProjectManager()
{
//    std::cout << "CProjectManager constructor"  << std::endl;
}

//-----------------------------------------------------------------------------------------
CProjectManager::~CProjectManager()
{
//    std::cout << "CProjectManager desstructor"  << std::endl;
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
    m_uiOwnAddress = pxCommantLineArgumentCustomer -> GetOwnAddress();
}
