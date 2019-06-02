#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
int	cnt1,cnt2,an03,pwm1,gyro1;
char	sw01;
short	result[14];
char	senddata[5], receivedata[5];
unsigned short	enc1;

void main(void)
{

while(1){
	
	if(cnt1>2500){
		R_PG_IO_PORT_Write_P5(0x1);
		cnt1=0;
	}
	else if(cnt1>=2000){
		R_PG_IO_PORT_Write_P5(0x2);
	}
	else if(cnt1>=1500){
		R_PG_IO_PORT_Write_P5(0x4);
	}
	else if(cnt1>=1000){
		R_PG_IO_PORT_Write_P5(0x8);
	}
	else if(cnt1>=500){
		R_PG_IO_PORT_Write_P5(0x0);
		
	}
	
	R_PG_IO_PORT_Read_P55(&sw01);//スイッチ入力

	R_PG_ADC_12_GetResult_S12AD0(result);//AD変換値をレジスタに格納
	an03 = result[3];
	
	if(cnt2>=100)printf( "%4d,%4d,%4d\r",an03,sw01,enc1),cnt2 = 0;
	
	if(sw01) pwm1 = 50;
	else pwm1 = 0;
	
	
}

}
void Cmt0IntFunc(void){//1ms_timer
	int b1;
	cnt1++;
	cnt2++;
	b1 = 4798 * pwm1 / 100;
	R_PG_Timer_SetTGR_B_MTU_U0_C0(b1);//TGR_D　PWM出力
	
	R_PG_Timer_GetCounterValue_MTU_U0_C2( &enc1 );
	
	senddata[0] = 0x06;
	R_PG_SCI_I2CMode_Send_C0(0,0xd2,senddata,1);//I2C送信_ビット幅、アドレス、内容、送る数
	
	R_PG_SCI_I2CMode_Receive_C0(0,0xd3,receivedata,2);

	gyro1 = receivedata[1] << 8 | receivedata[0];
	
}