//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CMODBUS_H
#define CMODBUS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "../Platform.h"
#include "../Dfa.h"
#include "../Timer.h"

#define HAVE_DECL_TIOCSRS485 1

///* Max between RTU and TCP max adu length (so TCP) */
//#define MODBUS_RTU_MAX_ADU_LENGTH 260

#define COMMON_DELAY_TIME    100
#define MAX_MODBUS_BUFFER_BUSY_WAITING_TIME 5000 //COMMON_DELAY_TIME * 5000 = 500ms
#define MAX_MAIN_BUFFER_BUSY_WAITING_TIME 10 //COMMON_DELAY_TIME * 20 = 2ms

#define MODBUS_BROADCAST_ADDRESS    0

/* Modbus_Application_Protocol_V1_1b.pdf (chapter 6 section 1 page 12)
 * Quantity of Coils to read (2 bytes): 1 to 2000 (0x7D0)
 * (chapter 6 section 11 page 29)
 * Quantity of Coils to write (2 bytes): 1 to 1968 (0x7B0)
 */
#define MODBUS_MAX_READ_BITS              2000
#define MODBUS_MAX_WRITE_BITS             1968

/* Modbus_Application_Protocol_V1_1b.pdf (chapter 6 section 3 page 15)
 * Quantity of Registers to read (2 bytes): 1 to 125 (0x7D)
 * (chapter 6 section 12 page 31)
 * Quantity of Registers to write (2 bytes) 1 to 123 (0x7B)
 * (chapter 6 section 17 page 38)
 * Quantity of Registers to write in R/W registers (2 bytes) 1 to 121 (0x79)
 */
#define MODBUS_MAX_READ_REGISTERS          125
#define MODBUS_MAX_WRITE_REGISTERS         123
#define MODBUS_MAX_RW_WRITE_REGISTERS      121

#define MODBUS_ADDRESS_LENGTH 1
#define MODBUS_FUNCTION_CODE_LENGTH 1
#define MODBUS_BYTE_QUANTITY_LENGTH 1
#define MODBUS_FUNCTION_REGISTER_ADDRESS_LENGTH 2
#define MODBUS_FUNCTION_REGISTER_QUANTITY_LENGTH 2
#define MODBUS_CRC_LENGTH 2
#define MAX_DATA_EXCHANGE_BYTE      (MODBUS_RTU_MAX_ADU_LENGTH - \
                                     MODBUS_ADDRESS_LENGTH - \
                                      MODBUS_FUNCTION_CODE_LENGTH - \
                                       MODBUS_BYTE_QUANTITY_LENGTH - \
                                       MODBUS_CRC_LENGTH)

/* Random number to avoid errno conflicts */
#define MODBUS_ENOBASE 0//112345678

/* It's not really the minimal length (the real one is report slave ID
 * in RTU (4 bytes)) but it's a convenient size to use in RTU or TCP
 * communications to read many values or write a single one.
 * Maximum between :
 * - HEADER_LENGTH_TCP (7) + function (1) + address (2) + number (2)
 * - HEADER_LENGTH_RTU (1) + function (1) + address (2) + number (2) + CRC (2)
 */
#define _MIN_REQ_LENGTH 12
#define _MIN_MESSAGE_LENGTH 4

#define _REPORT_SLAVE_ID SERVER_ID//180

#define _MODBUS_EXCEPTION_RSP_LENGTH 5

/* Timeouts in microsecond (0.5 s) */
#define _RESPONSE_TIMEOUT    500
#define _BYTE_TIMEOUT        500
/* Timeouts in second (15 s) */
#define _RECEIVE_TIMEOUT    15000//2000//

/* Function codes */
#define _FC_READ_COILS                0x01
#define _FC_READ_DISCRETE_INPUTS      0x02
#define _FC_READ_HOLDING_REGISTERS    0x03
#define _FC_READ_INPUT_REGISTERS      0x04
#define _FC_WRITE_SINGLE_COIL         0x05
#define _FC_WRITE_SINGLE_REGISTER     0x06
#define _FC_READ_EXCEPTION_STATUS     0x07
#define _FC_WRITE_MULTIPLE_COILS      0x0F
#define _FC_WRITE_MULTIPLE_REGISTERS  0x10
#define _FC_REPORT_SLAVE_ID           0x11
#define _FC_WRITE_AND_READ_REGISTERS  0x17

#define _FC_PROGRAMMING_COMPLETION_REQUEST  0x0E
#define _FC_CONFIGURATION_REQUEST  0x11
#define _FC_DATA_BASE_ARCHIVE_BLOCK_READ  0x43
#define _FC_DATA_BASE_READ  0x44
#define _FC_DATA_BASE_WRITE  0x45
#define _FC_TIME_SET  0x46
#define _FC_ONLINE_DATA_READ  0x47

#define _FC_PROGRAMMING 0x46
#define _FC_WRITE_DATA  0x41
#define _FC_READ_DATA  0x42
#define _FC_DATA_EXCHANGE  0x41

#define _MODBUS_TCP_PI_NODE_LENGTH    1025
#define _MODBUS_TCP_PI_SERVICE_LENGTH   32

/*
    ---------- Request     Indication ----------
    | Client | ---------------------->| Server |
    ---------- Confirmation  Response ----------
*/

/* Protocol exceptions */
typedef enum
{
    MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
    MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
    MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
    MODBUS_EXCEPTION_ACKNOWLEDGE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
    MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
    MODBUS_EXCEPTION_MEMORY_PARITY,
    MODBUS_EXCEPTION_NOT_DEFINED,
    MODBUS_EXCEPTION_GATEWAY_PATH,
    MODBUS_EXCEPTION_GATEWAY_TARGET,
    MODBUS_EXCEPTION_MAX
};

typedef enum
{
    MODBUS_ERROR_RECOVERY_NONE          = 0,
    MODBUS_ERROR_RECOVERY_LINK          = (1<<1),
    MODBUS_ERROR_RECOVERY_PROTOCOL      = (1<<2),
} modbus_error_recovery_mode;

#define EMBXILFUN  (MODBUS_ENOBASE + MODBUS_EXCEPTION_ILLEGAL_FUNCTION)
#define EMBXILADD  (MODBUS_ENOBASE + MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS)
#define EMBXILVAL  (MODBUS_ENOBASE + MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE)
#define EMBXSFAIL  (MODBUS_ENOBASE + MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE)
#define EMBXACK    (MODBUS_ENOBASE + MODBUS_EXCEPTION_ACKNOWLEDGE)
#define EMBXSBUSY  (MODBUS_ENOBASE + MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY)
#define EMBXNACK   (MODBUS_ENOBASE + MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE)
#define EMBXMEMPAR (MODBUS_ENOBASE + MODBUS_EXCEPTION_MEMORY_PARITY)
#define EMBXGPATH  (MODBUS_ENOBASE + MODBUS_EXCEPTION_GATEWAY_PATH)
#define EMBXGTAR   (MODBUS_ENOBASE + MODBUS_EXCEPTION_GATEWAY_TARGET)

/* Native libmodbus error codes */
#define EMBBADCRC  (EMBXGTAR + 1)
#define EMBBADDATA (EMBXGTAR + 2)
#define EMBBADEXC  (EMBXGTAR + 3)
#define EMBUNKEXC  (EMBXGTAR + 4)
#define EMBMDATA   (EMBXGTAR + 5)


//-----------------------------------------------------------------------------------------------------
class CModbus : public CDfa
{
public:
    typedef enum
    {
        IDDLE  = 0,
        START,

        REQUEST_ENABLE,
        WAITING_ACCEPT,
        START_REQUEST,
        WAITING_MESSAGE_REQUEST,
        RECEIVE_MESSAGE_REQUEST,
        REQUEST_PROCESSING_REQUEST,
        FRAME_TRANSMIT_CONFIRMATION,
        WAITING_FRAME_TRANSMIT_CONFIRMATION,
        END_WAITING_FRAME_TRANSMIT_CONFIRMATION,
        STOP_REQUEST,
        REQUEST_ERROR,

//-----------------------------------------------------------------------------------------------------
// ModbusMaster
        CONFIRMATION_ENABLE,
        WAITING_CONNECT,
        START_CONFIRMATION,
        WAITING_MESSAGE_CONFIRMATION,
        RECEIVE_MESSAGE_CONFIRMATION,
        ANSWER_PROCESSING_CONFIRMATION,
        FRAME_TRANSMIT_REQUEST,
        WAITING_FRAME_TRANSMIT_REQUEST,
        END_WAITING_FRAME_TRANSMIT_REQUEST,
        STOP_CONFIRMATION,
        CONFIRMATION_ERROR,

        RESTART,
    } FsmState;

    enum
    {
        MODBUS_EXCEPTION_CODE_OFFSET = 1,
    };

    CModbus();
    virtual ~CModbus();

    static const char *ModbusStringError(int errnum);
    void SlaveSet(uint8_t );

    uint16_t ReadCoils(uint8_t * , uint8_t * , uint16_t );
    uint16_t ReadDiscreteInputs(uint8_t * , uint8_t * , uint16_t );
    uint16_t ReadHoldingRegisters(uint8_t * , uint8_t * , uint16_t );
    uint16_t ReadInputRegisters(uint8_t * , uint8_t * , uint16_t );
    uint16_t WriteSingleCoil(uint8_t * , uint8_t * , uint16_t );
    uint16_t WriteSingleRegister(uint8_t * , uint8_t * , uint16_t );
    uint16_t WriteMultipleCoils(uint8_t * , uint8_t * , uint16_t );
    uint16_t WriteMultipleRegisters(uint8_t * , uint8_t * , uint16_t );
    uint16_t ReadExceptionStatus(uint8_t * , uint8_t * , uint16_t );
    uint16_t ReportSlaveID(uint8_t * , uint8_t * , uint16_t );
    uint16_t WriteAndReadRegisters(uint8_t * , uint8_t * , uint16_t );
    uint16_t Programming(uint8_t * , uint8_t * , uint16_t );
    uint16_t PollProgramming(uint8_t * , uint8_t * , uint16_t );
    uint16_t RequestProcessing(uint8_t * , uint8_t * , uint16_t );


protected:
private:

    uint16_t ByteToBitPack(uint16_t ,
                           uint16_t ,
                           uint8_t *,
                           uint8_t *,
                           uint16_t );
    virtual bool IsDataWrited(void) = 0;
    int8_t MessengerIsReady(void);
    virtual uint16_t Tail(uint8_t * , uint16_t ) = 0;
    virtual uint16_t RequestBasis(uint8_t uiSlave,
                                  uint8_t uiFunctionCode,
                                  uint16_t uiAddress,
                                  uint16_t uiBitNumber,
                                  uint8_t *puiRequest) = 0;
    virtual uint16_t ResponseBasis(uint8_t , uint8_t , uint8_t * ) = 0;
    uint16_t ResponseException(uint8_t , uint8_t , uint8_t , uint8_t * );
    uint16_t SendMessage(uint8_t * , uint16_t );
    virtual uint16_t Send(uint8_t * , uint16_t ) = 0;
    void SetByteFromBits(uint8_t * , uint16_t , const uint8_t );
    void SetBytesFromBits(uint8_t * , uint16_t , uint16_t ,
                          const uint8_t * );
    uint8_t GetByteFromBits(const uint8_t * , uint16_t ,
                            uint16_t );
    float GetFloat(const uint16_t * );
    void SetFloat(float , uint16_t * );

public:
//-----------------------------------------------------------------------------------------------------
// ModbusMaster
//    int8_t ReadCoilsRequest(uint16_t uiAddress,
//                            uint16_t uiBitNumber);
//    uint16_t ReadCoilsReply(uint8_t *puiDestination);
//    uint8_t CheckConfirmation(uint8_t *puiDestination, uint16_t uiLength);
    int8_t ReadDiscreteInputsRequest(uint8_t uiSlaveAddress,
                                     uint16_t uiAddress,
                                     uint16_t uiBitNumber);
    uint16_t ReadDiscreteInputsReceive(uint8_t *puiMessage, uint16_t uiLength);


private:
protected:

//    static uint8_t CheckConfirmation(uint8_t *puiResponse, uint16_t uiLength);
    uint16_t AnswerProcessing(uint8_t *puiResponse, uint16_t uiFrameLength);

    virtual uint8_t GetMessageLength(void)
    {
        return m_uiMessageLength;
    };
    virtual void SetMessageLength(uint8_t uiData)
    {
        m_uiMessageLength = uiData;
    };

    virtual uint16_t HEADER_LENGTH(void)
    {
        return 1;
    };
    virtual uint16_t CRC_LENGTH(void)
    {
        return 2;
    };


//-----------------------------------------------------------------------------------------------------
    uint8_t m_uiOwnAddress;
    uint8_t m_uiSlaveAddress;
    uint8_t m_uiFunctionCode;
    uint16_t m_uiQuantity;
    uint16_t m_uiMessageLength;

    uint8_t *m_puiRxBuffer;
    uint8_t *m_puiTxBuffer;

    uint8_t *m_puiCoils;
    uint8_t *m_puiDiscreteInputs;
    uint16_t *m_pui16HoldingRegisters;
    uint16_t *m_pui16InputRegisters;
    uint16_t m_uiCoilsNumber;
    uint16_t m_uiDiscreteInputsNumber;
    uint16_t m_uiHoldingRegistersNumber;
    uint16_t m_uiInputRegistersNumber;

    friend class CModbusRtu;
    friend class CModbusTcp;
};

//-----------------------------------------------------------------------------------------------------
#endif // CMODBUS_H


