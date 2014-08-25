//----------------------------------------------------------------------------
//    프로그램명 	:
//
//    만든이     	: Cho Han Cheol
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: Hw_VCom_Q.h
//----------------------------------------------------------------------------
                                                                                                 
#ifndef __HW_VCOM_Q_H__
#define __HW_VCOM_Q_H__


#ifdef   HW_VCOM_Q_LOCAL
#define  EXT_HW_VCOM_Q_DEF
#else
#define  EXT_HW_VCOM_Q_DEF     extern
#endif



#include "board.h"
#include "usb_type.h"


#define HW_VCOM_Q_CH_MAX       1
#define HW_VCOM_Q_BUFFER_MAX   1024                //  버퍼 최대 갯수


#define HW_VCOM_Q_EMPTY        1
#define HW_VCOM_Q_FULL         0
#define HW_VCOM_POP_SUCCESS    2


EXT_HW_VCOM_Q_DEF u32 HW_VCOM_Q_SIZE( u8 Ch );
EXT_HW_VCOM_Q_DEF u32 HW_VCOM_Q_VAILD( u8 Ch );

EXT_HW_VCOM_Q_DEF u8  Hw_VCom_Q_Buffer[HW_VCOM_Q_CH_MAX][ HW_VCOM_Q_BUFFER_MAX+1 ];


EXT_HW_VCOM_Q_DEF s16  Hw_VCom_Q_Size [HW_VCOM_Q_CH_MAX];                       // 버퍼의 데이터 숫자
EXT_HW_VCOM_Q_DEF s16  Hw_VCom_Q_Start[HW_VCOM_Q_CH_MAX];                      // 버퍼의 시작 포인터
EXT_HW_VCOM_Q_DEF s16  Hw_VCom_Q_End  [HW_VCOM_Q_CH_MAX];                        // 버퍼의 끝 포인터


EXT_HW_VCOM_Q_DEF void Hw_VCom_Q_Init(void);
EXT_HW_VCOM_Q_DEF u32  Hw_VCom_Q_PushReady( u8 Ch );
EXT_HW_VCOM_Q_DEF u8   Hw_VCom_Q_Push( u8 Ch, u8 *PushData );
EXT_HW_VCOM_Q_DEF u8   Hw_VCom_Q_Pop( u8 Ch, u8 *pData );

#endif
