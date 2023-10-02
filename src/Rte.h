#ifndef CRTE_H
#define CRTE_H
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
class CRteInterface
{
public:
};

//-----------------------------------------------------------------------------------------









//-----------------------------------------------------------------------------------------
class CRte : public CTask
{
public:

    enum
    {
        IDDLE = 0,
        START,
        FULL_LOAD_MODE_START,
        FULL_LOAD_MODE,
        STANDBY_MODE_START,
        STANDBY_MODE,
        STOP,
    };

    CRte();
    virtual ~CRte();

    void Fsm(void);


    CSerialPort* GetCommunicationDevice(void)
    {
        return m_pxCommunicationDevice;
    };

    void SetPeriodTime(uint32_t uiValue)
    {
        m_uiPeriodTime = uiValue;
    };
    uint32_t GetPeriodTime(void)
    {
        return m_uiPeriodTime;
    };

    void SetLoadPercent(uint8_t uiValue)
    {
        m_uiLoadPercent = uiValue;
    };
    uint8_t GetLoadPercent(void)
    {
        return m_uiLoadPercent;
    };

private:
    CSerialPort* m_pxCommunicationDevice;
    uint32_t m_uiPeriodTime;
    uint8_t m_uiLoadPercent;
    CTimeMeasure m_xTimeMeasure;
};

//-----------------------------------------------------------------------------------------
#endif // CRTE_H
