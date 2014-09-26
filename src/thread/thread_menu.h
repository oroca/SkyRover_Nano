//----------------------------------------------------------------------------
//    프로그램명 	: thread_menu 관련 함수 헤더
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type 	:
//
//    파일명     	: thread_menu.h
//----------------------------------------------------------------------------




                                                                                                 
#ifndef  _THREAD_MENU_H
#define  _THREAD_MENU_H



#include "thread_main.h"



#ifdef   THREAD_MENU_LOCAL
#define  EXT_THREAD_MENU_DEF
#else
#define  EXT_THREAD_MENU_DEF     extern
#endif


EXT_THREAD_MENU_DEF void thread_menu(void const *argument);

#endif
                                                                                                 
                                                                                                 

