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
//    std::cout << "CGooseEthernet constructor"  << std::endl;
    m_pxCommunicationDevice = new CEthernetCommunicationDevice();
    m_puiRxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    m_puiTxBuffer = new uint8_t[GOOSE_ETHERNET_MAX_FRAME_LENGTH];
    SetFsmState(SERVER_STOPED);
    // создадим объект "производственная площадка задачи"
    SetProductionSite(new CGooseThreadProduction());
}

//-----------------------------------------------------------------------------------------
CGooseEthernet::~CGooseEthernet()
{
//    std::cout << "CGooseEthernet desstructor"  << std::endl;
    // удалим объект "производственная площадка задачи"
    delete m_pxProductionSite;
    delete[] m_puiTxBuffer;
    delete[] m_puiRxBuffer;
    delete m_pxCommunicationDevice;
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::Sleep(void)
{
    GetProductionSite() -> Sleep();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::Wakeup(void)
{
    GetProductionSite() -> Wakeup();
}

//-----------------------------------------------------------------------------------------
void CGooseEthernet::CommunicationDeviceInit(const char* pccIpAddress,
        uint16_t uiPort)
{
    m_pxCommunicationDevice -> Init();
    m_pxCommunicationDevice -> SetIpAddress(pccIpAddress);
    m_pxCommunicationDevice -> SetPort(uiPort);
}

//-----------------------------------------------------------------------------------------------------
void CGooseEthernet::WorkingArraysInit(uint8_t *puiCoils,
                                       uint8_t *puiDiscreteInputs,
                                       uint16_t *pui16HoldingRegisters,
                                       uint16_t *pui16InputRegisters,
                                       uint16_t uiCoilsNumber,
                                       uint16_t uiDiscreteInputsNumber,
                                       uint16_t uiHoldingRegistersNumber,
                                       uint16_t uiInputRegistersNumber)
{
    m_puiCoils = puiCoils;
    m_puiDiscreteInputs = puiDiscreteInputs;
    m_pui16HoldingRegisters = pui16HoldingRegisters;
    m_pui16InputRegisters = pui16InputRegisters;
    m_uiCoilsNumber = uiCoilsNumber;
    m_uiDiscreteInputsNumber = uiDiscreteInputsNumber;
    m_uiHoldingRegistersNumber = uiHoldingRegistersNumber;
    m_uiInputRegistersNumber = uiInputRegistersNumber;
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
    //    m_pxCommunicationDevice -> socket_address.sll_ifindex = if_idx.ifr_ifindex;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_ifindex = if_idx.ifr_ifindex;
//    printf("if_idx.ifr_ifindex: %x\n", if_idx.ifr_ifindex);
    /* Address length*/
//    m_pxCommunicationDevice -> socket_address.sll_halen = ETH_ALEN;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_halen = ETH_ALEN;

//    m_pxCommunicationDevice -> socket_address.sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
//    m_pxCommunicationDevice -> socket_address.sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
//    m_pxCommunicationDevice -> socket_address.sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
//    m_pxCommunicationDevice -> socket_address.sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
//    m_pxCommunicationDevice -> socket_address.sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
//    m_pxCommunicationDevice -> socket_address.sll_addr[5] = pxEthernetHeader -> ether_dhost[5];

    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[5] = pxEthernetHeader -> ether_dhost[5];


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

//-----------------------------------------------------------------------------------------
uint16_t CGooseEthernet::RequestBasis(uint8_t uiSlave,
                                      uint8_t uiFunctionCode,
                                      uint8_t *puiRequest)
{
    uint16_t uiLength = 0;

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiRequest;

    memcpy(pxEthernetHeader -> ether_dhost,
           m_pxCommunicationDevice -> GetDestnationMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

//    pxEthernetHeader -> ether_dhost[0] = DEST_MAC0;
//    pxEthernetHeader -> ether_dhost[1] = DEST_MAC1;
//    pxEthernetHeader -> ether_dhost[2] = DEST_MAC2;
//    pxEthernetHeader -> ether_dhost[3] = DEST_MAC3;
//    pxEthernetHeader -> ether_dhost[4] = DEST_MAC4;
//    pxEthernetHeader -> ether_dhost[5] = DEST_MAC5;

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
    //    m_pxCommunicationDevice -> socket_address.sll_ifindex = if_idx.ifr_ifindex;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_ifindex = if_idx.ifr_ifindex;
//    printf("if_idx.ifr_ifindex: %x\n", if_idx.ifr_ifindex);
    /* Address length*/
//    m_pxCommunicationDevice -> socket_address.sll_halen = ETH_ALEN;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_halen = ETH_ALEN;

//    m_pxCommunicationDevice -> socket_address.sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
//    m_pxCommunicationDevice -> socket_address.sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
//    m_pxCommunicationDevice -> socket_address.sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
//    m_pxCommunicationDevice -> socket_address.sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
//    m_pxCommunicationDevice -> socket_address.sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
//    m_pxCommunicationDevice -> socket_address.sll_addr[5] = pxEthernetHeader -> ether_dhost[5];

    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[5] = pxEthernetHeader -> ether_dhost[5];


    uiLength += sizeof(struct ether_header);

    if (m_uiRequestTransactionId < UINT16_MAX)
    {
        m_uiRequestTransactionId++;
    }
    else
    {
        m_uiRequestTransactionId = 0;
    }

    puiRequest[uiLength++] = (m_uiRequestTransactionId >> 8);
    puiRequest[uiLength++] = (m_uiRequestTransactionId & 0x00ff);

//    uint16_t uiLength;
//
//    uiLength = SetHeader(puiRequest);
    puiRequest[uiLength++] = uiSlave;
    puiRequest[uiLength++] = uiFunctionCode;

    return uiLength;
}

////-----------------------------------------------------------------------------------------
//uint16_t CGooseEthernet::RequestBasis(uint8_t uiSlave,
//                                      uint8_t uiFunctionCode,
//                                      uint16_t uiAddress,
//                                      uint16_t uiBitNumber,
//                                      uint8_t *puiRequest)
//{
//    std::cout << "CGooseEthernet::RequestBasis 5 arg"  << std::endl;
//    puiRequest[0] = uiSlave;
//    puiRequest[1] = uiFunctionCode;
//    puiRequest[2] = (static_cast<uint8_t>(uiAddress >> 8));
//    puiRequest[3] = (static_cast<uint8_t>(uiAddress & 0x00ff));
//    puiRequest[4] = (static_cast<uint8_t>(uiBitNumber >> 8));
//    puiRequest[5] = (static_cast<uint8_t>(uiBitNumber & 0x00ff));
//
//    return 0;//_MODBUS_RTU_PRESET_REQ_LENGTH;
//}

//-----------------------------------------------------------------------------------------
uint16_t CGooseEthernet::ResponseBasis(uint8_t uiSlave,
                                       uint8_t uiFunctionCode,
                                       uint8_t *puiResponse)
{

//    std::cout << "CGooseEthernet::ResponseBasis"  << std::endl;
    uint16_t uiLength = 0;

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiResponse;

    memcpy(pxEthernetHeader -> ether_dhost,
           m_pxCommunicationDevice -> GetDestnationMacAddress(),
           CEthernetCommunicationDevice::MAC_ADDRESS_LENGTH);

//    pxEthernetHeader -> ether_dhost[0] = DEST_MAC0;
//    pxEthernetHeader -> ether_dhost[1] = DEST_MAC1;
//    pxEthernetHeader -> ether_dhost[2] = DEST_MAC2;
//    pxEthernetHeader -> ether_dhost[3] = DEST_MAC3;
//    pxEthernetHeader -> ether_dhost[4] = DEST_MAC4;
//    pxEthernetHeader -> ether_dhost[5] = DEST_MAC5;

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
    //    m_pxCommunicationDevice -> socket_address.sll_ifindex = if_idx.ifr_ifindex;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_ifindex = if_idx.ifr_ifindex;
//    printf("if_idx.ifr_ifindex: %x\n", if_idx.ifr_ifindex);
    /* Address length*/
//    m_pxCommunicationDevice -> socket_address.sll_halen = ETH_ALEN;
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_halen = ETH_ALEN;

//    m_pxCommunicationDevice -> socket_address.sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
//    m_pxCommunicationDevice -> socket_address.sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
//    m_pxCommunicationDevice -> socket_address.sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
//    m_pxCommunicationDevice -> socket_address.sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
//    m_pxCommunicationDevice -> socket_address.sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
//    m_pxCommunicationDevice -> socket_address.sll_addr[5] = pxEthernetHeader -> ether_dhost[5];

    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[0] = pxEthernetHeader -> ether_dhost[0];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[1] = pxEthernetHeader -> ether_dhost[1];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[2] = pxEthernetHeader -> ether_dhost[2];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[3] = pxEthernetHeader -> ether_dhost[3];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[4] = pxEthernetHeader -> ether_dhost[4];
    m_pxCommunicationDevice -> GetSocketLowAddress() -> sll_addr[5] = pxEthernetHeader -> ether_dhost[5];


    uiLength += sizeof(struct ether_header);

    if (m_uiRequestTransactionId < UINT16_MAX)
    {
        m_uiRequestTransactionId++;
    }
    else
    {
        m_uiRequestTransactionId = 0;
    }

    puiResponse[uiLength++] = (m_uiRequestTransactionId >> 8);
    puiResponse[uiLength++] = (m_uiRequestTransactionId & 0x00ff);

//    uint16_t uiLength;

//    uiLength = SetHeader(puiResponse);
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
    if (GetFsmState() == CLIENT_IDDLE)
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

//-----------------------------------------------------------------------------------------
// GooseServer
    case SERVER_START:
//        std::cout << "CGooseEthernet::Fsm SERVER_START"  << std::endl;
        ReceiveDisable();
        ReceiveEnable();
        SetFsmState(SERVER_DATA_RECEIVE_PREPARE);
        break;

    case SERVER_DATA_RECEIVE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm SERVER_DATA_RECEIVE_PREPARE"  << std::endl;
        SetMessageLength(0);
        SetFsmState(SERVER_DATA_RECEIVE_WAITING);
        break;

    case SERVER_DATA_RECEIVE_WAITING:
//        std::cout << "CGooseEthernet::Fsm SERVER_DATA_RECEIVE_WAITING"  << std::endl;
        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
            SetFsmState(SERVER_RECEIVED_DATA_PROCESSING);
        }
        else
        {
            SetFsmState(SERVER_RECEIVED_DATA_ERROR_PROCESSING);
        }
        break;

    case SERVER_RECEIVED_DATA_PROCESSING:
//        std::cout << "CGooseEthernet::Fsm SERVER_RECEIVED_DATA_PROCESSING"  << std::endl;
        if (RequestProcessing(GetRxBuffer(), GetTxBuffer(), GetMessageLength()))
        {
            SetFsmState(SERVER_DATA_TRANSMIT);
        }
        else
        {
            SetFsmState(SERVER_RECEIVED_DATA_ERROR_PROCESSING);
        }
        break;

    case SERVER_RECEIVED_DATA_ERROR_PROCESSING:
//        std::cout << "CGooseEthernet::Fsm SERVER_RECEIVED_DATA_ERROR_PROCESSING"  << std::endl;
        SetFsmState(SERVER_DATA_RECEIVE_PREPARE);
        break;

    case SERVER_DATA_TRANSMIT_PREPARE:
//        std::cout << "CGooseEthernet::Fsm SERVER_DATA_TRANSMIT_PREPARE"  << std::endl;
//        Send(GetTxBuffer(), GetMessageLength());
//
//        // увеличим количество отправленных пакетов
//        GetGooseServerObserver() ->
//        SetTransmitPacketNumber(GetGooseServerObserver() ->
//                                GetTransmitPacketNumber() + 1);

        SetFsmState(SERVER_DATA_TRANSMIT);
        break;

    case SERVER_DATA_TRANSMIT:
//        std::cout << "CGooseEthernet::Fsm SERVER_DATA_TRANSMIT"  << std::endl;
//        // получим время начала замера
//        xTimeMeasure.Begin();

        Send(GetTxBuffer(), GetMessageLength());

        // увеличим количество отправленных пакетов
        GetGooseServerObserver() ->
        SetTransmitPacketNumber(GetGooseServerObserver() ->
                                GetTransmitPacketNumber() + 1);

        SetFsmState(SERVER_DATA_RECEIVE_PREPARE);
        break;

    case SERVER_IDDLE_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm SERVER_IDDLE_STATE_PREPARE"  << std::endl;
        SetFsmState(SERVER_IDDLE);
        break;

    case SERVER_IDDLE:
//        std::cout << "CGooseEthernet::Fsm SERVER_IDDLE"  << std::endl;
//        Sleep();
        break;

    case SERVER_STOP_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm SERVER_STOP_STATE_PREPARE"  << std::endl;
        ReceiveDisable();
        SetFsmState(SERVER_STOPED);
        break;

    case SERVER_STOPED:
//        std::cout << "CGooseEthernet::Fsm SERVER_STOPED"  << std::endl;
        break;



////-----------------------------------------------------------------------------------------
//// GooseClient
// GooseClient
    case CLIENT_START:
//        std::cout << "CGooseEthernet::Fsm CLIENT_START"  << std::endl;
        ReceiveDisable();
        ReceiveEnable();
        SetFsmState(CLIENT_IDDLE_STATE_PREPARE);
        break;

    case CLIENT_DATA_RECEIVE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm CLIENT_DATA_RECEIVE_PREPARE"  << std::endl;
        SetMessageLength(0);
        SetFsmState(CLIENT_DATA_RECEIVE_WAITING);
        break;

    case CLIENT_DATA_RECEIVE_WAITING:
//        std::cout << "CGooseEthernet::Fsm CLIENT_DATA_RECEIVE_WAITING"  << std::endl;
        iBytesNumber = Receive((GetRxBuffer() + GetMessageLength()), (GOOSE_ETHERNET_MAX_FRAME_LENGTH - GetMessageLength()));

        if (iBytesNumber > 0)
        {
            SetMessageLength(GetMessageLength() + iBytesNumber);
            SetFsmState(CLIENT_RECEIVED_DATA_PROCESSING);
        }
        else
        {
            SetFsmState(CLIENT_RECEIVED_DATA_ERROR_PROCESSING);
        }
        break;

    case CLIENT_RECEIVED_DATA_PROCESSING:
//        std::cout << "CGooseEthernet::Fsm CLIENT_RECEIVED_DATA_PROCESSING"  << std::endl;
        if (AnswerProcessing(GetRxBuffer(), GetMessageLength()))
        {
            SetFsmState(CLIENT_IDDLE_STATE_PREPARE);
        }
        else
        {
            SetFsmState(CLIENT_IDDLE_STATE_PREPARE);
        }
        break;

    case CLIENT_RECEIVED_DATA_ERROR_PROCESSING:
//        std::cout << "CGooseEthernet::Fsm CLIENT_RECEIVED_DATA_ERROR_PROCESSING"  << std::endl;
        SetFsmState(CLIENT_IDDLE_STATE_PREPARE);
        break;

    case CLIENT_DATA_TRANSMIT_PREPARE:
//        std::cout << "CGooseEthernet::Fsm CLIENT_DATA_TRANSMIT_PREPARE"  << std::endl;
//        ReportSlaveIDRequest(7);
//
//        usleep(GetPeriodTime());

//        // получим время начала замера
//        xTimeMeasure.Begin();
//
//        Send(GetTxBuffer(), GetMessageLength());
//
//        // увеличим количество отправленных пакетов
//        GetGooseServerObserver() ->
//        SetTransmitPacketNumber(GetGooseServerObserver() ->
//                                GetTransmitPacketNumber() + 1);

        SetFsmState(CLIENT_DATA_TRANSMIT);
        break;

    case CLIENT_DATA_TRANSMIT:
//        std::cout << "CGooseEthernet::Fsm CLIENT_DATA_TRANSMIT"  << std::endl;
        // получим время начала замера
        xTimeMeasure.Begin();

        Send(GetTxBuffer(), GetMessageLength());

        // увеличим количество отправленных пакетов
        GetGooseServerObserver() ->
        SetTransmitPacketNumber(GetGooseServerObserver() ->
                                GetTransmitPacketNumber() + 1);

        SetFsmState(CLIENT_DATA_RECEIVE_PREPARE);
        break;

    case CLIENT_IDDLE_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm CLIENT_IDDLE_STATE_PREPARE"  << std::endl;
        SetFsmState(CLIENT_IDDLE);
        break;

    case CLIENT_IDDLE:
//        std::cout << "CGooseEthernet::Fsm CLIENT_IDDLE"  << std::endl;
//        Sleep();
        break;

    case CLIENT_STOP_STATE_PREPARE:
//        std::cout << "CGooseEthernet::Fsm CLIENT_STOP_STATE_PREPARE"  << std::endl;
        ReceiveDisable();
        SetFsmState(CLIENT_STOPED);
        break;

    case CLIENT_STOPED:
//        std::cout << "CGooseEthernet::Fsm CLIENT_STOPED"  << std::endl;
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------
