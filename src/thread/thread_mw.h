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
//    파일명     	: thread_mw.h
//----------------------------------------------------------------------------




                                                                                                 
#ifndef  _THREAD_MW_H
#define  _THREAD_MW_H



#include "thread_main.h"



#ifdef   THREAD_MW_LOCAL
#define  EXT_THREAD_MW_DEF
#else
#define  EXT_THREAD_MW_DEF     extern
#endif


EXT_THREAD_MW_DEF void thread_mw(void const *argument);

#endif
                                                                                                 
                                                                                                 

