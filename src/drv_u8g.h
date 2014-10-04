//----------------------------------------------------------------------------
//    프로그램명 	: LCD 라이브러리 u8g 함수 헤더
//
//    만든이     	:
//
//    날  짜     	:
//    
//    최종 수정  	:
//
//    MPU_Type 	:
//
//    파일명     	: drv_u8g.h
//----------------------------------------------------------------------------
                   

#ifndef  _DRV_U8G_H
#define  _DRV_U8G_H



#include "board.h"

#include "u8g.h"


#ifdef   DRV_U8G_LOCAL
#define  EXT_DRV_U8G_DEF
#else
#define  EXT_DRV_U8G_DEF     extern
#endif



EXT_DRV_U8G_DEF void u8g_Delay(uint16_t val);
EXT_DRV_U8G_DEF void u8g_MicroDelay(void);
EXT_DRV_U8G_DEF void u8g_10MicroDelay(void);


EXT_DRV_U8G_DEF uint8_t u8g_com_sw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);




#endif




