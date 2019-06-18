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
R_PG_IO_PORT_SetPortNotAvailable();//�g��Ȃ��|�[�g�̐ݒ�
R_PG_Clock_WaitSet(0.01);//�N���b�N�ݒ�

R_PG_IO_PORT_Set_P5();//P�T������

R_PG_Timer_Set_CMT_U0_C0();//CMT0�ݒ�
R_PG_Timer_StartCount_CMT_U0_C0();//CMT0�����݃^�C�}����J�n

R_PG_SCI_Set_C0();//I2C�ݒ�
senddata_HW[0] = 0x0f;
senddata_HW[1] = 0x00;
senddata_HW[2] = 0x10;
senddata_HW[3] = 0x03;
senddata_HW[4] = 0x11;
senddata_HW[5] = 0x00;
R_PG_SCI_I2CMode_Send_C0(0,0xd2,senddata_HW,6);//I2C���M_�r�b�g���A�A�h���X�A���e

init_SCI1(RATE_115200);

R_PG_ADC_12_Set_S12AD0();//AD�ϊ��ݒ�

initFlash();//�f�[�^�t���b�V��������

R_PG_Timer_Set_MTU_U0_C0();
R_PG_Timer_Set_MTU_U0_C1();
R_PG_Timer_Set_MTU_U0_C2();
R_PG_Timer_Set_MTU_U0_C3();
R_PG_Timer_Set_MTU_U0_C4();
R_PG_Timer_SynchronouslyStartCount_MTU_U0(1,1,1,1,1);//PWM�A�G���R�[�_�J�E���g����J�n

}
