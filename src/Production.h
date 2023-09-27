#ifndef CPRODUCTION_H
#define CPRODUCTION_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>
#include <thread>

#include "Goose.h"
#include "MainProductionCycle.h"

//-----------------------------------------------------------------------------------------
class CProductionInterface
{
public:
//    virtual void Create(void) {};
//    virtual void Create(CGooseInterface* pxGooseInterface) {};
    virtual void Place(CGooseInterface* pxGooseInterface) {};
//    virtual void Start(void) {};
//    virtual void Stop(void) {};
//    static void Process(void) {};
    static void Process(CGooseInterface* pxGooseInterface) {};

    virtual void Place(CMainProductionCycleInterface* pxMainProductionCycleInterface) {};
    static void Process(CMainProductionCycleInterface* pxMainProductionCycleInterface) {};
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CProduction : public CProductionInterface
{
public:
    CProduction();
    virtual ~CProduction();

//    void Create(void);
//    void Place(void);
//    void Start(void);
//    void Stop(void);
//    static void Process(void);

protected:

private:
//    std::thread x
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CMainThreadProduction : public CProduction
{
public:
    CMainThreadProduction();
    virtual ~CMainThreadProduction();

    void Place(CMainProductionCycleInterface* pxMainProductionCycleInterface);
    static void Process(CMainProductionCycleInterface* pxMainProductionCycleInterface);

protected:

private:
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CGooseThreadProduction : public CProduction
{
public:
    CGooseThreadProduction();
    virtual ~CGooseThreadProduction();

//    void Create(CGooseInterface* pxGooseInterface);
    void Place(CGooseInterface* pxGooseInterface);
//    void Start(void);
//    void Stop(void);
    static void Process(CGooseInterface* pxGooseInterface);

protected:

private:
    std::thread m_xThread;
};

//-----------------------------------------------------------------------------------------
#endif // CPRODUCTION_H
