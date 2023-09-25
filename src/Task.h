#ifndef CTASK_H
#define CTASK_H
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include <stdint.h>

//-----------------------------------------------------------------------------------------
class CTaskInterface
{
public:
    virtual void SetFsmState(uint8_t uiData) {};
    virtual uint8_t GetFsmState(void) {};
    virtual void Fsm(void) {};
};

//-----------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------
class CTask : public CTaskInterface
{
public:
    CTask();
    virtual ~CTask();

    void SetFsmState(uint8_t uiData)
    {
        m_uiFsmState = uiData;
    };
    uint8_t GetFsmState(void)
    {
        return m_uiFsmState;
    };


private:
    uint8_t m_uiFsmState;

};

//-----------------------------------------------------------------------------------------






////-----------------------------------------------------------------------------------------
//class CMainProductionTask : public CTask
//{
//public:
//    enum
//    {
//
//    };
//
//    CMainProductionTask();
//    virtual ~CMainProductionTask();
//
//private:
//
//};
////-----------------------------------------------------------------------------------------

#endif // CTASK_H
