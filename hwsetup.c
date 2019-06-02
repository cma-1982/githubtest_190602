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

void HardwareSetup(void)
{
R_PG_IO_PORT_SetPortNotAvailable();//�g��Ȃ��|�[�g�̐ݒ�
R_PG_Clock_WaitSet(0.01);//�N���b�N�ݒ�
R_PG_IO_PORT_Set_P5();//P�T������
R_PG_Timer_Set_CMT_U0_C0();//CMT0�ݒ�
R_PG_Timer_StartCount_CMT_U0_C0();//CMT0�����݃^�C�}����J�n
R_PG_ADC_12_Set_S12AD0();//AD�ϊ��ݒ�
R_PG_ADC_12_StartConversionSW_S12AD0();//AD�ϊ��J�n
init_SCI1(RATE_9600);
}
