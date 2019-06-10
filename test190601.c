#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
#include "iodefine.h"
#include "E2dataFlash.h"


short	cnt1,cnt2;
short	an00,an01,an02,an03,an04,an05,an06,an07;
short	pwm1,pwm2;
short	gyro1;
char	sw01;
short	result[14];
char	senddata[5], receivedata[5];
int	enc1, enc2;


void main(void)
{

while(1){
	
	if	(cnt1<=100)R_PG_IO_PORT_Write_P5(0x0);
	else if	(cnt1<=200)R_PG_IO_PORT_Write_P5(0x1);
	else if	(cnt1<=300)R_PG_IO_PORT_Write_P5(0x3);
	else if	(cnt1<=400)R_PG_IO_PORT_Write_P5(0x2);
	else	cnt1=0;
	
	R_PG_IO_PORT_Read_P55(&sw01);//スイッチ入力

	if(cnt2>=50)printf( "gyro=%6d ,an00=%4d ,an01=%4d ,an02=%4d ,an03=%4d ,an04=%4d ,an05=%4d ,an06=%4d ,an07=%4d ,sw=%4d ,enc1=%8d ,enc2=%8d \r",gyro1,an00,an01,an02,an03,an04,an05,an06,an07,sw01,enc1,enc2),cnt2 = 0;
	
	if(sw01) pwm1 = 50;
	else pwm1 = 0;
}

}

/*void Mtu2IcCmAIntFunc(void) 
{     //コンペアマッチA割り込み発生時処理
	
}*/

void Cmt0IntFunc(void){//1ms_timer
	int b1,b2;
	cnt1++;
	cnt2++;
	cnt_flash++;
	
	
	b1 = 4798 * pwm1 / 100;
	R_PG_Timer_SetTGR_B_MTU_U0_C0(b1);//PWM出力
	
	b2 = 4798 * pwm2 / 100;
	R_PG_Timer_SetTGR_D_MTU_U0_C0(b1);//PWM出力
	
	
	R_PG_Timer_GetCounterValue_MTU_U0_C1( & enc1 );
	R_PG_Timer_GetCounterValue_MTU_U0_C2( & enc2 );
	
	
	senddata[0] = 0x06;
	R_PG_SCI_I2CMode_Send_C0(0,0xd2,senddata,1);//I2C送信_ビット幅、アドレス、内容、送る数
	R_PG_SCI_I2CMode_Receive_C0(0,0xd3,receivedata,2);
	gyro1 = receivedata[1] << 8 | receivedata[0];
	
	
	R_PG_ADC_12_StartConversionSW_S12AD0();//AD変換開始
	R_PG_ADC_12_GetResult_S12AD0(result);//AD変換値をレジスタに格納
	an00 = result[0];
	an01 = result[1];
	an02 = result[2];
	an03 = result[3];
	an04 = result[4];
	an05 = result[5];
	an06 = result[6];
	an07 = result[7];
	R_PG_ADC_12_StopConversion_S12AD0();
}