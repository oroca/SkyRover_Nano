//----------------------------------------------------------------------------
//    프로그램명 	: thread_main 관련 함수 헤더
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type 	:
//
//    파일명     	: thread_main.h
//----------------------------------------------------------------------------




                                                                                                 
#ifndef  _THREAD_MAIN_H
#define  _THREAD_MAIN_H



#include "board.h"
#include "cmsis_os.h"



#ifdef   THREAD_MAIN_LOCAL
#define  EXT_THREAD_MAIN_DEF
#else
#define  EXT_THREAD_MAIN_DEF     extern
#endif


EXT_THREAD_MAIN_DEF osMutexId Mutex_Loop;


EXT_THREAD_MAIN_DEF void thread_main(void);

#endif
                                                                                                 
                                                                                                 

