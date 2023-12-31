//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Rte.h"
#include "Platform.h"

// Namespaces:
using namespace std;

//-----------------------------------------------------------------------------------------
CRte::CRte()
{
    m_pxCommunicationDevice = new CSerialPort();
    SetFsmState(IDDLE);
    m_uiCurrentSymbolIndex = 0;
}

//-----------------------------------------------------------------------------------------
CRte::~CRte()
{
    //dtor
}

//-----------------------------------------------------------------------------------------
void CRte::Fsm(void)
{
    switch (GetFsmState())
    {
    case IDDLE:
        break;

    case START:
        // откроем порт
        GetCommunicationDevice() -> Open();
        SetFsmState(FULL_LOAD_MODE_START);
        break;

    case FULL_LOAD_MODE_START:
//        std::cout << "CRte::Fsm FULL_LOAD_MODE_START"  << std::endl;
        // отправим маркер в порт
        GetCommunicationDevice() ->
        Write((uint8_t*)&m_pccMarkerData[m_uiCurrentSymbolIndex], 1);
        if (m_uiCurrentSymbolIndex < MARKER_SYMBOL_NUMBER)
        {
            m_uiCurrentSymbolIndex += 1;
        }
        else
        {
            m_uiCurrentSymbolIndex = 0;
        }

        //        // получим время начала замера
//        m_xTimeMeasure.Begin();
        if (m_xTimeMeasure.Begin())
        {
            SetFsmState(FULL_LOAD_MODE);
        }
        else
        {
            m_xTimeMeasure.Begin();
        }
        break;

    case FULL_LOAD_MODE:
//        std::cout << "CRte::Fsm FULL_LOAD_MODE"  << std::endl;
//        usleep(10000);
        // получим время прошедшее с начала замера
        uint32_t uiTime;
        uiTime = m_xTimeMeasure.End();

//        std::cout << "CRte::Fsm FULL_LOAD_MODE uiTime "  << (uint32_t)uiTime << std::endl;
        // время работы закончилось?
        if (uiTime >
                ((GetPeriodTime() * GetLoadPercent()) / 100))
        {
            SetFsmState(STANDBY_MODE_START);
        }
        else
        {
            std::srand(std::time(nullptr)); // use current time as seed for random generator
            int random_variable = std::rand();
//            std::cout << "Random value on [0, " << RAND_MAX << "]: "
//                      << random_variable << '\n';

            // roll 6-sided dice 20 times
            for (int n = 0; n < 1000; n++)
            {
                int x = 7;
                while (x < 4)
                {
                    x = 1 + std::rand() / ((RAND_MAX + 1u) / 6); // Note: 1 + rand() % 6 is biased
                }
//                std::cout << x << ' ';
            }
        }
        break;

    case STANDBY_MODE_START:
//        std::cout << "CRte::Fsm STANDBY_MODE_START"  << std::endl;
//        // получим время начала замера
//        m_xTimeMeasure.Begin();

        SetFsmState(STANDBY_MODE);
        break;

    case STANDBY_MODE:
        // установим перерыв
        usleep(((GetPeriodTime() * (100 - GetLoadPercent())) / 100));
        // вернёмся к работе
        SetFsmState(FULL_LOAD_MODE_START);
        break;

    case STOP:
        // закроем порт
        GetCommunicationDevice() -> Close();
        SetFsmState(IDDLE);
        break;

    default:
        break;
    }
}
