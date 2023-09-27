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
uint16_t CGooseEthernet::SetHeader(uint8_t *puiData)
{
    uint16_t uiLength = 0;

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiData;

    memcpy(pxEthernetHeader -> ether_dhost,
           m_pxCommunicationDevice -> GetDestnationMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    memcpy(pxEthernetHeader -> ether_shost,
           m_pxCommunicationDevice -> GetSourseMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    /* Ethertype field */
    pxEthernetHeader -> ether_type = htons(ETH_P_IP);

    uiLength += sizeof(struct ether_header);

    if (m_uiRequestTransactionId < UINT16_MAX)
    {
        m_uiRequestTransactionId++;
    }
    else
    {
        m_uiRequestTransactionId = 0;
    }

    puiData[uiLength++] = (m_uiRequestTransactionId >> 8);
    puiData[uiLength++] = (m_uiRequestTransactionId & 0x00ff);

    return uiLength;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGooseEthernet::RequestBasis(uint8_t uiSlave,
                                      uint8_t uiFunctionCode,
                                      uint8_t *puiRequest)
{
//    /* Extract from MODBUS Messaging on TCP/IP Implementation Guide V1.0b
//       (page 23/46):
//       The transaction identifier is used to associate the future response
//       with the request. So, at a time, on a TCP connection, this identifier
//       must be unique. */
//
//    /* Transaction ID */
//    if (m_uiRequestTransactionId < UINT16_MAX)
//    {
//        m_uiRequestTransactionId++;
//    }
//    else
//    {
//        m_uiRequestTransactionId = 0;
//    }
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

    uint16_t uiLength;

    uiLength = SetHeader(puiRequest);
    puiRequest[uiLength++] = uiSlave;
    puiRequest[uiLength++] = uiFunctionCode;

    return uiLength;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGooseEthernet::ResponseBasis(uint8_t uiSlave,
                                       uint8_t uiFunctionCode,
                                       uint8_t *puiResponse)
{
    uint16_t uiLength;

    uiLength = SetHeader(puiResponse);
    puiResponse[uiLength++] = uiSlave;
    puiResponse[uiLength++] = uiFunctionCode;

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
//        std::cout << "CGooseEthernet::Fsm REQUEST_ENABLE"  << std::endl;
        ReceiveDisable();
        SetMessageLength(0);
        ReceiveEnable();
        SetFsmState(START_REQUEST);
        break;

    case START_REQUEST:
//        std::cout << "CGooseEthernet::Fsm START_REQUEST"  << std::endl;
        SetMessageLength(0);
        SetFsmState(RECEIVE_MESSAGE_REQUEST);
        break;

    case RECEIVE_MESSAGE_REQUEST:
//        std::cout << "CGooseEthernet::Fsm RECEIVE_MESSAGE_REQUEST"  << std::endl;
        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
            SetFsmState(REQUEST_PROCESSING_REQUEST);
        }
        else
        {
            SetFsmState(STOP_REQUEST);
        }

        break;

    case REQUEST_PROCESSING_REQUEST:
//        std::cout << "CGooseEthernet::Fsm REQUEST_PROCESSING_REQUEST"  << std::endl;
        m_uiResponseTransactionId++;

        if (RequestProcessing(GetRxBuffer(), GetTxBuffer(), GetMessageLength()))
        {
            SetFsmState(FRAME_TRANSMIT_CONFIRMATION);
        }
        else
        {
            SetFsmState(STOP_REQUEST);
        }
        break;

    case FRAME_TRANSMIT_CONFIRMATION:
//        std::cout << "CGooseEthernet::Fsm FRAME_TRANSMIT_CONFIRMATION"  << std::endl;
        Send(GetTxBuffer(), GetMessageLength());
        SetFsmState(STOP_REQUEST);
        break;

    case STOP_REQUEST:
//        ReceiveDisable();
        SetFsmState(START_REQUEST);
        break;

    case REQUEST_ERROR:
//        ReceiveDisable();
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
//        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (MODBUS_TCP_MAX_ADU_LENGTH - GetMessageLength()));
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
//        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (MODBUS_TCP_MAX_ADU_LENGTH - GetMessageLength()));
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
//            if (FrameCheck(GetRxBuffer(), GetMessageLength()))
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
//        if (AnswerProcessing(GetRxBuffer(), GetMessageLength()))
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
//            SendMessage(GetTxBuffer(), GetMessageLength());
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
