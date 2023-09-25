//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "GooseEthernet.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------
CGooseEthernet::CGooseEthernet()
{
    std::cout << "CGooseEthernet constructor"  << std::endl;
    m_pxCommunicationDevice = new CEthernetCommunicationDevice();
    m_puiRxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    m_puiTxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
//    SetFsmState(IDDLE);
}

//-----------------------------------------------------------------------------------------
CGooseEthernet::~CGooseEthernet()
{
    std::cout << "CGooseEthernet desstructor"  << std::endl;
    delete[] m_puiTxBuffer;
    delete[] m_puiRxBuffer;
    delete m_pxCommunicationDevice;
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::CommunicationDeviceInit(const char* pccIpAddress,
        uint16_t uiPort)
{
    m_pxCommunicationDevice -> Init();
    m_pxCommunicationDevice -> SetIpAddress(pccIpAddress);
    m_pxCommunicationDevice -> SetPort(uiPort);
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::ReceiveEnable(void)
{
//    m_pxCommunicationDevice -> Open();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::ReceiveDisable(void)
{
//    m_pxCommunicationDevice -> Close();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::TransmitEnable(void)
{
//    m_pxCommunicationDevice -> Open();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::TransmitDisable(void)
{
//    m_pxCommunicationDevice -> Close();
}

//-----------------------------------------------------------------------------------------
uint16_t CGooseEthernet::Send(uint8_t *puiMessage, uint16_t uiLength)
{
    return m_pxCommunicationDevice -> Write(puiMessage, uiLength);
}

//-----------------------------------------------------------------------------------------
int16_t CGooseEthernet::Receive(uint8_t *puiDestination, uint16_t uiLength)
{
    return m_pxCommunicationDevice -> Read(puiDestination, uiLength);
}

//-----------------------------------------------------------------------------------------
int8_t CGooseEthernet::FrameCheck(uint8_t *puiSourse, uint16_t uiLength)
{
    if (uiLength < MIN_MESSAGE_LENGTH())
    {
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------
int8_t CGooseEthernet::MessengerIsReady(void)
{
    if (GetFsmState() == IDDLE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::Fsm(void)
{
    switch (GetFsmState())
    {
        int16_t iBytesNumber;

    case IDDLE:
        break;
//-----------------------------------------------------------------------------------------
// GooseServer
    case REQUEST_ENABLE:
        m_pxCommunicationDevice -> Listen();
        GetTimerPointer() -> Set(m_uiReceiveTimeout);
        SetFsmState(WAITING_ACCEPT);
        break;

    case WAITING_ACCEPT:
        if (m_pxCommunicationDevice -> Accept())
        {
            SetFsmState(START_REQUEST);
        }

        // «акончилось врем€ ожидани€ запроса(15 секунд)?
        if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmState(REQUEST_ERROR);
        }
        break;

    case START_REQUEST:
//        ReceiveDisable();
        GetTimerPointer() -> Set(m_uiReceiveTimeout);
        SetMessageLength(0);
//        ReceiveEnable();
        SetFsmState(WAITING_MESSAGE_REQUEST);
        break;

    case WAITING_MESSAGE_REQUEST:
        iBytesNumber = Receive((m_puiRxBuffer + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
//            GetTimerPointer() -> Set(m_uiGuardTimeout);
            SetFsmState(RECEIVE_MESSAGE_REQUEST);
        }
        else if (iBytesNumber == 0)
        {
            SetFsmState(REQUEST_ERROR);
        }

        // «акончилось врем€ ожидани€ запроса(15 секунд)?
        if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmState(REQUEST_ERROR);
        }

        break;

    case RECEIVE_MESSAGE_REQUEST:
        iBytesNumber = Receive((m_puiRxBuffer + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
//            GetTimerPointer() -> Set(m_uiGuardTimeout);
        }
        else if (iBytesNumber == 0)
        {
            SetFsmState(REQUEST_ERROR);
        }

        // ѕрин€т пакет(закончилось врем€ ожидани€ следующего бода(3.5 бод))?
        if (GetTimerPointer() -> IsOverflow())
        {
            if (FrameCheck(m_puiRxBuffer, GetMessageLength()))
            {
                SetFsmState(REQUEST_PROCESSING_REQUEST);
            }
            else
            {
                SetFsmState(STOP_REQUEST);
            }
        }

        break;

    case REQUEST_PROCESSING_REQUEST:
        m_uiResponseTransactionId = (m_puiRxBuffer[0] << 8) + m_puiRxBuffer[1];

        if (RequestProcessing(m_puiRxBuffer, m_puiTxBuffer, GetMessageLength()))
        {
//            CPlatform::TxLedOn();
            SetFsmState(FRAME_TRANSMIT_CONFIRMATION);
        }
        else
        {
            //            CPlatform::TxLedOff();
            SetFsmState(STOP_REQUEST);
        }
        break;

    case FRAME_TRANSMIT_CONFIRMATION:
        GetTimerPointer() -> Set(m_uiTransmitDelayTimeout);
        ReceiveDisable();
        SetFsmState(WAITING_FRAME_TRANSMIT_CONFIRMATION);
        break;

    case WAITING_FRAME_TRANSMIT_CONFIRMATION:
        // «акончилось врем€ паузы между приЄмом и передачей(5 милисекунд)?
        if (GetTimerPointer() -> IsOverflow())
        {
            GetTimerPointer() -> Set(m_uiConfirmationTimeout);
            TransmitEnable();
            Send(m_puiTxBuffer, GetMessageLength());
            SetFsmState(END_WAITING_FRAME_TRANSMIT_CONFIRMATION);
        }
        break;

    case END_WAITING_FRAME_TRANSMIT_CONFIRMATION:
        if (IsDataWrited())
        {
            TransmitDisable();
//            CPlatform::TxLedOff();
            SetFsmState(STOP_REQUEST);
        }

        // «акончилось врем€ ожидани€ окончани€ передачи?
        if (GetTimerPointer() -> IsOverflow())
        {
//            CPlatform::TxLedOff();
            SetFsmState(REQUEST_ERROR);
        }

        break;

    case STOP_REQUEST:
//        ReceiveDisable();
        SetFsmState(START_REQUEST);
        break;

    case REQUEST_ERROR:
//        ReceiveDisable();
        m_pxCommunicationDevice -> Close();
        SetFsmState(REQUEST_ENABLE);
        break;

////-----------------------------------------------------------------------------------------
//// GooseClient
//    case START_CONFIRMATION:
//        ReceiveDisable();
//        GetTimerPointer() -> Set(m_uiConfirmationTimeout);
//        SetMessageLength(0);
//        ReceiveEnable();
//        SetFsmState(WAITING_MESSAGE_CONFIRMATION);
//        break;
//
//    case WAITING_MESSAGE_CONFIRMATION:
//        iBytesNumber = Receive((m_puiRxBuffer + GetMessageLength()), (MODBUS_TCP_MAX_ADU_LENGTH - GetMessageLength()));
//
//        if (iBytesNumber > 0)
//        {
//            SetMessageLength(GetMessageLength() + iBytesNumber);
//            GetTimerPointer() -> Set(m_uiGuardTimeout);
//            SetFsmState(RECEIVE_MESSAGE_CONFIRMATION);
//        }
//        else if (iBytesNumber == -1)
//        {
//            SetFsmState(STOP_CONFIRMATION);
//        }
//
//        // «акончилось врем€ ожидани€ ответа(500 милисекунд)?
//        if (GetTimerPointer() -> IsOverflow())
//        {
//            SetFsmState(STOP_CONFIRMATION);
//        }
//
//        break;
//
//    case RECEIVE_MESSAGE_CONFIRMATION:
//        iBytesNumber = Receive((m_puiRxBuffer + GetMessageLength()), (MODBUS_TCP_MAX_ADU_LENGTH - GetMessageLength()));
//
//        if (iBytesNumber > 0)
//        {
//            SetMessageLength(GetMessageLength() + iBytesNumber);
//            GetTimerPointer() -> Set(m_uiGuardTimeout);
//        }
//        else if (iBytesNumber == -1)
//        {
//            SetFsmState(STOP_CONFIRMATION);
//        }
//
//        // ѕрин€т пакет(закончилось врем€ ожидани€ следующего бода(3.5 бод))?
//        if (GetTimerPointer() -> IsOverflow())
//        {
//            if (FrameCheck(m_puiRxBuffer, GetMessageLength()))
//            {
//                SetFsmState(ANSWER_PROCESSING_CONFIRMATION);
//            }
//            else
//            {
//                SetFsmState(STOP_CONFIRMATION);
//            }
//        }
//
//        break;
//
//    case ANSWER_PROCESSING_CONFIRMATION:
//        if (AnswerProcessing(m_puiRxBuffer, GetMessageLength()))
//        {
//            SetFsmState(STOP_CONFIRMATION);
//        }
//        else
//        {
//            SetFsmState(STOP_CONFIRMATION);
//        }
//        break;
//
//    case FRAME_TRANSMIT_REQUEST:
//        GetTimerPointer() -> Set(m_uiTransmitDelayTimeout);
////        CPlatform::TxLedOn();
//        SetFsmState(WAITING_FRAME_TRANSMIT_REQUEST);
//        break;
//
//    case WAITING_FRAME_TRANSMIT_REQUEST:
//        // «акончилось врем€ паузы между приЄмом и передачей(5 милисекунд)?
//        if (GetTimerPointer() -> IsOverflow())
//        {
//            GetTimerPointer() -> Set(m_uiConfirmationTimeout);
//            TransmitEnable();
//            SendMessage(m_puiTxBuffer, GetMessageLength());
//            SetFsmState(END_WAITING_FRAME_TRANSMIT_REQUEST);
//        }
//        break;
//
//    case END_WAITING_FRAME_TRANSMIT_REQUEST:
//        if (IsDataWrited())
//        {
//            TransmitDisable();
////            CPlatform::TxLedOff();
//            SetFsmState(START_CONFIRMATION);
//        }
//
//        // «акончилось врем€ ожидани€ окончани€ передачи?
//        if (GetTimerPointer() -> IsOverflow())
//        {
////            CPlatform::TxLedOff();
//            SetFsmState(STOP_CONFIRMATION);
//        }
//
//        break;
//
//    case STOP_CONFIRMATION:
//        ReceiveDisable();
//        TransmitEnable();
//        SetFsmState(IDDLE);
//        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
