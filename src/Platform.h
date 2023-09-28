//-----------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------
#ifndef PLATFORM_H
#define PLATFORM_H

//-----------------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <termios.h>
#include <linux/serial.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/spi/spidev.h>
#include <time.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */

#if defined(__OpenBSD__) || (defined(__FreeBSD__) && __FreeBSD__ < 5)
# define OS_BSD
# include <netinet/in_systm.h>
#endif

# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <poll.h>
# include <netdb.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>


#include <unistd.h>

/* Include definition for RS485 ioctls: TIOCGRS485 and TIOCSRS485 */
#include <sys/ioctl.h>

#include "Configuration.h"
#include "Timer.h"

//-----------------------------------------------------------------------------------------
class CCommunicationDeviceInterface
{
public:
    virtual void Init(void) {};

    virtual void SetSocketLowAddress(struct sockaddr_ll* pxSocketLowAddress) {};
    virtual struct sockaddr_ll* GetSocketLowAddress(void) {};

    virtual void SetPortName(const char* pccDeviceName) {};
    virtual const char* GetPortName(void) {};
    virtual void SetBaudRate(uint32_t uiBaudRate) {};
    virtual void SetDataBits(uint8_t uiDataBits) {};
    virtual void SetParity(char cParity) {};
    virtual void SetStopBit(uint8_t uiStopBit) {};

    virtual void SetIpAddress(const char* pccIpAddress) {};
    virtual const char* GetIpAddress(void) {};
    virtual void SetPort(uint16_t uiPort) {};
    virtual void SetDestinationMacAddress(uint8_t* puiMacAddress) {};
    virtual uint8_t* GetDestnationMacAddress(void) {};
    virtual void SetSourseMacAddress(uint8_t* puiMacAddress) {};
    virtual uint8_t* GetSourseMacAddress(void) {};

    virtual int8_t Open(void) {};
    virtual int8_t Close(void) {};
    virtual int16_t Write(uint8_t* puiDestination, uint16_t uiLength) {};
    virtual int16_t Read(uint8_t* puiSource, uint16_t uiLength) {};
    virtual int Exchange(uint8_t uiAddress,
                         unsigned char* pucTxBuff,
                         unsigned char* pucRxBuff,
                         int iLength,
                         int iSpeed) {};
    virtual bool IsDataWrited(void) {};
};
//-----------------------------------------------------------------------------------------














//-----------------------------------------------------------------------------------------
class CCommunicationDevice : public CCommunicationDeviceInterface
{
public:
    CCommunicationDevice();
    virtual ~CCommunicationDevice();

    void SetDataIsWrited(bool bData)
    {
        m_bDataIsWrited = bData;
    }
    bool GetDataIsWrited(void)
    {
        return m_bDataIsWrited;
    }

    virtual bool IsDataWrited(void)
    {
        if (m_bDataIsWrited)
        {
            m_bDataIsWrited = false;
            return true;
        }
        else
        {
            return false;
        }
    };

//-----------------------------------------------------------------------------------------
private:
    // Флаг - данные записаны.
    bool m_bDataIsWrited;
};
//-----------------------------------------------------------------------------------------














//-----------------------------------------------------------------------------------------
class CSerialPort : public CCommunicationDevice
{
public:
    enum
    {
        UART_MAX_BUFF_LENGTH = 256,
        UART_INTERMEDIATE_BUFF_LENGTH = 16
    };

    CSerialPort();
    virtual ~CSerialPort();

//-----------------------------------------------------------------------------------------
    void Init(void);
    void SetPortName(const char* pccDeviceName);
    const char* GetPortName(void);
    void SetBaudRate(uint32_t uiBaudRate);
    void SetDataBits(uint8_t uiDataBits);
    void SetParity(char cParity);
    void SetStopBit(uint8_t uiStopBit);
    int8_t Open(void);
    int8_t Close(void);
//    void Reset(void);
//    bool IsDataAvailable(void);
    int16_t Write(uint8_t* puiDestination, uint16_t uiLength);
    int16_t Read(uint8_t* puiSource, uint16_t uiLength);
    int Exchange(uint8_t uiAddress,
                 unsigned char *pucTxBuff,
                 unsigned char *pucRxBuff,
                 int iLength,
                 int iSpeed);

//-----------------------------------------------------------------------------------------
private:
protected:
    const char *m_pccDeviceName;
    /* Socket or file descriptor */
    int32_t m_iDeviceDescriptor;
    struct termios m_xTios;
    struct serial_rs485 m_xRs485Conf;
//    struct timeval *pto;
//    fd_set readfds, writefds;
//    uint32_t m_uiBaudRate;
//    /* Parity: 'N', 'O', 'E' */
//    char m_uiParity;
////    uint8_t m_uiParity;
//    uint8_t m_uiDataBits;
//    uint8_t m_uiStopBit;
//    // Флаг - данные записаны.
//    bool m_bDataIsWrited = false;
//    uint8_t* m_puiTxBuffer;
//    uint16_t m_nuiTxBuffByteCounter;
//    uint8_t* m_puiRxBuffer;
//    uint16_t m_nuiRxBuffByteCounter;
////    uint8_t m_auiIntermediateBuff[UART_INTERMEDIATE_BUFF_LENGTH];
};
//-----------------------------------------------------------------------------------------














//-----------------------------------------------------------------------------------------
class CTcpCommunicationDevice : public CCommunicationDevice
{
public:
    enum
    {
        UART_MAX_BUFF_LENGTH = 256,
        UART_INTERMEDIATE_BUFF_LENGTH = 16
    };

    CTcpCommunicationDevice();
    virtual ~CTcpCommunicationDevice();

//-----------------------------------------------------------------------------------------
    void Init(void);
    void SetIpAddress(const char* pccIpAddress);
    const char* GetIpAddress(void);
    void SetPort(uint16_t uiPort);
    int8_t Listen(void);
    int8_t Accept(void);
    int8_t Connect(void);
    int8_t Open(void);
    int8_t Close(void);
//    void Reset(void);
//    bool IsDataAvailable(void);
    int16_t Write(uint8_t* puiDestination, uint16_t uiLength);
    int16_t Read(uint8_t* puiSource, uint16_t uiLength);
    int Exchange(uint8_t uiAddress,
                 unsigned char *pucTxBuff,
                 unsigned char *pucRxBuff,
                 int iLength,
                 int iSpeed);

//-----------------------------------------------------------------------------------------
private:
protected:
    const char *m_pccIpAddress;
    uint32_t m_uiIpAddress;
    uint16_t m_uiPort;
    /* Socket or file descriptor */
    int32_t m_iDeviceDescriptor;
    int32_t m_iDeviceDescriptorAccept;
    struct sockaddr_in m_Address;
//    struct termios m_xTios;
//    struct serial_rs485 m_xRs485Conf;
//    struct timeval *pto;
//    fd_set readfds, writefds;
//    uint32_t m_uiBaudRate;
//    /* Parity: 'N', 'O', 'E' */
//    char m_uiParity;
////    uint8_t m_uiParity;
//    uint8_t m_uiDataBits;
//    uint8_t m_uiStopBit;
//    // Флаг - данные записаны.
//    bool m_bDataIsWrited = false;
//    uint8_t* m_puiTxBuffer;
//    uint16_t m_nuiTxBuffByteCounter;
//    uint8_t* m_puiRxBuffer;
//    uint16_t m_nuiRxBuffByteCounter;
};
//-----------------------------------------------------------------------------------------














//-----------------------------------------------------------------------------------------
class CEthernetCommunicationDevice : public CCommunicationDevice
{
public:
    enum
    {
        ETHERNET_TYPE = 0x0800,
        MAX_BUFF_LENGTH = 1024,
        INTERMEDIATE_BUFF_LENGTH = 16,
        MAC_ADDRESS_LENGTH = 6,
    };

    CEthernetCommunicationDevice();
    virtual ~CEthernetCommunicationDevice();

    void SetSocketLowAddress(struct sockaddr_ll* pxSocketLowAddress)
    {
        m_pxSocketLowAddress = pxSocketLowAddress;
    };
    struct sockaddr_ll* GetSocketLowAddress(void)
    {
        return m_pxSocketLowAddress;
    };

//-----------------------------------------------------------------------------------------
    void Init(void);

    void SetPortName(const char* pccDeviceName);
    const char* GetPortName(void);
    void SetIpAddress(const char* pccIpAddress);
    const char* GetIpAddress(void);
    void SetDestinationMacAddress(uint8_t* puiMacAddress);
    uint8_t* GetDestnationMacAddress(void);
    void SetSourseMacAddress(uint8_t* puiMacAddress);
    uint8_t* GetSourseMacAddress(void);
    void SetPort(uint16_t uiPort);
    int8_t Listen(void);
    int8_t Accept(void);
    int8_t Connect(void);
    int8_t Open(void);
    int8_t Close(void);
//    void Reset(void);
//    bool IsDataAvailable(void);
    int16_t Write(uint8_t* puiDestination, uint16_t uiLength);
    int16_t Read(uint8_t* puiSource, uint16_t uiLength);
    int Exchange(uint8_t uiAddress,
                 unsigned char *pucTxBuff,
                 unsigned char *pucRxBuff,
                 int iLength,
                 int iSpeed);

//-----------------------------------------------------------------------------------------
//private:
//protected:
    const char *m_pccDeviceName;
    const char *m_pccIpAddress;
    uint32_t m_uiIpAddress;
    uint16_t m_uiPort;
    uint8_t m_auiDestinationMacAddress[6] = {0};
    uint8_t m_auiSourseMacAddress[6] = {0};
    /* Socket or file descriptor */
    int32_t m_iDeviceDescriptor;
    int32_t m_iDeviceDescriptorAccept;
    struct sockaddr_in m_Address;
    struct sockaddr_ll* m_pxSocketLowAddress;
};
//-----------------------------------------------------------------------------------------









//-----------------------------------------------------------------------------------------
#define SPI_PATH "/dev/spidev0.0"
#define TX_RX_BUFF_SIZE 256
#define SPI_MODE SPI_MODE_0
#define SPI_MODE32 SPI_3WIRE
#define BITS_PER_WORD 8
#define SPEED_IN_HZ 150000UL
#define LOW_SPEED_IN_HZ SPEED_IN_HZ

#define SPI_CHIP_SELECT_PIN_0  7 /* (R2) lcd_data1.gpio2[7] A0*/
#define SPI_CHIP_SELECT_PIN_0_PORT  GPIO_PORT_2
#define SPI_CHIP_SELECT_PIN_1  11  /* (T2) lcd_data5.gpio2[11] A1*/
#define SPI_CHIP_SELECT_PIN_1_PORT  GPIO_PORT_2
#define SPI_CHIP_SELECT_PIN_2  8  /* (R3) lcd_data2.gpio2[8] A2*/
#define SPI_CHIP_SELECT_PIN_2_PORT  GPIO_PORT_2
#define SPI_CHIP_SELECT_PIN_3  6  /* (R1) lcd_data0.gpio2[6] A3*/
#define SPI_CHIP_SELECT_PIN_3_PORT  GPIO_PORT_2
#define SPI_CHIP_ENABLE_PIN  12 /* (T3) lcd_data6.gpio2[12] ENABLE*/
#define SPI_CHIP_ENABLE_PIN_PORT  GPIO_PORT_2
#define SPI_CHIP_MIND_ENABLE_PIN  16 /* (U3) lcd_data10.gpio2[16] SS0*/
#define SPI_CHIP_MIND_ENABLE_PIN_PORT  GPIO_PORT_2

//-----------------------------------------------------------------------------------------
class CSpi : public CCommunicationDevice
{
public:
    CSpi();
    virtual ~CSpi();

    void Init(void);
    int8_t Open(void);
    int8_t Close(void);
    int Exchange(uint8_t uiAddress,
                 unsigned char *pucTxBuff,
                 unsigned char *pucRxBuff,
                 int iLength,
                 int iSpeed);
    void ChipSelectPinSet(void);
    void ChipSelectPinDelete(void);
    void ChipSelectAddressSet(unsigned char ucAddress);

    static const uint8_t BUFFER_LENGTH = 64;
private:
    const char *m_pccDeviceName;
    /* Socket or file descriptor */
    int32_t m_iDeviceDescriptor;
    static const uint8_t aui8ModuleSlotNumberToSpiAddressMatching[SPI_MAX_BUS_ADDRESS];

};
//-----------------------------------------------------------------------------------------









//-----------------------------------------------------------------------------------------
#define CM_PER 0x44E00000
#define CM_PER_L4LS_CLKSTCTRL_OFFSET 0x00
#define CLKACTIVITY_GPIO_3_GDBCLK 21
#define CLKACTIVITY_GPIO_2_GDBCLK 20
#define CLKACTIVITY_GPIO_1_GDBCLK 19

#define CM_PER_GPIO1_CLKCTRL_OFFSET 0xAC
#define CM_PER_GPIO2_CLKCTRL_OFFSET 0xB0
#define CM_PER_GPIO3_CLKCTRL_OFFSET 0xB4
#define MODULEMODE_BIT_0 0
#define MODULEMODE_BIT_1 1
#define OPTFCLKEN_GPIO_X_GDBCLK 18

#define GPIO0_ADDR 0x44E07000
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AE000
#define GPIO_OE_OFFSET 0x134
#define GPIO_DATAIN_OFFSET 0x138
#define GPIO_DATAOUT_OFFSET 0x13C

#define GPIO_PORT_0 0
#define GPIO_PORT_1 1
#define GPIO_PORT_2 2
#define GPIO_PORT_3 3
#define GPIO_PORT_QUANTITY 4

#define SYSFS_GPIO_DIR "/sys/class/gpio"
//#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

enum PIN_DIRECTION
{
    INPUT_PIN=0,
    OUTPUT_PIN=1
};

enum PIN_VALUE
{
    LOW=0,
    HIGH=1
};

struct TGpioControl
{
    unsigned long *pulCmPerMap;
    unsigned long *apulGpioMmapPointers[GPIO_PORT_QUANTITY];
    unsigned long aulGpioMmapAddresses[GPIO_PORT_QUANTITY];
};

//-----------------------------------------------------------------------------------------
class CGpio
{
public:
//    CGpio();
//    virtual ~CGpio();

    static void Init(void);
    static int8_t Open(void);
    static int8_t Close(void);
    static void SetPinOutput(unsigned char ucPortN, unsigned char ucPinN);
    static void SetPinInput(unsigned char ucPortN, unsigned char ucPinN);
    static void SetPin(unsigned char ucPortN, unsigned char ucPinN);
    static void ClearPin(unsigned char ucPortN, unsigned char ucPinN);

private:
//    const char *m_pccDeviceName;
    /* Socket or file descriptor */
    static int32_t m_iDeviceDescriptor;
    static TGpioControl m_xGpioControl;

};
//-----------------------------------------------------------------------------------------













//-----------------------------------------------------------------------------------------
class CPlatform
{
public:
    CPlatform();
    virtual ~CPlatform();
    static void Init(void);
    static uint16_t GetCurrentTime(void);

private:

protected:
};

//-----------------------------------------------------------------------------------------
#endif // PLATFORM_H
