//----------------------------------------------------------------------------
//    프로그램명 	: VCom 관련 함수
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type		:
//
//    파일명     	: Hw_VCom.h
//----------------------------------------------------------------------------




//----- 헤더파일 열기
//
#define  HW_VCOM_LOCAL

#include "drv_vcom.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "printf.h"

//-- 내부 선언
//



//-- 내부 변수
//



//-- 내부 함수
//

static void usb_putc(void *p, char c)
{
    Hw_VCom_Putch(c);
}


/*---------------------------------------------------------------------------
     TITLE   : Hw_VCom_Init
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_VCom_Init( void )
{
	Hw_VCom_Q_Init();


	Hw_VCom_RxdFuncPtr = NULL;


	Set_System();

	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();	
}





/*---------------------------------------------------------------------------
     TITLE	: Hw_VCom_Getch
     WORK
			: 시리얼 포트에서 문자 1바이트 읽는다.
     ARG
     RET
---------------------------------------------------------------------------*/
u8 Hw_VCom_Getch( void )
{
	u8 Uart_GetData = 0;

	while( 1 )
	{
		// 버퍼에 데이터 들어올때까지 기다린다.
		if( HW_VCOM_Q_VAILD(0) > 0 ) break;
	}

	Hw_VCom_Q_Pop( 0, &Uart_GetData );

	return Uart_GetData;
}





/*---------------------------------------------------------------------------
     TITLE	: Hw_VCom_IsReceived
     WORK
			: 시리얼 포트에서 데이터가 왔는지 검사
     ARG
     RET
---------------------------------------------------------------------------*/
u8 Hw_VCom_IsReceived( void )
{
	if( HW_VCOM_Q_VAILD(0) > 0 ) return 1;
	else 						 return 0;
}





extern void USB_Send_Data( u8 SendData );

/*---------------------------------------------------------------------------
     TITLE	: Hw_VCom_Putch
     WORK
			: 시리얼 포트로 문자 1바이트 전송
     ARG
     RET
---------------------------------------------------------------------------*/
void Hw_VCom_Putch( char Uart_PutData )
{
	if( bDeviceState == CONFIGURED )
	{
		USB_Send_Data( Uart_PutData );
	}
}



/*---------------------------------------------------------------------------
     TITLE	: Hw_Uart_SetReceiveFuncISR
     WORK
			: 시리얼 포트에서 데이터 수신시 실행할 함수 설정 .
     ARG
     RET
---------------------------------------------------------------------------*/
void Hw_VCom_SetReceiveFuncISR( void (*ISR_FuncPtr)(char Ch) )
{
	Hw_VCom_RxdFuncPtr = ISR_FuncPtr;	
}





/*---------------------------------------------------------------------------
     TITLE	: Hw_VCom_PrintEx
     WORK
     ARG
     RET
---------------------------------------------------------------------------*/
void Hw_VCom_PrintEx( char *UartPrintData )
{
	while( *UartPrintData != '\0' )
	{
		Hw_VCom_Putch( *UartPrintData );
		UartPrintData++;
	}        
}



/*---------------------------------------------------------------------------
     TITLE	: Hw_VCom_Printf
     WORK
     ARG
     RET
---------------------------------------------------------------------------*/
void Hw_VCom_Printf( char *format, ... )
{
	//char Str[200];
	
	//va_list ap;
	
	//va_start( ap, format );

	//vsprintf( Str, format, ap );	

	//sprintf(Str, format );
	
	//va_end(ap);	
	
	//Hw_VCom_PrintEx( Str );


    va_list va;
    va_start(va, format);
    tfp_format(NULL, usb_putc, format, va);
    va_end(va);		

}
