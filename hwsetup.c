/************************************************************************
*
* Device     : RX/RX600/RX63N,RX631
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 0.10  (2011-02-21)  [Hardware Manual Revision : 0.01]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2011 Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
************************************************************************/
#include "R_PG_default190601.h"
#include "SCI.h"
#include "iodefine.h"


#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif

char	senddata_HW[8];

void HardwareSetup(void)
{
R_PG_IO_PORT_SetPortNotAvailable();//使わないポートの設定
R_PG_Clock_WaitSet(0.01);//クロック設定

R_PG_IO_PORT_Set_P5();//P５初期化

R_PG_Timer_Set_CMT_U0_C0();//CMT0設定
R_PG_Timer_StartCount_CMT_U0_C0();//CMT0割込みタイマ動作開始

R_PG_SCI_Set_C0();//I2C設定
senddata_HW[0] = 0x0f;
senddata_HW[1] = 0x00;
senddata_HW[2] = 0x10;
senddata_HW[3] = 0x03;
senddata_HW[4] = 0x11;
senddata_HW[5] = 0x00;
R_PG_SCI_I2CMode_Send_C0(0,0xd2,senddata_HW,6);//I2C送信_ビット幅、アドレス、内容

init_SCI1(RATE_115200);

R_PG_ADC_12_Set_S12AD0();//AD変換設定

initFlash();//データフラッシュ初期化

R_PG_Timer_Set_MTU_U0_C0();
R_PG_Timer_Set_MTU_U0_C1();
R_PG_Timer_Set_MTU_U0_C2();
R_PG_Timer_Set_MTU_U0_C3();
R_PG_Timer_Set_MTU_U0_C4();
R_PG_Timer_SynchronouslyStartCount_MTU_U0(1,1,1,1,1);//PWM、エンコーダカウント動作開始

}
