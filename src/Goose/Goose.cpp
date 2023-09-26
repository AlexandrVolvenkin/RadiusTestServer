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
uint16_t CGoose::ResponseException(uint8_t uiSlave, uint8_t uiFunctionCode, uint8_t uiExceptionCode, uint8_t *puiResponse)
{
//    uint16_t uiLength;
//    SetHeader(uint8_t *puiResponse)
//    uiLength = ResponseBasis(uiSlave, (uiFunctionCode | 0x80), puiResponse);
//    /* Positive exception code */
//    puiResponse[uiLength++] = uiExceptionCode;
//
//    return uiLength;
}

//-----------------------------------------------------------------------------------------
void CGoose::SlaveSet(uint8_t uiSlave)
{
    m_uiOwnAddress = uiSlave;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGoose::ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength)
{
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];
//
//    uiLength = ResponseBasis(uiSlave, uiFunctionCode, puiResponse);
//    puiResponse[uiLength++] = 3;			// Число байт данных
//    puiResponse[uiLength++] = 32;			// Количество окон сигнализации
//    puiResponse[uiLength++] = 7;			// Код модификации
//    puiResponse[uiLength++] = 50;			// Код устройства
//
//    return uiLength;
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::RequestProcessing(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiFrameLength)
{
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];
    uint16_t uiLength = uiFrameLength;

//    /* Filter on the Modbus unit identifier (slave) in RTU mode */
//    if (uiSlave != m_uiOwnAddress && uiSlave != MODBUS_BROADCAST_ADDRESS)
//    {
//        return 0;
//    }

    switch (uiFunctionCode)
    {
    case _FC_REPORT_SLAVE_ID:
        uiLength = ReportSlaveID(puiRequest, puiResponse, uiLength);
        break;

    default:
        uiLength = ResponseException(uiSlave,
                                     uiFunctionCode,
                                     MODBUS_EXCEPTION_ILLEGAL_FUNCTION,
                                     puiResponse);
        break;
    }

    m_uiMessageLength = uiLength;
    return uiLength;
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength)
{

}
