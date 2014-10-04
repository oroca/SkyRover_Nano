//----------------------------------------------------------------------------
//    프로그램명 	: thread_main 관련 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: thread_main.h
//----------------------------------------------------------------------------



//----- 헤더파일 열기
//
#define  THREAD_MAIN_LOCAL

#include "thread_main.h"
#include "thread_mw.h"
#include "thread_menu.h"
#include "thread_lcd.h"
#include "mw.h"


//-- 외부
//
extern core_t core;


//-- 내부 선언
//



//-- 내부 변수
//
//-- Thread
//
osThreadId Thread_Handle_mw;
osThreadId Thread_Handle_menu;
osThreadId Thread_Handle_lcd;



//-- 내부 함수
//




//-- IP
//
osMutexDef(MUTEX1);


/*---------------------------------------------------------------------------
     TITLE   : thread_main
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void thread_main(void)
{


	Mutex_Loop = osMutexCreate( osMutex(MUTEX1) );

	if( Mutex_Loop == NULL ) DEBUG_PRINT("Mutex Fail\r\n");


    //-- Thread 1 definition
    //
    osThreadDef(TASK1, thread_mw  , osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    osThreadDef(TASK2, thread_menu, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    osThreadDef(TASK3, thread_lcd,  osPriorityNormal, 0, configMINIMAL_STACK_SIZE);



    //-- Start thread
    //
    Thread_Handle_mw   = osThreadCreate(osThread(TASK1), NULL);
    Thread_Handle_menu = osThreadCreate(osThread(TASK2), NULL);
    Thread_Handle_lcd  = osThreadCreate(osThread(TASK3), NULL);



    //-- Start scheduler
    //
    osKernelStart(NULL, NULL);


    while(1);
}

