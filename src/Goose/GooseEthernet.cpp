//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "GooseEthernet.h"
#include "Platform.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
CGooseEthernet::CGooseEthernet()
{
    std::cout << "CGooseEthernet constructor"  << std::endl;
    m_pxCommunicationDevice = new CEthernetCommunicationDevice();
    m_puiRxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    m_puiTxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    SetFsmState(IDDLE);
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

////-----------------------------------------------------------------------------------------
//void CGooseEthernet::DestinationMacAddressSet(uint8_t* uiDestination,
//        uint8_t* uiSourse)
//{
//    memset(uiDestination, uiSourse, MAC_ADDRESS_LENGTH);
//}
//
////-----------------------------------------------------------------------------------------
//void CGooseEthernet::SourseMacAddressSet(uint8_t* uiDestination,
//        uint8_t* uiSourse)
//{
//    memset(uiDestination, uiSourse, MAC_ADDRESS_LENGTH);
//}
//
//////-----------------------------------------------------------------------------------------
////void CGooseEthernet::DestinationMacAddressSet(uint8_t* puiMacAddress)
////{
////    memset(m_auiDestinationMacAddress, puiMacAddress, MAC_ADDRESS_LENGTH);
////}
////
//////-----------------------------------------------------------------------------------------
////void CGooseEthernet::SourseMacAddressSet(uint8_t* puiMacAddress)
////{
////    memset(m_auiSourseMacAddress, puiMacAddress, MAC_ADDRESS_LENGTH);
////}
//
//
///* TODO: consider replacing this with memcpy */
//#define SET_MAC(WHICH, FRAME, MAC) \
//do \
//{ \
//  /* Check parameters */ \
//  if ( FRAME == 0 || MAC == 0 ) \
//  { \
//    return 0; \
//  } \
//\
//  /* Declare variables */ \
//  size_t i = 0; /* Temp variable used for array index */ \
//\
//  /* Copy the ethernet header into the GOOSE frame */ \
//  for( i = 0; i < 6; i++ ) \
//  { \
//    WHICH = MAC[i]; \
//  } \
//\
//  return 1; \
//\
//} \
//while (0)
//
//
//int set_dest_mac( goose_frame_t *goose_frame, const uint8_t *dmac )
//{
//    SET_MAC(goose_frame->eth_hdr.ether_dhost[i], goose_frame, dmac);
//}
//
//
//int set_src_mac( goose_frame_t *goose_frame, const uint8_t *smac )
//{
//    SET_MAC(goose_frame->eth_hdr.ether_shost[i], goose_frame, smac);
//#if 0
//    /* Check parameters */
//    if ( goose_frame == 0 || smac == 0 )
//    {
//        return 0;
//    }
//
//    /* Declare variables */
//    size_t i = 0; /* Temp variable used for array index */
//
//    /* Copy the ethernet header into the GOOSE frame */
//    for( i = 0; i < 6; i++ )
//    {
//        goose_frame->eth_hdr.ether_shost[i] = smac[i];
//    }
//
//    return 1;
//#endif
//}

//    eh = (struct ether_header *) buf;
//-----------------------------------------------------------------------------------------
void CGooseEthernet::ReceiveEnable(void)
{
    m_pxCommunicationDevice -> Open();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::ReceiveDisable(void)
{
    m_pxCommunicationDevice -> Close();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::TransmitEnable(void)
{
    m_pxCommunicationDevice -> Open();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::TransmitDisable(void)
{
    m_pxCommunicationDevice -> Close();
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGooseEthernet::CheckHeader(uint8_t *puiRequest)
{

//    /* Transaction ID */
//    if (m_uiRequestTransactionId < UINT16_MAX)
//    {
//        m_uiRequestTransactionId++;
//    }
//    else
//    {
//        m_uiRequestTransactionId = 0;
//    }
//
//    puiRequest[0] = (m_uiRequestTransactionId >> 8);
//    puiRequest[1] = (m_uiRequestTransactionId & 0x00ff);
//
//    /* Protocol Modbus */
//    puiRequest[2] = 0;
//    puiRequest[3] = 0;
//
//    /* Length will be defined later by set_puiRequest_length_tcp at offsets 4
//       and 5 */
//
//    puiRequest[6] = uiSlave;
//    puiRequest[7] = uiFunctionCode;
//    puiRequest[8] = (static_cast<uint8_t>(uiAddress >> 8));
//    puiRequest[9] = (static_cast<uint8_t>(uiAddress & 0x00ff));
//    puiRequest[10] = (static_cast<uint8_t>(uiBitNumber >> 8));
//    puiRequest[11] = (static_cast<uint8_t>(uiBitNumber & 0x00ff));
//
//    return _MODBUS_TCP_PRESET_REQ_LENGTH;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGooseEthernet::SetHeader(uint8_t *puiResponse)
{
    uint16_t uiLength = 0;

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiResponse;

    memcpy(pxEthernetHeader -> ether_dhost,
           m_pxCommunicationDevice -> GetDestnationMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    memcpy(pxEthernetHeader -> ether_shost,
           m_pxCommunicationDevice -> GetSourseMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    /* Ethertype field */
    pxEthernetHeader -> ether_type = htons(ETH_P_IP);

    uiLength += sizeof(struct ether_header);

    return uiLength;
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
//    std::cout << "CGooseEthernet::Fsm"  << std::endl;
//
//            cout << "GetFsmState() " << (int)GetFsmState() << endl;

    switch (GetFsmState())
    {
        int16_t iBytesNumber;

    case IDDLE:
        break;
//-----------------------------------------------------------------------------------------
// GooseServer
    case REQUEST_ENABLE:
        std::cout << "CGooseEthernet::Fsm REQUEST_ENABLE"  << std::endl;
//        m_pxCommunicationDevice -> Listen();
//        GetTimerPointer() -> Set(m_uiReceiveTimeout);
//        SetFsmState(WAITING_ACCEPT);
        ReceiveDisable();
        GetTimerPointer() -> Set(m_uiReceiveTimeout);
        SetMessageLength(0);
        ReceiveEnable();
        SetFsmState(START_REQUEST);
        break;

//    case WAITING_ACCEPT:
//        if (m_pxCommunicationDevice -> Accept())
//        {
//            SetFsmState(START_REQUEST);
//        }
//
//        // Закончилось время ожидания запроса(15 секунд)?
//        if (GetTimerPointer() -> IsOverflow())
//        {
//            SetFsmState(REQUEST_ERROR);
//        }
//        break;

    case START_REQUEST:
//    std::cout << "CGooseEthernet::Fsm START_REQUEST"  << std::endl;
//        ReceiveDisable();
        GetTimerPointer() -> Set(m_uiReceiveTimeout);
        SetMessageLength(0);
//        ReceiveEnable();
        SetFsmState(WAITING_MESSAGE_REQUEST);
        break;

    case WAITING_MESSAGE_REQUEST:
        iBytesNumber = Receive((m_puiRxBuffer + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

//        if (iBytesNumber > 0)
//        {
//            SetMessageLength(GetMessageLength() + iBytesNumber);
////            GetTimerPointer() -> Set(m_uiGuardTimeout);
//            SetFsmState(RECEIVE_MESSAGE_REQUEST);
//        }
//        else if (iBytesNumber == 0)
//        {
//            SetFsmState(REQUEST_ERROR);
//        }
//
//        // Закончилось время ожидания запроса(15 секунд)?
//        if (GetTimerPointer() -> IsOverflow())
//        {
//            SetFsmState(REQUEST_ERROR);
//        }

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

        // Принят пакет(закончилось время ожидания следующего бода(3.5 бод))?
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
        // Закончилось время паузы между приёмом и передачей(5 милисекунд)?
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

        // Закончилось время ожидания окончания передачи?
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
//        // Закончилось время ожидания ответа(500 милисекунд)?
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
//        // Принят пакет(закончилось время ожидания следующего бода(3.5 бод))?
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
//        // Закончилось время паузы между приёмом и передачей(5 милисекунд)?
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
//        // Закончилось время ожидания окончания передачи?
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
