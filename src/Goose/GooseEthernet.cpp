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


// pas 64:cf:d9:55:ca:1e
#define DEST_MAC0	0x64
#define DEST_MAC1	0xcf
#define DEST_MAC2	0xd9
#define DEST_MAC3	0x55
#define DEST_MAC4	0xca
#define DEST_MAC5	0x1e
//// beagle ether fc:69:47:db:3f:91
//#define DEST_MAC0	0xfc
//#define DEST_MAC1	0x69
//#define DEST_MAC2	0x47
//#define DEST_MAC3	0xdb
//#define DEST_MAC4	0x3f
//#define DEST_MAC5	0x91
//// msi destination MAC: 3c:e9:f7:ab:dd:6c
//#define DEST_MAC0	0x3c
//#define DEST_MAC1	0xe9
//#define DEST_MAC2	0xf7
//#define DEST_MAC3	0xab
//#define DEST_MAC4	0xdd
//#define DEST_MAC5	0x6c


// pas 64:cf:d9:55:ca:1e
#define SOURSE_MAC0	0x64
#define SOURSE_MAC1	0xcf
#define SOURSE_MAC2	0xd9
#define SOURSE_MAC3	0x55
#define SOURSE_MAC4	0xca
#define SOURSE_MAC5	0x1e
//// beagle ether fc:69:47:db:3f:91
//#define SOURSE_MAC0	0xfc
//#define SOURSE_MAC1	0x69
//#define SOURSE_MAC2	0x47
//#define SOURSE_MAC3	0xdb
//#define SOURSE_MAC4	0x3f
//#define SOURSE_MAC5	0x91
//// msi destination MAC: 3c:e9:f7:ab:dd:6c
//#define SOURSE_MAC0	0x3c
//#define SOURSE_MAC1	0xe9
//#define SOURSE_MAC2	0xf7
//#define SOURSE_MAC3	0xab
//#define SOURSE_MAC4	0xdd
//#define SOURSE_MAC5	0x6c

extern CTimeMeasure xTimeMeasure;
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

//-----------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------
uint16_t CGooseEthernet::SetHeader(uint8_t *puiData)
{
//    std::cout << "CGooseEthernet::SetHeader"  << std::endl;
    uint16_t uiLength = 0;

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiData;

//    memcpy(pxEthernetHeader -> ether_dhost,
//           m_pxCommunicationDevice -> GetDestnationMacAddress(),
//           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    pxEthernetHeader -> ether_dhost[0] = DEST_MAC0;
    pxEthernetHeader -> ether_dhost[1] = DEST_MAC1;
    pxEthernetHeader -> ether_dhost[2] = DEST_MAC2;
    pxEthernetHeader -> ether_dhost[3] = DEST_MAC3;
    pxEthernetHeader -> ether_dhost[4] = DEST_MAC4;
    pxEthernetHeader -> ether_dhost[5] = DEST_MAC5;

    memcpy(pxEthernetHeader -> ether_shost,
           m_pxCommunicationDevice -> GetSourseMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

    /* Ethertype field */
    pxEthernetHeader -> ether_type = htons(ETH_P_IP);


//struct sockaddr_ll socket_address;
struct ifreq if_idx;
    // передача.
    /* Get the index of the interface to send on */
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, m_pxCommunicationDevice -> m_pccDeviceName, strlen(m_pxCommunicationDevice -> m_pccDeviceName));
    if (ioctl(m_pxCommunicationDevice -> m_iDeviceDescriptor, SIOCGIFINDEX, &if_idx) < 0)
    {
//        perror("SIOCGIFINDEX");
        return 0;
    }

    /* Index of the network device */
    m_pxCommunicationDevice -> socket_address.sll_ifindex = if_idx.ifr_ifindex;
//    printf("if_idx.ifr_ifindex: %x\n", if_idx.ifr_ifindex);
    /* Address length*/
    m_pxCommunicationDevice -> socket_address.sll_halen = ETH_ALEN;

    m_pxCommunicationDevice -> socket_address.sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
    m_pxCommunicationDevice -> socket_address.sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
    m_pxCommunicationDevice -> socket_address.sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
    m_pxCommunicationDevice -> socket_address.sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
    m_pxCommunicationDevice -> socket_address.sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
    m_pxCommunicationDevice -> socket_address.sll_addr[5] = pxEthernetHeader -> ether_dhost[5];


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


//    cout << "Write" << endl;
//    unsigned char *pucSourceTemp;
//    pucSourceTemp = (unsigned char*)puiData;
//    for(int i=0; i<32; )
//    {
//        for(int j=0; j<8; j++)
//        {
//            cout << hex << uppercase << setw(2) << setfill('0') << (unsigned int)pucSourceTemp[i + j] << " ";
//        }
//        cout << endl;
//        i += 8;
//    }


//    /* Send packet */
//    if (sendto(m_pxCommunicationDevice -> m_iDeviceDescriptor,
//               puiData,
//               uiLength,
//               0,
//               (struct sockaddr*)&socket_address,
//               sizeof(struct sockaddr_ll)) < 0)
////    if (write(sockfd, buf, tx_len) < 0)
//    {
//        printf("Send failed\n");
//        return 1;
//    }
//    else
//    {
//        printf("Send ok\n");
//        return 1;
//    }

    return uiLength;
}

//-----------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------
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
        // увеличим количество отправленных пакетов
        GetGooseServerObserver() ->
        SetTransmitPacketNumber(GetGooseServerObserver() ->
                                GetTransmitPacketNumber() + 1);
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

//-----------------------------------------------------------------------------------------
// GooseClient
    case CONFIRMATION_ENABLE:
        std::cout << "CGooseEthernet::Fsm REQUEST_ENABLE"  << std::endl;
        ReceiveDisable();
        SetMessageLength(0);
        ReceiveEnable();
        SetFsmState(FRAME_TRANSMIT_REQUEST);
        break;

    case START_CONFIRMATION:
        ReceiveDisable();
        SetMessageLength(0);
        ReceiveEnable();
        SetFsmState(RECEIVE_MESSAGE_CONFIRMATION);
        break;

    case RECEIVE_MESSAGE_CONFIRMATION:
        std::cout << "CGooseEthernet::Fsm RECEIVE_MESSAGE_CONFIRMATION"  << std::endl;
        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
            SetFsmState(ANSWER_PROCESSING_CONFIRMATION);
        }
        else
        {
            SetFsmState(FRAME_TRANSMIT_REQUEST);
        }

        break;

    case ANSWER_PROCESSING_CONFIRMATION:
        std::cout << "CGooseEthernet::Fsm ANSWER_PROCESSING_CONFIRMATION"  << std::endl;
        if (AnswerProcessing(GetRxBuffer(), GetMessageLength()))
        {
            SetFsmState(FRAME_TRANSMIT_REQUEST);
        }
        else
        {
            SetFsmState(FRAME_TRANSMIT_REQUEST);
        }
        break;

    case FRAME_TRANSMIT_REQUEST:
        std::cout << "CGooseEthernet::Fsm FRAME_TRANSMIT_REQUEST"  << std::endl;
        ReportSlaveIDRequest(7);
        Send(GetTxBuffer(), GetMessageLength());
//        GetTimerPointer() -> Begin();
        xTimeMeasure.Begin();
        SetFsmState(END_WAITING_FRAME_TRANSMIT_REQUEST);
        break;

    case END_WAITING_FRAME_TRANSMIT_REQUEST:
        std::cout << "CGooseEthernet::Fsm END_WAITING_FRAME_TRANSMIT_REQUEST"  << std::endl;
        if (GetAttemptNumber() > 0)
        {
            SetAttemptNumber(GetAttemptNumber() - 1);
            SetFsmState(RECEIVE_MESSAGE_CONFIRMATION);
        }
        else
        {
            SetFsmState(STOP_CONFIRMATION);
        }
        break;

    case STOP_CONFIRMATION:
        std::cout << "CGooseEthernet::Fsm STOP_CONFIRMATION"  << std::endl;
        ReceiveDisable();
        SetFsmState(IDDLE);
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
