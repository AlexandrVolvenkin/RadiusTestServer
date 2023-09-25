//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------

#include "Goose.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------
CGoose::CGoose()
{
    std::cout << "CGoose constructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
CGoose::~CGoose()
{
    std::cout << "CGoose desstructor"  << std::endl;

}

//-----------------------------------------------------------------------------------------
void CGoose::SlaveSet(uint8_t uiSlave)
{
    m_uiOwnAddress = uiSlave;
}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::RequestProcessing(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiFrameLength)
{

}

//-----------------------------------------------------------------------------------------
uint16_t CGoose::AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength)
{

}
