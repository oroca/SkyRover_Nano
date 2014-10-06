//----------------------------------------------------------------------------
//    프로그램명 	: thread_lcd 관련 함수 헤더
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type 	:
//
//    파일명     	: thread_lcd.h
//----------------------------------------------------------------------------




                                                                                                 
#ifndef  _THREAD_LCD_H
#define  _THREAD_LCD_H



#include "thread_main.h"



#ifdef   THREAD_LCD_LOCAL
#define  EXT_THREAD_LCD_DEF
#else
#define  EXT_THREAD_LCD_DEF     extern
#endif


EXT_THREAD_LCD_DEF uint8_t	thread_lcd_draw_lcd_flag;




EXT_THREAD_LCD_DEF void thread_lcd(void const *argument);
EXT_THREAD_LCD_DEF void thread_lcd_show_goboot( void);


#endif
                                                                                                 
                                                                                                 

