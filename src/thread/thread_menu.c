//----------------------------------------------------------------------------
//    프로그램명 	: thread_menu 관련 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: thread_menu.h
//----------------------------------------------------------------------------



//----- 헤더파일 열기
//
#define  THREAD_MENU_LOCAL

#include "thread_menu.h"
#include "mw.h"

#include "usb_lib.h"
#include "usb_pwr.h"



//-- 외부
//
extern core_t core;


//-- 내부 선언
//
/*
#define _menu_received		Hw_VCom_IsReceived
#define _menu_getch			Hw_VCom_Getch
#define _menu_putch			Hw_VCom_Putch
#define _menu_printf		Hw_VCom_Printf
*/

//#define _menu_received		Hw_VCom_IsReceived
//#define _menu_getch			Hw_VCom_Getch
//#define _menu_putch			Hw_VCom_Putch
//#define _menu_printf		tfp_printf


uint8_t _menu_received(void)
{
	return serialTotalBytesWaiting(core.menuport);
}

uint8_t _menu_getch(void)
{
	return serialRead(core.menuport);
}

void _menu_putch(uint8_t c)
{
	while(!isSerialTransmitBufferEmpty(core.menuport));
	serialWrite(core.menuport, c);
}

static void _menu_putc(void *p, char c)
{
	while(!isSerialTransmitBufferEmpty(core.menuport));
	serialWrite(core.menuport, c);
}

void _menu_printf( char *format, ... )
{
    va_list va;
    va_start(va, format);
    tfp_format(NULL, _menu_putc, format, va);
    va_end(va);
}


//-- 내부 변수
//



//-- 내부 함수
//
void cmd_bluetooth_setup( void );
void cmd_bluetooth_check( void );


/*---------------------------------------------------------------------------
     TITLE   : _menu_show_menu
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
static void _menu_show_menu(void)
{
	u8 key;

	_menu_printf("\n\r\n\r");
	_menu_printf("*******************************************************\n\r");
	_menu_printf("                 SkyRover Nano V0.1                    \n\r");
	_menu_printf("*******************************************************\n\r");
	_menu_printf("* 1. Sensor Status                                    *\n\r");
	_menu_printf("* 2. Bluetooth Setup                                  *\n\r");
	_menu_printf("* 3. Bluetooth Check                                  *\n\r");
	_menu_printf("* 4.                                                  *\n\r");
	_menu_printf("* 5.                                                  *\n\r");
	_menu_printf("* 6.                                                  *\n\r");
	_menu_printf("* 7.                                                  *\n\r");
	_menu_printf("* 8.                                                  *\n\r");
	_menu_printf("* 9.                                                  *\n\r");
	_menu_printf("* m.  Menu                                            *\n\r");
	_menu_printf("*******************************************************\n\r");
	_menu_printf("\n\r");
}





/*---------------------------------------------------------------------------
     TITLE   : _menu_get_cmd
     WORK    :
     ARG     : void
     RET     :
---------------------------------------------------------------------------*/
static uint8_t _menu_get_cmd( uint8_t *pKey )
{
	uint8_t  ret = FALSE;


	if( _menu_received() > 0 )
	{
		ret = TRUE;
		*pKey = _menu_getch();
	}


    return ret;
}





/*---------------------------------------------------------------------------
     TITLE   : _menu_show_cmd
     WORK    :
     ARG     : void
     RET     :
---------------------------------------------------------------------------*/
static void _menu_show_cmd( void )
{
	_menu_printf(">> ");
}





/*---------------------------------------------------------------------------
     TITLE   : thread_menu
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void thread_menu(void const *argument)
{
    (void) argument;
    uint8_t cmd;

    DEBUG_PRINT("Thread Menu\r\n");


    _menu_show_menu();
    _menu_show_cmd();


    for (;;)
    {
    	//if( bDeviceState == CONFIGURED && _menu_get_cmd( &cmd ) == TRUE )
    	if( _menu_get_cmd( &cmd ) == TRUE )
        {

    		switch( cmd )
    		{
				case '1':
					_menu_printf( "Angle : %d\t %d\t %d\t"  , angle[0], angle[1], heading );
					_menu_printf( "rc :\t %d\t %d\t %d\t %d\t \r\n", rcCommand[0], rcCommand[1], rcCommand[2], rcCommand[3] );
					break;

				case '2':
					cmd_bluetooth_setup();
					break;

				case '3':
					cmd_bluetooth_check();
					break;

				case 'm':
				case 'M':
					_menu_show_menu();
					_menu_show_cmd();
					break;

				default:
					break;

    		}

        }
        osDelay(1);
    }
}





/*---------------------------------------------------------------------------
     TITLE   : cmd_bluetooth_setup
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void cmd_bluetooth_setup( void )
{
	uint32_t time_out;
	uint8_t  ch;


	_menu_printf("Uart2 Open 9600BPS \r\n");

	core.blueport = uartOpen(USART2, NULL, 9600, MODE_RXTX);


	_menu_printf("\r\nSned AT\r\n");
	serialPrint(core.blueport, "AT");


	//-- 응답이 올때까지 기다림
	time_out = 100;
	while(time_out--)
	{
		if( serialTotalBytesWaiting(core.blueport) )
		{
			ch = serialRead(core.blueport);
			_menu_putch(ch);
		}
		osDelay(1);
	}


	_menu_printf("\r\nSned AT+BAUD4\r\n");
	serialPrint(core.blueport, "AT+BAUD4");


	//-- 응답이 올때까지 기다림
	time_out = 500;
	while(time_out--)
	{
		if( serialTotalBytesWaiting(core.blueport) )
		{
			ch = serialRead(core.blueport);
			_menu_putch(ch);
		}
		osDelay(1);
	}

	_menu_printf("\r\nSned AT+RESET\r\n");
	serialPrint(core.blueport, "AT+RESET");


	//-- 응답이 올때까지 기다림
	time_out = 500;
	while(time_out--)
	{
		if( serialTotalBytesWaiting(core.blueport) )
		{
			ch = serialRead(core.blueport);
			_menu_putch(ch);
		}
		osDelay(1);
	}


	serialInit(mcfg.serial_baudrate);

}





/*---------------------------------------------------------------------------
     TITLE   : cmd_bluetooth_check
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void cmd_bluetooth_check( void )
{
	uint32_t time_out;
	uint8_t  ch;
	uint8_t  ch_array[2];
	uint8_t  ch_i;


	core.blueport = uartOpen(USART2, NULL, 115200, MODE_RXTX);


	_menu_printf("\r\rnSned AT\r\n");

	serialPrint(core.blueport, "AT");


	ch_array[0] = 0;
	ch_array[1] = 0;
	ch_i  = 0;

	//-- 응답이 올때까지 기다림
	time_out = 1000;
	while(time_out--)
	{
		if( serialTotalBytesWaiting(core.blueport) )
		{
			ch = serialRead(core.blueport);
			_menu_putch(ch);
			ch_array[ch_i++] = ch;

			if( ch_i >= 2 ) break;
		}

		osDelay(1);
	}

	if( ch_array[0] == 'O' && ch_array[1] == 'K' )
	{
		_menu_printf("\r\rnReceived OK\r\n");
	}
	else
	{
		_menu_printf("\r\rnReceived Fail\r\n");
	}

	serialInit(mcfg.serial_baudrate);

}
