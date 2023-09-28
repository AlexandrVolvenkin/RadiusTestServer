//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Goose.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------
CGoose::CGoose()
{
    std::cout << "CGoose constructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
CGoose::~CGoose()
{
    std::cout << "CGoose desstructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::ResponseException(uint8_t uiSlave,
                                   uint8_t uiFunctionCode,
                                   uint8_t uiExceptionCode,
                                   uint8_t *puiResponse)
{
    uint16_t uiLength;
    uiLength = ResponseBasis(uiSlave,
                             (uiFunctionCode | 0x80),
                             puiResponse);
    puiResponse[uiLength++] = uiExceptionCode;

    return uiLength;
}

////-----------------------------------------------------------------------------------------
//void CGoose::SlaveSet(uint8_t uiSlave)
//{
//    m_uiOwnAddress = uiSlave;
//}

//-----------------------------------------------------------------------------------------------------
uint16_t CGoose::ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength)
{
    std::cout << "CGoose::ReportSlaveID"  << std::endl;
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset];
    int8_t uiFunctionCode = puiRequest[uiOffset + 1];


    // увеличим количество принятых пакетов
    GetGooseServerObserver() ->
    SetReceivePacketNumber(GetGooseServerObserver() ->
                           GetReceivePacketNumber() + 1);

    // получим индекс пакета
    uint16_t uiIndex = 0;
    // младштй байт
    uiIndex = (uint16_t)(puiRequest[sizeof(struct ether_header) + 1]);
    // старший байт
    uiIndex |= ((uint16_t)(puiRequest[sizeof(struct ether_header)]) << 8);
    GetGooseServerObserver() ->
    CalculateLostPacketNumber(uiIndex);
    GetGooseServerObserver() ->
    SetLastReceivedPacketIndex(uiIndex);
    // Это не первый принятый пакет?
    if (GetGooseServerObserver() ->
            GetReceivePacketNumber())
    {

    }


    uiLength = ResponseBasis(uiSlave,
                             uiFunctionCode,
                             puiResponse);

    // установим идентификатор устройства
    puiResponse[uiLength++] = 1;
    puiResponse[uiLength++] = 50;

    return uiLength;
}

//-----------------------------------------------------------------------------------------
// Server
uint16_t CGoose::RequestProcessing(uint8_t *puiRequest,
                                   uint8_t *puiResponse,
                                   uint16_t uiFrameLength)
{
//    std::cout << "CGoose::RequestProcessing"  << std::endl;
    uint16_t uiLength = uiFrameLength;
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset];
    int8_t uiFunctionCode = puiRequest[uiOffset + 1];

    /* Filter on the Modbus unit identifier (slave) in RTU mode */
    if (uiSlave != m_uiOwnAddress && uiSlave != 0)
    {
        std::cout << "CGoose::RequestProcessing uiSlave != m_uiOwnAddress"  << std::endl;
        return 0;
    }

    struct ether_header* pxEthernetHeader;
    pxEthernetHeader = (struct ether_header*)puiRequest;
    GetCommunicationDevice() ->
    SetDestinationMacAddress(pxEthernetHeader -> ether_shost);

    switch (uiFunctionCode)
    {
    case _FC_REPORT_SLAVE_ID:
        std::cout << "CGoose::RequestProcessing _FC_REPORT_SLAVE_ID"  << std::endl;
        uiLength = ReportSlaveID(puiRequest, puiResponse, uiLength);
        break;

    default:
//        std::cout << "CGoose::RequestProcessing default"  << std::endl;
        uiLength = ResponseException(uiSlave,
                                     uiFunctionCode,
                                     MODBUS_EXCEPTION_ILLEGAL_FUNCTION,
                                     puiResponse);
        return 0;
        break;
    }

    m_uiMessageLength = uiLength;
    return uiLength;
}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
// Client
int8_t CGoose::ReportSlaveIDRequest(uint8_t uiSlaveAddress)
{
    usleep(500);
//    if (MessengerIsReady())
//    {
    m_uiSlaveAddress = uiSlaveAddress;
    m_uiFunctionCode = _FC_REPORT_SLAVE_ID;
    m_uiMessageLength = RequestBasis(uiSlaveAddress,
                                     m_uiFunctionCode,
                                     GetTxBuffer());
    SetFsmState(FRAME_TRANSMIT_REQUEST);
    return 1;
//    }
//    else
//    {
//        return 0;
//    }
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::ReportSlaveIDReceive(uint8_t *puiMessage, uint16_t uiLength)
{
    return 1;
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength)
{
    uint16_t uiLength = uiFrameLength;
    uint16_t uiOffset = HEADER_LENGTH();
    uint8_t uiSlave = puiResponse[uiOffset];
    uint8_t uiFunctionCode = puiResponse[uiOffset + 1];

    if ((m_uiSlaveAddress == uiSlave) &&
            (m_uiFunctionCode == uiFunctionCode))
    {
        switch (uiFunctionCode)
        {
        case _FC_REPORT_SLAVE_ID:
            break;

        default:
            break;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}
