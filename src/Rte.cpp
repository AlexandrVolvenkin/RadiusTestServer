//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Rte.h"
#include "Platform.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
CRte::CRte()
{
    m_pxCommunicationDevice = new CSerialPort();
    SetFsmState(IDDLE);
}

//-----------------------------------------------------------------------------------------
CRte::~CRte()
{
    //dtor
}

//-----------------------------------------------------------------------------------------
void CRte::Fsm(void)
{
    switch (GetFsmState())
    {
//    case IDDLE:
//        break;
//
//    case START_SERVER:
//        GetCommunicationDevice()-> Open();
//        GetCommunicationDevice()-> Close();
////        SetFsmState(START_SERVER);
//        break;
//
//    case START_CLIENT:
////SetAttemptNumber(PING_ATTEMPTS_NUMBER)
//        break;

    default:
        break;
    }
}
