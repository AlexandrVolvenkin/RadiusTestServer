//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Goose.h"
#include "Platform.h"
#include "Modbus.h"

using namespace std;
extern CTimeMeasure xTimeMeasure;
//-----------------------------------------------------------------------------------------
CGoose::CGoose()
{
//    std::cout << "CGoose constructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
CGoose::~CGoose()
{
//    std::cout << "CGoose desstructor"  << std::endl;
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
uint16_t CGoose::ReadHoldingRegisters(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength)
{
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];
    uint16_t uiAddress = ((static_cast<uint16_t>(puiRequest[uiOffset + 1]) << 8) |
                          (static_cast<uint16_t>(puiRequest[uiOffset + 2])));

    uint16_t uiNumberB = ((static_cast<uint16_t>(puiRequest[uiOffset + 3]) << 8) |
                          (static_cast<uint16_t>(puiRequest[uiOffset + 4])));

    if (uiNumberB < 1 || MODBUS_MAX_READ_REGISTERS < uiNumberB)
    {
        uiLength = ResponseException(uiSlave,
                                     uiFunctionCode,
                                     MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
                                     puiResponse);
    }
    else if ((uiAddress + uiNumberB) > m_uiHoldingRegistersNumber)
    {
        uiLength = ResponseException(uiSlave,
                                     uiFunctionCode,
                                     MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
                                     puiResponse);
    }
    else
    {
        uiLength = ResponseBasis(uiSlave, uiFunctionCode, puiResponse);
        puiResponse[uiLength++] = (uiNumberB << 1);
        for (uint16_t i = 0; i < uiNumberB; i++)
        {
//            int8_t uiData = 0;
//            uiData = (static_cast<uint8_t>(m_pui16HoldingRegisters[uiAddress] >> 8));
//            uiData = (static_cast<uint8_t>(m_pui16HoldingRegisters[uiAddress] & 0x00FF));
            puiResponse[uiLength++] = (static_cast<uint8_t>(m_pui16HoldingRegisters[uiAddress] >> 8));
            puiResponse[uiLength++] = (static_cast<uint8_t>(m_pui16HoldingRegisters[uiAddress] & 0x00FF));
            uiAddress++;
        }
    }

    return uiLength;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CGoose::ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength)
{
//    std::cout << "CGoose::ReportSlaveID"  << std::endl;
//    uint16_t uiOffset = HEADER_LENGTH();
//    int8_t uiSlave = puiRequest[uiOffset];
//    int8_t uiFunctionCode = puiRequest[uiOffset + 1];

    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];



//    uint16_t uiIndex = 0;
//    // Это не первый принятый пакет?
//    if (GetGooseServerObserver() ->
//            GetReceivePacketNumber())
//    {
//        // получим индекс пакета
//        // младштй байт
//        uiIndex = (uint16_t)(puiRequest[sizeof(struct ether_header) + 1]);
//        // старший байт
//        uiIndex |= ((uint16_t)(puiRequest[sizeof(struct ether_header)]) << 8);
//
//        // не было потери пакета?
//        if ((uiIndex - 1) ==
//                GetGooseServerObserver() ->
//                GetLastReceivedPacketIndex())
//        {
//            // получим время окончания замера
//            uint32_t uiTime = xTimeMeasure.End();
//            // при получении времени не произошло ошибок?
//            if (uiTime)
//            {
//                // результат текущего измерения времени меньше минимального значения?
//                if (uiTime <
//                        GetGooseServerObserver() ->
//                        GetMinReceivePacketTimeout())
//                {
//                    // сохраним новое минимального значение
//                    GetGooseServerObserver() ->
//                    SetMinReceivePacketTimeout(uiTime);
//                }
//
//                // результат текущего измерения времени больше максимального значения?
//                if (uiTime >
//                        GetGooseServerObserver() ->
//                        GetMaxReceivePacketTimeout())
//                {
//                    // сохраним новое максимальное значение
//                    GetGooseServerObserver() ->
//                    SetMaxReceivePacketTimeout(uiTime);
//                }
//
////                SetAverageReceivePacketTimeout(uint32_t uiData)
////                GetAverageReceivePacketTimeout(void)
//            }
//        }
//        else
//        {
//            // получим и вычислим количество потерянных пакетов
//            GetGooseServerObserver() ->
//            CalculateLostPacketNumber(uiIndex);
//        }
//    }
//
//    // сохраним индекс принятого пакета
//    GetGooseServerObserver() ->
//    SetLastReceivedPacketIndex(uiIndex);
//
//    // увеличим количество принятых пакетов
//    GetGooseServerObserver() ->
//    SetReceivePacketNumber(GetGooseServerObserver() ->
//                           GetReceivePacketNumber() + 1);
//
//    // получим время начала замера
//    xTimeMeasure.Begin();

    uiLength = ResponseBasis(uiSlave,
                             uiFunctionCode,
                             puiResponse);

    // установим идентификатор устройства
    puiResponse[uiLength++] = 3;
    puiResponse[uiLength++] = 14;

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
//    uint16_t uiOffset = HEADER_LENGTH();
//    int8_t uiSlave = puiRequest[uiOffset];
//    int8_t uiFunctionCode = puiRequest[uiOffset + 1];

    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];

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

    case _FC_READ_HOLDING_REGISTERS:
        uiLength = ReadHoldingRegisters(puiRequest, puiResponse, uiLength);
        break;

    case _FC_REPORT_SLAVE_ID:
//        std::cout << "CGoose::RequestProcessing _FC_REPORT_SLAVE_ID"  << std::endl;
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
    usleep(GetPeriodTime());
    if (MessengerIsReady())
    {
        m_uiSlaveAddress = uiSlaveAddress;
        m_uiFunctionCode = _FC_REPORT_SLAVE_ID;
        uint8_t *puiRequest = GetTxBuffer();

        m_uiMessageLength = RequestBasis(uiSlaveAddress,
                                         m_uiFunctionCode,
                                         puiRequest);

        SetFsmState(CLIENT_DATA_TRANSMIT_PREPARE);
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::ReportSlaveIDReceive(uint8_t *puiResponse, uint16_t uiLength)
{
//    std::cout << "CGoose::ReportSlaveIDReceive"  << std::endl;
//    uint16_t uiOffset = HEADER_LENGTH();
//    int8_t uiSlave = puiResponse[uiOffset];
//    int8_t uiFunctionCode = puiResponse[uiOffset + 1];

    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiResponse[uiOffset - 1];
    int8_t uiFunctionCode = puiResponse[uiOffset];


    uint16_t uiIndex = 0;
    // получим индекс пакета
    // младштй байт
    uiIndex = (uint16_t)(puiResponse[sizeof(struct ether_header) + 1]);
    // старший байт
    uiIndex |= ((uint16_t)(puiResponse[sizeof(struct ether_header)]) << 8);

    // Это не первый принятый пакет?
    if (GetGooseServerObserver() ->
            GetReceivePacketNumber() > 1)
    {
        // не было потери пакета?
        if ((uiIndex - 1) ==
                GetGooseServerObserver() ->
                GetLastReceivedPacketIndex())
        {
            // получим время окончания замера
            uint32_t uiTime = xTimeMeasure.End();
//    std::cout << "CGoose::ReportSlaveIDReceive xTimeMeasure.End()"  << (int)uiTime  << std::endl;
            // при получении времени не произошло ошибок?
            if (uiTime)
            {
                // результат текущего измерения времени меньше минимального значения?
                if (uiTime <
                        GetGooseServerObserver() ->
                        GetMinReceivePacketTimeout())
                {
                    // сохраним новое минимального значение
                    GetGooseServerObserver() ->
                    SetMinReceivePacketTimeout(uiTime);
                }

                // результат текущего измерения времени больше максимального значения?
                if (uiTime >
                        GetGooseServerObserver() ->
                        GetMaxReceivePacketTimeout())
                {
                    // сохраним новое максимальное значение
                    GetGooseServerObserver() ->
                    SetMaxReceivePacketTimeout(uiTime);
                }

                // суммируем с общим временем отклика всех пакетов
                GetGooseServerObserver() ->
                SetCommonReceivePacketTimeout(GetGooseServerObserver() ->
                                              GetCommonReceivePacketTimeout() + uiTime);

                // увеличим количество успешно принятых пакетов за сессию вывода статистики - 1с
                GetGooseServerObserver() ->
                SetCommonReceivePacketNumber(GetGooseServerObserver() ->
                                             GetCommonReceivePacketNumber() + 1);

            }
        }
        else
        {
            // получим и вычислим количество потерянных пакетов
            GetGooseServerObserver() ->
            CalculateLostPacketNumber(uiIndex);
        }
    }

    // сохраним индекс принятого пакета
    GetGooseServerObserver() ->
    SetLastReceivedPacketIndex(uiIndex);

    // увеличим количество принятых пакетов
    GetGooseServerObserver() ->
    SetReceivePacketNumber(GetGooseServerObserver() ->
                           GetReceivePacketNumber() + 1);
//    // увеличим количество отправленных пакетов
//    GetGooseServerObserver() ->
//    SetTransmitPacketNumber(GetGooseServerObserver() ->
//                            GetTransmitPacketNumber() + 1);

    if ((GetTimerPointer() -> IsOverflow()))
    {
        // вычислим среднее время отклика
        GetGooseServerObserver() ->
        SetAverageReceivePacketTimeout(GetGooseServerObserver() ->
                                       GetCommonReceivePacketTimeout() /
                                       GetGooseServerObserver() ->
                                       GetCommonReceivePacketNumber());

        // очистим общее время отклика всех пакетов за сессию вывода статистики - 1с
        GetGooseServerObserver() ->
        SetCommonReceivePacketTimeout(0);
        // очистим количество успешно принятых пакетов за сессию вывода статистики - 1с
        GetGooseServerObserver() ->
        SetCommonReceivePacketNumber(0);

        std::cout << std::endl;
        std::cout << "//----------------------------------------" << std::endl;
        std::cout << "Client statistics session: " << (uint)GetGooseServerObserver() -> GetCommonStatisticsOutCounter() << std::endl;
        std::cout << std::endl;
//        std::cout << "Last packet index: " << (int)GetGooseServerObserver() -> GetLastReceivedPacketIndex() << std::endl;
        std::cout << "Transmited: " << (uint)GetGooseServerObserver() -> GetTransmitPacketNumber() << std::endl;
        std::cout << "Received: " << (uint)GetGooseServerObserver() -> GetReceivePacketNumber() << std::endl;
        std::cout << "Lost: " << (uint)GetGooseServerObserver() -> GetLostPacketNumber() << std::endl;
        std::cout << "Min: " << (uint)GetGooseServerObserver() -> GetMinReceivePacketTimeout() << std::endl;
        std::cout << "Max: " << (uint)GetGooseServerObserver() -> GetMaxReceivePacketTimeout() << std::endl;
        std::cout << "Average: " << (uint)GetGooseServerObserver() -> GetAverageReceivePacketTimeout() << std::endl;
        std::cout << std::endl;
        std::cout << "//----------------------------------------" << std::endl;

        // увеличим номер сессии вывода статистики
        GetGooseServerObserver() ->
        SetCommonStatisticsOutCounter(GetGooseServerObserver() ->
                                      GetCommonStatisticsOutCounter() + 1);

        GetTimerPointer() -> Set(1000);
    }

    return 1;
}

//-----------------------------------------------------------------------------------------
// Client
int8_t CGoose::ReadHoldingRegistersRequest(uint8_t uiSlaveAddress,
        uint16_t uiAddress,
        uint16_t uiNumber,
        uint16_t* puiDestination)
{

    if (uiNumber > MODBUS_MAX_READ_REGISTERS)
    {
        return 0;
    }

    if (MessengerIsReady())
    {
        m_uiSlaveAddress = uiSlaveAddress;
        m_uiFunctionCode = _FC_READ_HOLDING_REGISTERS;
        m_pui16Destination = puiDestination;
        uint8_t *puiRequest = GetTxBuffer();

        m_uiMessageLength = RequestBasis(uiSlaveAddress,
                                         m_uiFunctionCode,
                                         puiRequest);

        puiRequest[m_uiMessageLength++] = (static_cast<uint8_t>(uiAddress >> 8));
        puiRequest[m_uiMessageLength++] = (static_cast<uint8_t>(uiAddress & 0x00ff));
        puiRequest[m_uiMessageLength++] = (static_cast<uint8_t>(uiNumber >> 8));
        puiRequest[m_uiMessageLength++] = (static_cast<uint8_t>(uiNumber & 0x00ff));

        SetFsmState(CLIENT_DATA_TRANSMIT_PREPARE);
        return 1;
    }
    else
    {
        return 0;
    }
}
//-----------------------------------------------------------------------------------------
uint16_t CGoose::ReadHoldingRegistersReceive(uint8_t *puiResponse, uint16_t uiLength)
{
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiResponse[uiOffset - 1];
    int8_t uiFunctionCode = puiResponse[uiOffset];
    uint16_t uiNumber = puiResponse[uiOffset + 1];

    for (uint16_t i, j = 0; i < (uiNumber / 2); i++, j + 2)
    {
        m_pui16Destination[i] = (puiResponse[uiOffset + 2 +j] << 8) |
                                puiResponse[uiOffset + 3 + j];
    }

    return uiNumber;
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength)
{
    uint16_t uiLength = uiFrameLength;
//    uint16_t uiOffset = HEADER_LENGTH();
//    uint8_t uiSlave = puiResponse[uiOffset];
//    uint8_t uiFunctionCode = puiResponse[uiOffset + 1];

    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiResponse[uiOffset - 1];
    int8_t uiFunctionCode = puiResponse[uiOffset];


//    std::cout << "CGoose::AnswerProcessing uiLength " << (int)uiLength << std::endl;
//    std::cout << "CGoose::AnswerProcessing m_uiSlaveAddress " << (int)m_uiSlaveAddress << std::endl;
//    std::cout << "CGoose::AnswerProcessing uiSlave " << (int)uiSlave << std::endl;
//    std::cout << "CGoose::AnswerProcessing m_uiFunctionCode " << (int)m_uiFunctionCode << std::endl;
//    std::cout << "CGoose::AnswerProcessing uiFunctionCode " << (int)uiFunctionCode << std::endl;

    // (uiFunctionCode & 0x7f) при формировании ответа об исключительной ситуации
    // сервер добавляет старший бит - 0x80. здесь его нужно очистить перед проверкой
    if ((m_uiSlaveAddress == uiSlave) &&
            (m_uiFunctionCode == (uiFunctionCode & 0x7f)))
    {
        switch (uiFunctionCode)
        {
        case _FC_REPORT_SLAVE_ID:
//            std::cout << "CGoose::AnswerProcessing _FC_REPORT_SLAVE_ID"  << std::endl;
            ReportSlaveIDReceive(puiResponse, uiLength);
            break;
//
        case _FC_READ_HOLDING_REGISTERS:
            ReadHoldingRegistersReceive(puiResponse, uiLength);
            break;

        default:
            std::cout << "CGoose::AnswerProcessing default"  << std::endl;
            break;
        }

        return 1;
    }
//    // (uiFunctionCode & 0x7f) при формировании ответа об исключительной ситуации
//    // сервер добавляет старший бит - 0x80. здесь его нужно очистить перед проверкой
//    else if (uiLength == (uiOffset + 2 + CRC_LENGTH()) &&
//             (uiFunctionCode & 0x7f))
//    {
//        /* EXCEPTION CODE RECEIVED */
//        int8_t uiExceptionCode =
//            puiResponse[uiOffset + MODBUS_EXCEPTION_CODE_OFFSET];
//        if (uiExceptionCode < MODBUS_EXCEPTION_MAX)
//        {
//            return MODBUS_ENOBASE + uiExceptionCode;
//        }
//        else
//        {
//            return EMBBADEXC;
//        }
//    }
    else
    {
//        std::cout << "CGoose::AnswerProcessing if ((m_uiSlaveAddress == uiSlave)"  << std::endl;
//
//        cout << "CGoose::AnswerProcessing Read" << endl;
//        unsigned char *pucSourceTemp;
//        pucSourceTemp = (unsigned char*)puiResponse;
//        for(int i=0; i<32; )
//        {
//            for(int j=0; j<8; j++)
//            {
//                cout << hex << uppercase << setw(2) << setfill('0') << (unsigned int)pucSourceTemp[i + j] << " ";
//            }
//            cout << endl;
//            i += 8;
//        }
//
        return 0;
    }
}
