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
#include "thread_lcd.h"
#include "mw.h"

#include "usb_lib.h"
#include "usb_pwr.h"

#include "drv_u8g.h"


//-- 외부
//
extern core_t  core;
extern uint8_t vbat;

//-- 내부 선언
//


#if _DEF_MENU_PORT == PORT_USB

#define _menu_received		Hw_VCom_IsReceived
#define _menu_getch			Hw_VCom_Getch
#define _menu_putch			Hw_VCom_Putch
#define _menu_printf		Hw_VCom_Printf

#else

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

#endif



//-- 내부 변수
//



//-- 내부 함수
//
void cmd_go_bootloader( void );
void cmd_bluetooth_setup( void );
void cmd_bluetooth_check( void );
void cmd_bluetooth_change_name( void );




static void _menu_show_vbat(void)
{
	_menu_printf(" Vbat: %d.%dV",vbat/10, vbat%10);
}


static void _menu_show_uart1_type(void)
{
	//-- Uart1 포트 설정값 표시
	//
	if      ( mcfg.uart1_type == _UART1_TYPE_NONE )	_menu_printf("None     \n\r");
	else if ( mcfg.uart1_type == _UART1_TYPE_MW   )	_menu_printf("MultiWii \n\r");
	else if ( mcfg.uart1_type == _UART1_TYPE_LCD  )	_menu_printf("LCD      \n\r");
	else
	{
		_menu_printf("None     \n\r");
	}
}



/*---------------------------------------------------------------------------
     TITLE   : _menu_show_menu
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
static void _menu_show_menu(void)
{

	_menu_printf("\n\r\n\r");
	_menu_printf("*******************************************************\n\r");
	_menu_printf("         SkyRover Nano ");
	_menu_printf(_SKYROVER_VER_STR_); _menu_show_vbat();
	_menu_printf("\r\n");
	_menu_printf("*******************************************************\n\r");
	_menu_printf("  1. Sensor Status                                     \n\r");
	_menu_printf("  2. Bluetooth Setup                                   \n\r");
	_menu_printf("  3. Bluetooth Check                                   \n\r");
	_menu_printf("  4. Uart1 : "); _menu_show_uart1_type();
	_menu_printf("  5. Reset Setup                                       \n\r");
	_menu_printf("  6. Change Bluetooth Name                             \n\r");
	_menu_printf("  7. Use USB for Multiwii                              \n\r");
	_menu_printf("  8. Monitor Msp                                       \n\r");
	_menu_printf("  9.                                                   \n\r");
	_menu_printf("  m.  Menu                                             \n\r");
	_menu_printf("  z.  Go to bootloader                                 \n\r");
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
    uint8_t show_menu_flag;


    DEBUG_PRINT("Thread Menu\r\n");


    _menu_show_menu();
    _menu_show_cmd();


    for (;;)
    {
    	//if( bDeviceState == CONFIGURED && _menu_get_cmd( &cmd ) == TRUE )
    	if( _menu_get_cmd( &cmd ) == TRUE )
        {
    		show_menu_flag = false;

    		switch( cmd )
    		{
				case '1':
					while( !_menu_received() )
					{
						_menu_printf( "Angle : %d\t %d\t %d\t %d "  , angle[0], angle[1], heading, EstAlt );
						_menu_printf( "rc :\t %d\t %d\t %d\t %d\t \r\n", rcCommand[0], rcCommand[1], rcCommand[2], rcCommand[3] );
						osDelay(100);
					}
					break;

				case '2':
					cmd_bluetooth_setup();
					break;

				case '3':
					cmd_bluetooth_check();
					break;

				case '4':
					mcfg.uart1_type++;

					if( mcfg.uart1_type > _UART1_TYPE_END ) mcfg.uart1_type = 0;
					writeEEPROM(1, true);

					_menu_printf( "the board should be rebooted\r\n" );
					show_menu_flag = true;
					break;

				case '5':
					if (!f.ARMED)
					{
            			checkFirstTime(true);
            		}
					show_menu_flag = true;
					break;

				case '6':
					cmd_bluetooth_change_name();
					break;

				case '7':
					core.useVComMultiwii  = true;
					_menu_printf("\r\nOK\r\n");
					break;

				case '8':
					core.useShowMspCmd = true;
					_menu_printf( "Monitor Start\r\n ");

					while( !_menu_received() )
					{
						osDelay(100);
					}
					core.useShowMspCmd = false;

					_menu_printf( "Monitor End\r\n ");

					break;

				case 'm':
				case 'M':
					_menu_show_menu();
					_menu_show_cmd();
					break;

				case 'z':
					cmd_go_bootloader();
					break;

				default:
					break;

    		}

    		if( show_menu_flag == true )
    		{
				_menu_show_menu();
				_menu_show_cmd();
    		}

        }
        osDelay(1);
    }
}




/*---------------------------------------------------------------------------
     TITLE   : cmd_go_bootloader
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void cmd_go_bootloader( void )
{
	/*
	USB_Cable_Config(DISABLE);

	RCC->APB1RSTR = 0xFFFFFFFF;
	RCC->APB2RSTR = 0xFFFFFFFF;
	RCC->APB1RSTR = 0x00000000;
	RCC->APB2RSTR = 0x00000000;
	*/

	if( mcfg.uart1_type == _UART1_TYPE_LCD )
	{
		thread_lcd_show_goboot();
	}

	osDelay(500);

	IWDG->PR  = 0; 		// divider / 4
	IWDG->RLR = 1;

	IWDG->KR  = 0xCCCC;	// Start
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
	osStatus ret;


	//-- MW의 메인 Loop를 중지 시킨다.
	//
	ret = osMutexWait( Mutex_Loop, 1000 );

	if( ret != osOK )
	{
		_menu_printf("Fail to osMutexWait\r\n");
		return;
	}


	_menu_printf("\r\nUart2 Open 9600BPS \r\n");

	core.blueport = uartOpen(USART2, NULL, 9600, MODE_RXTX);


	_menu_printf("\r\nAT -> ");
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


	_menu_printf("\r\nAT+BAUD4 -> ");
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

	_menu_printf("\r\nAT+RESET -> ");
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

	_menu_printf("\r\n");

	serialInit(mcfg.serial_baudrate);

	osMutexRelease( Mutex_Loop );
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
	osStatus ret;

	ret = osMutexWait( Mutex_Loop, 1000 );

	if( ret != osOK )
	{
		_menu_printf("Fail to osMutexWait\r\n");
		return;
	}

	core.blueport = uartOpen(USART2, NULL, 115200, MODE_RXTX);

	_menu_printf("\r\n");
	_menu_printf("AT -> ");

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
		_menu_printf("\r\nBluetooth OK");
	}
	else
	{
		_menu_printf("\r\nBluetooth Fail");
	}

	_menu_printf("\r\n");

	serialInit(mcfg.serial_baudrate);

	osMutexRelease( Mutex_Loop );
}





/*---------------------------------------------------------------------------
     TITLE   : cmd_bluetooth_change_name
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void cmd_bluetooth_change_name( void )
{
	uint32_t time_out;
	uint8_t  ch;
	uint8_t  ch_array[20] = "AT+NAME";
	uint8_t  ch_i;
	uint8_t  ch_offset;

	osStatus ret;


	ret = osMutexWait( Mutex_Loop, 1000 );

	if( ret != osOK )
	{
		_menu_printf("Fail to osMutexWait\r\n");
		return;
	}

	core.blueport = uartOpen(USART2, NULL, 115200, MODE_RXTX);


	//-- 이름 입력
	//
	_menu_printf("Enter Name : ");


	ch_i = 0;
	ch_offset = 7;

	while(1)
	{
		if( _menu_received() > 0 )
		{
			ch = _menu_getch();

			if( ch_i < 12 && ch != 0x0D )
			{
				ch_array[ch_offset+ch_i++] = ch;
			}
			else
			{
				break;
			}

			_menu_printf("%c", ch);

			if( ch == 0x0D )
			{
				_menu_printf("\r\n");
				break;
			}
		}
	}

	ch_array[ch_offset+ch_i] = 0;


	//-- 블루투스 설정
	//
	//serialPrint(core.blueport, "AT+NAMEbaram1");
	serialPrint(core.blueport, (const char *)ch_array);


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
			//_menu_putch(ch);
			ch_array[ch_i++] = ch;

			if( ch_i >= 2 ) break;
		}

		osDelay(1);
	}


	if( ch_array[0] == 'O' && ch_array[1] == 'K' )
	{
		_menu_printf("\r\nBluetooth OK");
	}
	else
	{
		_menu_printf("\r\nBluetooth Fail");
	}



	_menu_printf("\r\nEnd\r\n");

	serialInit(mcfg.serial_baudrate);

	osMutexRelease( Mutex_Loop );
}
