//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Goose.h"
#include "Platform.h"

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
uint16_t CGoose::ReportSlaveID(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiLength)
{
//    std::cout << "CGoose::ReportSlaveID"  << std::endl;
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiRequest[uiOffset];
    int8_t uiFunctionCode = puiRequest[uiOffset + 1];



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
uint16_t CGoose::ReportSlaveIDReceive(uint8_t *puiResponse, uint16_t uiLength)
{
//    std::cout << "CGoose::ReportSlaveIDReceive"  << std::endl;
    uint16_t uiOffset = HEADER_LENGTH();
    int8_t uiSlave = puiResponse[uiOffset];
    int8_t uiFunctionCode = puiResponse[uiOffset + 1];


    uint16_t uiIndex = 0;
    // Это не первый принятый пакет?
    if (GetGooseServerObserver() ->
            GetReceivePacketNumber())
    {
        // получим индекс пакета
        // младштй байт
        uiIndex = (uint16_t)(puiResponse[sizeof(struct ether_header) + 1]);
        // старший байт
        uiIndex |= ((uint16_t)(puiResponse[sizeof(struct ether_header)]) << 8);

        // не было потери пакета?
        if ((uiIndex - 1) ==
                GetGooseServerObserver() ->
                GetLastReceivedPacketIndex())
        {
            // получим время окончания замера
            uint32_t uiTime = xTimeMeasure.End();
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
                                       GetReceivePacketNumber());

        std::cout << std::endl;
        std::cout << "//----------------------------------------" << std::endl;
        std::cout << "Client statistics session: " << (int)GetGooseServerObserver() -> GetCommonStatisticsOutCounter() << std::endl;
        std::cout << std::endl;
//        std::cout << "Last packet index: " << (int)GetGooseServerObserver() -> GetLastReceivedPacketIndex() << std::endl;
        std::cout << "Transmited: " << (int)GetGooseServerObserver() -> GetTransmitPacketNumber() << std::endl;
        std::cout << "Received: " << (int)GetGooseServerObserver() -> GetReceivePacketNumber() << std::endl;
        std::cout << "Lost: " << (int)GetGooseServerObserver() -> GetLostPacketNumber() << std::endl;
        std::cout << "Min: " << (int)GetGooseServerObserver() -> GetMinReceivePacketTimeout() << std::endl;
        std::cout << "Max: " << (int)GetGooseServerObserver() -> GetMaxReceivePacketTimeout() << std::endl;
        std::cout << "Average: " << (int)GetGooseServerObserver() -> GetAverageReceivePacketTimeout() << std::endl;
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
uint16_t CGoose::AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength)
{
    uint16_t uiLength = uiFrameLength;
    uint16_t uiOffset = HEADER_LENGTH();
    uint8_t uiSlave = puiResponse[uiOffset];
    uint8_t uiFunctionCode = puiResponse[uiOffset + 1];


//    std::cout << "CGoose::AnswerProcessing uiLength " << (int)uiLength << std::endl;
//    std::cout << "CGoose::AnswerProcessing m_uiSlaveAddress " << (int)m_uiSlaveAddress << std::endl;
//    std::cout << "CGoose::AnswerProcessing uiSlave " << (int)uiSlave << std::endl;
//    std::cout << "CGoose::AnswerProcessing m_uiFunctionCode " << (int)m_uiFunctionCode << std::endl;
//    std::cout << "CGoose::AnswerProcessing uiFunctionCode " << (int)uiFunctionCode << std::endl;

    if ((m_uiSlaveAddress == uiSlave) &&
            (m_uiFunctionCode == uiFunctionCode))
    {
        switch (uiFunctionCode)
        {
        case _FC_REPORT_SLAVE_ID:
//            std::cout << "CGoose::AnswerProcessing _FC_REPORT_SLAVE_ID"  << std::endl;
            ReportSlaveIDReceive(puiResponse, uiLength);
            break;

        default:
            std::cout << "CGoose::AnswerProcessing default"  << std::endl;
            break;
        }

        return 1;
    }
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
