//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Representation.h"
#include "Platform.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
CRepresentation::CRepresentation()
{
    //ctor
}

//-----------------------------------------------------------------------------------------
CRepresentation::~CRepresentation()
{
    //dtor
}

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
CGooseConsoleRepresentation::CGooseConsoleRepresentation()
{
    //ctor
}

//-----------------------------------------------------------------------------------------
CGooseConsoleRepresentation::~CGooseConsoleRepresentation()
{
    //dtor
}

//-----------------------------------------------------------------------------------------
void CGooseConsoleRepresentation::Show(void)
{

//    std::cout << "CGooseConsoleRepresentation::Show statistics"  << std::endl;
    std::cout << std::endl;
    std::cout << "//----------------------------------------" << std::endl;
    std::cout << "Statistics session window: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetCommonStatisticsOutCounter() << std::endl;
    std::cout << std::endl;
    std::cout << "Server" << std::endl;
//    std::cout << std::endl;
//        std::cout << "Last packet index: " << (int)GetGooseServerObserver() -> GetLastReceivedPacketIndex() << std::endl;
    std::cout << "Transmited: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetTransmitPacketNumber() << std::endl;
    std::cout << "Received: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetReceivePacketNumber() << std::endl;
    std::cout << "Lost: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetLostPacketNumber() << std::endl;
//    std::cout << "Min: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetMinReceivePacketTimeout() << std::endl;
//    std::cout << "Max: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetMaxReceivePacketTimeout() << std::endl;
//    std::cout << "Average: " << (uint)GetGooseServerStatistics() -> GetGooseServerObserver() -> GetAverageReceivePacketTimeout() << std::endl;
    std::cout << std::endl;
//    std::cout << "//----------------------------------------" << std::endl;
//
//
//    std::cout << std::endl;
//    std::cout << "//----------------------------------------" << std::endl;
//    std::cout << "Client statistics session: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetCommonStatisticsOutCounter() << std::endl;
    std::cout << "Client" << std::endl;
//    std::cout << std::endl;
//        std::cout << "Last packet index: " << (int)GetGooseClientObserver() -> GetLastReceivedPacketIndex() << std::endl;
    std::cout << "Transmited: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetTransmitPacketNumber() << std::endl;
    std::cout << "Received: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetReceivePacketNumber() << std::endl;
    std::cout << "Lost: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetLostPacketNumber() << std::endl;
    std::cout << "Min: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetMinReceivePacketTimeout() << std::endl;
    std::cout << "Max: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetMaxReceivePacketTimeout() << std::endl;
    std::cout << "Average: " << (uint)GetGooseServerStatistics() -> GetGooseClientObserver() -> GetAverageReceivePacketTimeout() << std::endl;
    std::cout << std::endl;
    std::cout << "//----------------------------------------" << std::endl;

}

//-----------------------------------------------------------------------------------------
