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
#include <chrono>

#include "Goose.h"
//#include "MainProductionCycle.h"
#include "Rte.h"

class CMainProductionCycleInterface;

//-----------------------------------------------------------------------------------------
class CProductionInterface
{
public:
    virtual void SetThread(std::thread* pxThread) {};
    virtual std::thread* GetThread(void) {};
//    virtual void SetThisThread(std::this_thread* pxThisThread) {};
//    virtual std::this_thread* GetThisThread(void) {};

//    virtual void Create(void) {};
//    virtual void Create(CGooseInterface* pxGooseInterface) {};
    virtual void Place(CGooseInterface* pxGooseInterface) {};
//    virtual void Start(void) {};
//    virtual void Stop(void) {};
//    static void Process(void) {};
    static void Process(CGooseInterface* pxGooseInterface) {};

    virtual void Place(CMainProductionCycleInterface* pxMainProductionCycleInterface) {};
    static void Process(CMainProductionCycleInterface* pxMainProductionCycleInterface) {};

    virtual void Place(CRte* pxRte) {};

    virtual void Sleep(void) {};
    virtual void Wakeup(void) {};

    static void Process(CRte* pxRte) {};
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
    void Sleep(void);
    void Wakeup(void);
//    static void Process(void);

    void SetThread(std::thread* pxThread)
    {
        m_pxThread = pxThread;
    };
    std::thread* GetThread(void)
    {
        return m_pxThread;
    };

//    void SetThisThread(std::this_thread* pxThisThread)
//    {
//        m_pxThisThread = pxThisThread;
//    };
//    std::this_thread* GetThisThread(void)
//    {
//        return m_pxThisThread;
//    };

protected:

private:
    std::thread* m_pxThread;
//    std::this_thread* pxThisThread;
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

//    std::thread* GetThread(void)
//    {
//        return m_pxThread;
//    };

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

//    std::thread* GetThread(void)
//    {
//        return m_pxThread;
//    };

protected:

private:
//    std::thread* m_pxThread;
};

//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CRteThreadProduction : public CProduction
{
public:
    CRteThreadProduction();
    virtual ~CRteThreadProduction();

//    void Create(CRte* pxRte);
    void Place(CRte* pxRte);
//    void Start(void);
//    void Stop(void);

    static void Process(CRte* pxRte);

//    std::thread* GetThread(void)
//    {
//        return m_pxThread;
//    };

protected:

private:
//    std::thread* m_pxThread;
};

//-----------------------------------------------------------------------------------------
#endif // CPRODUCTION_H
