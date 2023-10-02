#ifndef CSTATISTICS_H
#define CSTATISTICS_H
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
#include "Observer.h"

//-----------------------------------------------------------------------------------------
class CStatisticsInterface
{
public:

    virtual void SetGooseServerObserver(CGooseServerObserver* pxPointer) {};
    virtual CGooseServerObserver* GetGooseServerObserver(void) {};
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CStatistics : public CStatisticsInterface
{
public:
    CStatistics();
    virtual ~CStatistics();

private:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseServerStatistics : public CStatistics
{
public:
    CGooseServerStatistics();
    virtual ~CGooseServerStatistics();

    void SetGooseServerObserver(CGooseServerObserver* pxPointer)
    {
        m_pxGooseServerObserver = pxPointer;
    };
    CGooseServerObserver* GetGooseServerObserver(void)
    {
        return m_pxGooseServerObserver;
    };

private:
    CGooseServerObserver* m_pxGooseServerObserver;
};

//-----------------------------------------------------------------------------------------
#endif // CSTATISTICS_H
