#include "CH554_SDCC.h"
#include "compiler.h"
#include "system.h"
#include <stdio.h>

#define UART0_BUAD 38400

/** \brief 配置系统时钟
 *
 * \param void
 * \return void
 *
 */
void CfgSysClock()
{
    SAFE_MOD = 0x55; //Enter unsafe mode
    SAFE_MOD = 0xAA;
    CLOCK_CFG = CLOCK_CFG & ~MASK_SYS_CK_SEL | 0x04; // 12MHz
    SAFE_MOD = 0x00;
}

/** \brief 初始化UART
 *  此函数并未使用
 */
/*
void InitUART()
{
    uint32_t x;
    // uint32_t x2;

    SM0 = 0; // 8Bit
    SM1 = 1; // Variable
    SM2 = 0; // Single device

    RCLK = 0; // using timer1 as send/recv clock
    TCLK = 0; //

    PCON |= SMOD; //SMOD = 0; uart slow mode

    x = FREQ_SYS / UART0_BUAD / 16;

    TMOD = TMOD & ~bT1_GATE & ~bT1_CT & ~MASK_T1_MOD | bT1_M1; //0X20，Timer1作为8位自动重载定时器
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;                        //Timer1时钟选择
    TH1 = 0 - x;                                               //12MHz晶振,buad/12为实际需设置波特率
    TR1 = 1;                                                   //启动定时器1
    TI = 1;
    REN = 1; //串口0接收使能
}
*/


/*******************************************************************************
* Function Name  : Delayus(uint16_t n)
* Description    : us延时函数
* Input          : uint16_t n
* Output         : None
* Return         : None
*******************************************************************************/
void DelayUs(uint16_t n)  // 以uS为单位延时
{
	while (n) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
		-- n;
	}
}

/*******************************************************************************
* Function Name  : Delayms(uint16_t n)
* Description    : ms延时函数
* Input          : uint16_t n
* Output         : None
* Return         : None
*******************************************************************************/
void DelayMs(uint16_t n)                                                  // 以mS为单位延时
{
	while ( n ) {
		DelayUs(1000);
        -- n;
	}
}


void PrintHex(uint8_t *data, uint8_t len)
{
    for (int i = 0; i < len; i++)
    {
        printf_tiny("%x ", data[i]);
    }
}

int putchar(int c)
{
    while (TI == 0)
        ;
    TI = 0;
    SBUF = c;
    return c;
}

int getchar()
{
    while (RI == 0)
        ;
    RI = 0;
    return SBUF;
}
