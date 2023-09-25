
//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------
#ifndef CMAINPRODUCTIONCYCLE_H
#define CMAINPRODUCTIONCYCLE_H

#include <iostream>
#include <string.h>

#include "Platform.h"
#include "Task.h"

//-----------------------------------------------------------------------------------------
class CMainProductionCycleInterface : public CTask
{
public:

};
//-----------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------
class CMainProductionCycle : public CMainProductionCycleInterface
{
public:
    enum
    {
        IDDLE = 0,
    };

    CMainProductionCycle();
    virtual ~CMainProductionCycle();
    void Fsm(void);

protected:
private:
};

//-----------------------------------------------------------------------------------------
#endif // CMAINPRODUCTIONCYCLE_H
