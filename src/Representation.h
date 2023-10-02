#ifndef CREPRESENTATION_H
#define CREPRESENTATION_H
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
#include "Statistics.h"

//-----------------------------------------------------------------------------------------
class CRepresentationInterface
{
public:

    virtual void SetGooseServerStatistics(CStatisticsInterface* pxPointer) {};
    virtual CStatisticsInterface* GetGooseServerStatistics(void) {};
    virtual void Show(void) {};
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CRepresentation : public CRepresentationInterface
{
public:
    CRepresentation();
    virtual ~CRepresentation();

protected:

private:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseConsoleRepresentation : public CRepresentation
{
public:
    CGooseConsoleRepresentation();
    virtual ~CGooseConsoleRepresentation();
    void Show(void);

    void SetGooseServerStatistics(CStatisticsInterface* pxPointer)
    {
        m_pxGooseServerStatistics = pxPointer;
    };
    CStatisticsInterface* GetGooseServerStatistics(void)
    {
        return m_pxGooseServerStatistics;
    };

private:
    CStatisticsInterface* m_pxGooseServerStatistics;
};

//-----------------------------------------------------------------------------------------
#endif // CREPRESENTATION_H
