//----------------------------------------------------------------------------
//    프로그램명 	: thread_lcd 관련 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: thread_lcd.h
//----------------------------------------------------------------------------



//----- 헤더파일 열기
//
#define  THREAD_LCD_LOCAL

#include "thread_lcd.h"
#include "mw.h"
#include "drv_u8g.h"
#include "thread_lcd_logo.h"


//-- 외부
//
extern core_t  core;
extern uint8_t vbat;

//-- 내부 선언
//



//-- 내부 변수
//
u8g_t u8g;

uint8_t	lcd_state;


//-- 내부 함수
//
void _draw_intro( void );
void _draw_status( void );
void _draw_go_boot( void );



/*---------------------------------------------------------------------------
     TITLE   : thread_lcd
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void thread_lcd(void const *argument)
{
    (void) argument;

    DEBUG_PRINT("Thread Lcd\r\n");

    osDelay(500);

    if( mcfg.uart1_type == _UART1_TYPE_LCD )
    {
    	u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_i2c, u8g_com_sw_i2c_fn);
    	u8g_SetColorIndex(&u8g, U8G_MODE_BW);
    }
    else
    {
    	for(;;)
    	{
    		osDelay(1000);
    	}
    }


    lcd_state = 0;


    for (;;)
    {
    	switch( lcd_state )
    	{
    		case 0:
    			_draw_intro();
    			lcd_state = 1;
    			osDelay(3000);
    			break;

    		case 1:
    			_draw_status();
    			break;

    		case 99:
    			_draw_go_boot();
    			break;
    	}

		osDelay(100);
    }
}





/*---------------------------------------------------------------------------
     TITLE   : thread_lcd_show_goboot
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void thread_lcd_show_goboot( void )
{
	lcd_state = 99;
}




/*---------------------------------------------------------------------------
     TITLE   : _draw_intro
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void _draw_intro( void )
{
    u8g_FirstPage(&u8g);
    do
    {
    	//u8g_SetFont(&u8g, u8g_font_unifont);
    	u8g_SetFont(&u8g, u8g_font_6x10);
    	//u8g_SetFontPosTop(&u8g);

    	//u8g_DrawStr(&u8g,  0, 0, "Hello World!");
    	u8g_DrawBitmap(&u8g, 0, 0, 128/8, 64, SkyRover_Nano_Logo);

    	u8g_DrawStr(&u8g, 128/2-u8g_GetStrWidth(&u8g, _SKYROVER_VER_STR_)/2, 64, _SKYROVER_VER_STR_);


    } while ( u8g_NextPage(&u8g) );
}





/*---------------------------------------------------------------------------
     TITLE   : _draw_status
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void _draw_status( void )
{
	char str[50];
	uint8_t line_space = 12;


    u8g_FirstPage(&u8g);
    do
    {
    	u8g_SetFont(&u8g, u8g_font_6x10);
    	u8g_SetFontPosTop(&u8g);

    	if( f.ARMED ) u8g_DrawStr( &u8g, 128-u8g_GetStrWidth(&u8g, "Armed"), 0, "Armed");
    	else		  u8g_DrawStr( &u8g, 128-u8g_GetStrWidth(&u8g, "DisArmed"), 0, "DisArmed");

    	tfp_sprintf( str, "%d.%dV", vbat/10, vbat%10 );
    	u8g_DrawStr( &u8g, 128-u8g_GetStrWidth(&u8g, str), line_space*1, str );

    	tfp_sprintf( str, "R: %d.%d", angle[0]/10, abs(angle[0]%10) );
    	u8g_DrawStr( &u8g, 0, line_space*1, str );

    	tfp_sprintf( str, "P: %d.%d", angle[1]/10, abs(angle[1]%10) );
    	u8g_DrawStr( &u8g, 0, line_space*2, str );

    	tfp_sprintf( str, "Y: %d", heading );
    	u8g_DrawStr( &u8g, 0, line_space*3, str );

    	tfp_sprintf( str, "A: %d", EstAlt );
    	u8g_DrawStr( &u8g, 0, line_space*4, str );

    	tfp_sprintf( str, "Head: %d", rcOptions[BOXHEADFREE] );
    	u8g_DrawStr( &u8g, 128/2, line_space*3, str );

    	tfp_sprintf( str, "Baro: %d", rcOptions[BOXBARO] );
    	u8g_DrawStr( &u8g, 128/2, line_space*4, str );



    } while ( u8g_NextPage(&u8g) );
}





/*---------------------------------------------------------------------------
     TITLE   : _draw_go_boot
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void _draw_go_boot( void )
{
    u8g_FirstPage(&u8g);
    do
    {
    	u8g_SetFont(&u8g, u8g_font_unifont);
    	u8g_SetFontPosTop(&u8g);

    	u8g_DrawStr(&u8g,  0, 0, "Go to boot..");
    } while ( u8g_NextPage(&u8g) );
}
