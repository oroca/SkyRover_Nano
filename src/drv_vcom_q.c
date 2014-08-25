//----------------------------------------------------------------------------
//    프로그램명 	:
//
//    만든이     	: Cho Han Cheol
//
//    날  짜     	: 2013. 1. 21.
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: Hw_VCom_Q.c
//----------------------------------------------------------------------------


//----- 헤더파일 열기
//
#define  HW_VCOM_Q_LOCAL

#include "drv_vcom_q.h"





/*---------------------------------------------------------------------------
     TITLE   : Hw_VCom_Q_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Hw_VCom_Q_Init( void )
{
	u8 i;

	for( i=0; i<HW_VCOM_Q_CH_MAX; i++ )
	{
		Hw_VCom_Q_Start[i] = Hw_VCom_Q_End[i] = 0;
	}
}




/*---------------------------------------------------------------------------
     TITLE   : HW_VCOM_Q_SIZE
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u32 HW_VCOM_Q_SIZE( u8 Ch )
{
	return (Hw_VCom_Q_Start[Ch] - Hw_VCom_Q_End[Ch] + HW_VCOM_Q_BUFFER_MAX) % HW_VCOM_Q_BUFFER_MAX;
}





/*---------------------------------------------------------------------------
     TITLE   : HW_VCOM_Q_VAILD
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u32 HW_VCOM_Q_VAILD( u8 Ch )
{
	return HW_VCOM_Q_SIZE(Ch);
}





/*---------------------------------------------------------------------------
     TITLE   : Hw_VCom_Q_PushReady
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u32 Hw_VCom_Q_PushReady( u8 Ch )
{
	if( Hw_VCom_Q_Size[Ch] < HW_VCOM_Q_BUFFER_MAX )	return TRUE;
	else                                  			return FALSE;
}




/*---------------------------------------------------------------------------
     TITLE   : Hw_VCom_Q_Push
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u8 Hw_VCom_Q_Push( u8 Ch, u8  *PushData )
{

	if (HW_VCOM_Q_SIZE(Ch) == (HW_VCOM_Q_BUFFER_MAX-1)) return FALSE;

	Hw_VCom_Q_Buffer[Ch][Hw_VCom_Q_Start[Ch]++]  = *PushData;
	Hw_VCom_Q_Start[Ch] 						%= HW_VCOM_Q_BUFFER_MAX;

	return TRUE;
}




/*---------------------------------------------------------------------------
     TITLE   : Hw_VCom_Q_Push
     WORK    :
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
u8 Hw_VCom_Q_Pop( u8 Ch, u8 *pData )
{
	if (HW_VCOM_Q_SIZE(Ch) == 0) return FALSE;

	*pData = Hw_VCom_Q_Buffer[Ch][Hw_VCom_Q_End[Ch]++];

	Hw_VCom_Q_End[Ch] %= HW_VCOM_Q_BUFFER_MAX;

    return TRUE;
}


















 
