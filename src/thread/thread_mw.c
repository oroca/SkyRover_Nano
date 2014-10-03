//----------------------------------------------------------------------------
//    프로그램명 	: thread_mw 관련 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: thread_mw.c
//----------------------------------------------------------------------------



//----- 헤더파일 열기
//
#define  THREAD_MW_LOCAL

#include "thread_mw.h"
#include "mw.h"

//-- 외부
//
extern core_t core;


//-- 내부 선언
//



//-- 내부 변수
//



//-- 내부 함수
//







/*---------------------------------------------------------------------------
     TITLE   : thread_mw
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void thread_mw(void const *argument)
{
    (void) argument;
    osStatus ret;

    DEBUG_PRINT("Thread multiwii\r\n");


    for (;;)
    {
    	ret = osMutexWait( Mutex_Loop, 10 );

    	if( ret == osOK )
    	{
    		loop();
            osMutexRelease( Mutex_Loop );
    	}
    }
}
