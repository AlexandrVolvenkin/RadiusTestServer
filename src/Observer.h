#ifndef COBSERVER_H
#define COBSERVER_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

#include "Platform.h"
#include "Task.h"

//-----------------------------------------------------------------------------------------
class CObserverInterface
{
public:

};
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CObserver : public CObserverInterface
{
public:
    CObserver();
    virtual ~CObserver();

protected:

private:
};
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseServerObserver// : public CObserver
{
public:
    CGooseServerObserver();
    virtual ~CGooseServerObserver();

    void Reset(void);
    void CalculateLostPacketNumber(uint16_t uiIndex);

    void SetTransmitPacketNumber(uint32_t uiData)
    {
        m_uiTransmitPacketNumber = uiData;
    }
    uint32_t GetTransmitPacketNumber(void)
    {
        return m_uiTransmitPacketNumber;
    }

    void SetReceivePacketNumber(uint32_t uiData)
    {
        m_uiReceivePacketNumber = uiData;
    }
    uint32_t GetReceivePacketNumber(void)
    {
        return m_uiReceivePacketNumber;
    }

    void SetLostPacketNumber(uint32_t uiData)
    {
        m_uiLostPacketNumber = uiData;
    }
    uint32_t GetLostPacketNumber(void)
    {
        return m_uiLostPacketNumber;
    }


    void SetMinReceivePacketTimeout(uint32_t uiData)
    {
        m_uiMinReceivePacketTimeout = uiData;
    }
    uint32_t GetMinReceivePacketTimeout(void)
    {
        return m_uiMinReceivePacketTimeout;
    }

    void SetMaxReceivePacketTimeout(uint32_t uiData)
    {
        m_uiMaxReceivePacketTimeout = uiData;
    }
    uint32_t GetMaxReceivePacketTimeout(void)
    {
        return m_uiMaxReceivePacketTimeout;
    }

    void SetAverageReceivePacketTimeout(uint32_t uiData)
    {
        m_uiAverageReceivePacketTimeout = uiData;
    }
    uint32_t GetAverageReceivePacketTimeout(void)
    {
        return m_uiAverageReceivePacketTimeout;
    }

    void SetCommonReceivePacketTimeout(uint32_t uiData)
    {
        m_uiCommonReceivePacketTimeout = uiData;
    }
    uint32_t GetCommonReceivePacketTimeout(void)
    {
        return m_uiCommonReceivePacketTimeout;
    }

    void SetCommonReceivePacketNumber(uint32_t uiData)
    {
        m_uiCommonReceivePacketNumber = uiData;
    }
    uint32_t GetCommonReceivePacketNumber(void)
    {
        return m_uiCommonReceivePacketNumber;
    }

    void SetLastReceivedPacketIndex(uint16_t uiData)
    {
        m_uiLastReceivedPacketIndex = uiData;
    }
    uint16_t GetLastReceivedPacketIndex(void)
    {
        return m_uiLastReceivedPacketIndex;
    }

    void SetCommonStatisticsOutCounter(uint32_t uiData)
    {
        m_uiCommonStatisticsOutCounter = uiData;
    }
    uint32_t GetCommonStatisticsOutCounter(void)
    {
        return m_uiCommonStatisticsOutCounter;
    }

private:
    uint32_t m_uiTransmitPacketNumber;
    uint32_t m_uiReceivePacketNumber;
    uint32_t m_uiLostPacketNumber;

    uint32_t m_uiMinReceivePacketTimeout;
    uint32_t m_uiMaxReceivePacketTimeout;
    uint32_t m_uiAverageReceivePacketTimeout;
    uint32_t m_uiCommonReceivePacketTimeout;
    uint32_t m_uiCommonReceivePacketNumber;

    uint16_t m_uiLastReceivedPacketIndex;
    uint32_t m_uiCommonStatisticsOutCounter;
};
//-----------------------------------------------------------------------------------------








////-----------------------------------------------------------------------------------------
//class CGooseClientObserver : public CGooseServerObserver
//{
//public:
//    CGooseClientObserver();
//    virtual ~CGooseClientObserver();
//
//    void SetMinReceivePacketTimeout(uint32_t uiData)
//    {
//        m_uiMinReceivePacketTimeout = uiData;
//    }
//    uint32_t GetMinReceivePacketTimeout(void)
//    {
//        return m_uiMinReceivePacketTimeout;
//    }
//
//    void SetMaxReceivePacketTimeout(uint32_t uiData)
//    {
//        m_uiMaxReceivePacketTimeout = uiData;
//    }
//    uint32_t GetMaxReceivePacketTimeout(void)
//    {
//        return m_uiMaxReceivePacketTimeout;
//    }
//
//    void SetAverageReceivePacketTimeout(uint32_t uiData)
//    {
//        m_uiAverageReceivePacketTimeout = uiData;
//    }
//    uint32_t GetAverageReceivePacketTimeout(void)
//    {
//        return m_uiAverageReceivePacketTimeout;
//    }
//
//private:
//    uint32_t m_uiMinReceivePacketTimeout;
//    uint32_t m_uiMaxReceivePacketTimeout;
//    uint32_t m_uiAverageReceivePacketTimeout;
//};
////-----------------------------------------------------------------------------------------

#endif // COBSERVER_H
