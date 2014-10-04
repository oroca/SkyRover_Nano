//----------------------------------------------------------------------------
//    프로그램명 	: LCD 라이브러리 u8glib 드라이 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: drv_u8g.c
//----------------------------------------------------------------------------




//----- 헤더파일 열기
//
#define  DRV_U8G_LOCAL

#include "drv_u8g.h"



//-- 외부 선언
//



//-- 내부 선언
//
#define U8G_I2C_ADDR		(0x78/2)
#define U8G_I2C_CMD_MODE	0x000
#define U8G_I2C_DATA_MODE	0x040

//-- 내부 변수
//
uint8_t	U8G_SSD_A0_SET	 = 0;
uint8_t	U8G_SSD_A0_STATE = 0;



//-- 내부 함수
//


//-- I2C 함
//
#define SCL_H         GPIOA->BSRR = Pin_10 /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */
#define SCL_L         GPIOA->BRR  = Pin_10 /* GPIO_ResetBits(GPIOB , GPIO_Pin_10) */

#define SDA_H         GPIOA->BSRR = Pin_9  /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */
#define SDA_L         GPIOA->BRR  = Pin_9  /* GPIO_ResetBits(GPIOB , GPIO_Pin_11) */

#define SCL_read      (GPIOA->IDR & Pin_10) /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) */
#define SDA_read      (GPIOA->IDR & Pin_9 ) /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */

static void I2C_delay(void)
{
    volatile int i = 7;
    while (i)
        i--;
}

static bool I2C_Start(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    if (!SDA_read)
        return false;
    SDA_L;
    I2C_delay();
    if (SDA_read)
        return false;
    SDA_L;
    I2C_delay();
    return true;
}

static bool I2C_Start_NoAck(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    //if (!SDA_read)
    //    return false;
    SDA_L;
    I2C_delay();
    //if (SDA_read)
    //    return false;
    SDA_L;
    I2C_delay();
    return true;
}

static void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}

static void I2C_Ack(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

static void I2C_NoAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

static bool I2C_WaitAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    if (SDA_read) {
        SCL_L;
        return false;
    }
    SCL_L;
    return true;
}

static void I2C_SendByte(uint8_t byte)
{
    uint8_t i = 8;
    while (i--) {
        SCL_L;
        I2C_delay();
        if (byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}

static uint8_t I2C_ReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t byte = 0;

    SDA_H;
    while (i--) {
        byte <<= 1;
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        if (SDA_read) {
            byte |= 0x01;
        }
    }
    SCL_L;
    return byte;
}

void I2C_SW_Init(I2C_TypeDef * I2C)
{
    gpio_config_t gpio;

    gpio.pin = Pin_9 | Pin_10;
    gpio.speed = Speed_2MHz;
    gpio.mode = Mode_Out_PP;//Mode_Out_OD
    gpioInit(GPIOA, &gpio);
}


bool I2C_WriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
{
    int i;
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    for (i = 0; i < len; i++) {
        I2C_SendByte(data[i]);
        if (!I2C_WaitAck()) {
            I2C_Stop();
            return false;
        }
    }
    I2C_Stop();
    return true;
}


bool I2C_WriteBuffer_NoAck(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data)
{
    int i;
    if (!I2C_Start_NoAck())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);

    I2C_NoAck();

    //I2C_SendByte(reg);
    //I2C_NoAck();
    for (i = 0; i < len; i++) {
        I2C_SendByte(data[i]);
        I2C_NoAck();
    }
    I2C_Stop();
    return true;
}


bool I2C_Write(uint8_t addr, uint8_t reg, uint8_t data)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
    return true;
}


bool I2C_Write_NoAck(uint8_t addr, uint8_t reg, uint8_t data)
{
    if (!I2C_Start_NoAck())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);

    I2C_NoAck();

    //I2C_SendByte(reg);
    //I2C_NoAck();
    I2C_SendByte(data);
    I2C_NoAck();
    I2C_Stop();
    return true;
}

bool I2C_Read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(addr << 1 | I2C_Direction_Receiver);
    I2C_WaitAck();
    while (len) {
        *buf = I2C_ReceiveByte();
        if (len == 1)
            I2C_NoAck();
        else
            I2C_Ack();
        buf++;
        len--;
    }
    I2C_Stop();
    return true;
}






/*========================================================================*/
/*
  The following delay procedures must be implemented for u8glib

  void u8g_Delay(uint16_t val)	Delay by "val" milliseconds
  void u8g_MicroDelay(void)		Delay be one microsecond
  void u8g_10MicroDelay(void)	Delay by 10 microseconds

*/

void u8g_Delay(uint16_t val)
{
	delay(val);
}

void u8g_MicroDelay(void)
{
	delayMicroseconds(1);
}

void u8g_10MicroDelay(void)
{
	delayMicroseconds(10);
}



uint8_t u8g_com_ssd_start_sequence(u8g_t *u8g)
{
	/* are we requested to set the a0 state? */
	if ( U8G_SSD_A0_SET == 0 )
		return 1;


	/* setup bus, might be a repeated start */
	I2C_Start_NoAck();
	I2C_SendByte( U8G_I2C_ADDR<< 1 | I2C_Direction_Transmitter);
	I2C_NoAck();



	if ( U8G_SSD_A0_STATE == 0 )
	{
		I2C_SendByte(U8G_I2C_CMD_MODE);
	    I2C_NoAck();
	}
	else
	{
		I2C_SendByte(U8G_I2C_DATA_MODE);
	    I2C_NoAck();
	}


	U8G_SSD_A0_SET = 0;
	return 1;
}



/*---------------------------------------------------------------------------
     TITLE   : u8g_com_sw_i2c_fn
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
uint8_t u8g_com_sw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{

	switch(msg)
	{
		case U8G_COM_MSG_STOP:
			break;

		case U8G_COM_MSG_INIT:

			//-- I2C 초기화
			//
			I2C_SW_Init(NULL);
			I2C_Stop();
			break;

		case U8G_COM_MSG_CHIP_SELECT:
			U8G_SSD_A0_STATE = 0;
			U8G_SSD_A0_SET	 = 1;
			if( arg_val == 0 )
			{
				I2C_Stop();
			}
			break;

		case U8G_COM_MSG_RESET:
			break;

		case U8G_COM_MSG_WRITE_BYTE:
			if ( u8g_com_ssd_start_sequence(u8g) == 0 )
			{
				I2C_Stop();
				return 0;
			}

		    I2C_SendByte(arg_val);
		    I2C_NoAck();

			break;

		case U8G_COM_MSG_WRITE_SEQ:
			if ( u8g_com_ssd_start_sequence(u8g) == 0 )
			{
				I2C_Stop();
				return 0;
			}

			{
		        register uint8_t *ptr = arg_ptr;
		        while( arg_val > 0 )
		        {
	    			I2C_SendByte(*ptr++);
	    			I2C_NoAck();
					arg_val--;
		        }
		      }
			break;

		case U8G_COM_MSG_WRITE_SEQ_P:
			if ( u8g_com_ssd_start_sequence(u8g) == 0 )
			{
				I2C_Stop();
				return 0;
			}
			{
		        register uint8_t *ptr = arg_ptr;
		        while( arg_val > 0 )
		        {
	    			I2C_SendByte(*ptr);
	    			I2C_NoAck();
		        	ptr++;
		        	arg_val--;
		        }
			}
			break;

	    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
			U8G_SSD_A0_STATE = arg_val;
			U8G_SSD_A0_SET	 = 1;
			break;
	}
	return 1;
}

