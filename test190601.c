#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
#include "iodefine.h"
#include "E2dataFlash.h"


void 		spi_write( unsigned char data );
unsigned char	who_am_i_read( void );
void		gyro_start( void );
void		gyro_read( void );

short		pattern;
short		cnt1,cnt2,cnt3;
short		an00,an01,an02,an03,an04,an05,an06,an07;
signed int	pwm1,pwm2,pwm3,pwm4;
short		gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
int		gx;
char		eep_data;
char		sw01;
short		result[14];
char		senddata[5], receivedata[5];
int		enc1, enc2;
short		spi_data;


void main(void)
{

while(1){

switch( pattern ){
	case 0:
			/*senddata[0] = 0x00, senddata[1] = 0x00;//データ読む
			R_PG_SCI_I2CMode_Send_C0(0,0xa0,senddata,2);//I2C送信_ビット幅、アドレス、内容、送る数
			R_PG_SCI_I2CMode_Receive_C0(0,0xa1,receivedata,1);
			eep_data = receivedata[0];*/
			R_PG_IO_PORT_Write_P5(0xf);
			gyro_start();
			pattern = 1;
				
			//initFlash();
	break;
	
	case 1:
		//if(cnt2>=100)printf( "gyro=%6d, an00=%4d, an01=%4d, an02=%4d, an03=%4d, an04=%4d, an05=%4d, an06=%4d, an07=%4d, sw=%4d,  enc1=%8d, enc2=%8d, eeprom=%8d\r",gyro1,an00,an01,an02,an03,an04,an05,an06,an07,sw01,enc1,enc2,eep_data),cnt2 = 0;
		//if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		if(cnt2>=100)printf( "pattern = %2d, gyroX = %6d, gyroY = %6d, gyroZ = %6d, accX = %6d, accY = %6d, accZ = %6d\r", pattern, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z ), cnt2 = 0;
		
		if(!sw01&&cnt3>=500) {
			/*senddata[0] = 0x00, senddata[1] = 0x00;//データ読む
			R_PG_SCI_I2CMode_Send_C0(0,0xa0,senddata,2);//I2C送信_ビット幅、アドレス、内容、送る数
			R_PG_SCI_I2CMode_Receive_C0(0,0xa1,receivedata,1);
			eep_data = receivedata[0];*/
			pattern = 2;
			cnt3 = 0;
		} else {
			pwm1 = 0;
			pwm2 = 0;
			pwm3 = 0;
			pwm4 = 0;
		}
	break;
	
	case 2:
		if	(cnt1<=100)R_PG_IO_PORT_Write_P5(0x1);
		else if	(cnt1<=200)R_PG_IO_PORT_Write_P5(0x0);
		else if	(cnt1<=300)R_PG_IO_PORT_Write_P5(0x1);
		else if	(cnt1<=400)R_PG_IO_PORT_Write_P5(0x0);
		else	cnt1 = 0;
		
		if(!sw01&&cnt3>=500) pattern = 3, cnt3 = 0;
		
		if(cnt3>=6000){
			cnt3 = 0;
		} else if (cnt3>=5000) {
			pwm1 = -100;
		} else if (cnt3>=4000) {
			pwm1 = -50;
		} else if (cnt3>=3000) {
			pwm1 =  0;
		} else if (cnt3>=2000) {
			pwm1 = 100;
		} else if (cnt3>=1000) {
			pwm1 = 50;
		} else {
			pwm1 =  0;
		}
		
		pwm2 = 0;
		pwm3 = 0;
		pwm4 = 0;
	break;
	
	case 3:
		if	(cnt1<=100)R_PG_IO_PORT_Write_P5(0x3);
		else if	(cnt1<=200)R_PG_IO_PORT_Write_P5(0x0);
		else if	(cnt1<=300)R_PG_IO_PORT_Write_P5(0x3);
		else if	(cnt1<=400)R_PG_IO_PORT_Write_P5(0x0);
		else	cnt1 = 0;
		
		if(!sw01&&cnt3>=500) pattern = 4, cnt3 = 0;
		
		if(cnt3>=6000){
			cnt3 = 0;
		} else if (cnt3>=5000) {
			pwm2 = -90;
		} else if (cnt3>=4000) {
			pwm2 = -50;
		} else if (cnt3>=3000) {
			pwm2 =  0;
		} else if (cnt3>=2000) {
			pwm2 = 90;
		} else if (cnt3>=1000) {
			pwm2 = 50;
		} else {
			pwm2 =  0;
		}
		
		pwm1 = 0;
		pwm3 = 0;
		pwm4 = 0;
	break;
	
	case 4:
		if	(cnt1<=100)R_PG_IO_PORT_Write_P5(0x7);
		else if	(cnt1<=200)R_PG_IO_PORT_Write_P5(0x0);
		else if	(cnt1<=300)R_PG_IO_PORT_Write_P5(0x7);
		else if	(cnt1<=400)R_PG_IO_PORT_Write_P5(0x0);
		else	cnt1 = 0;
		
		if(!sw01&&cnt3>=500) pattern = 5, cnt3 = 0;
		
		if(cnt3>=6000){
			cnt3 = 0;
		} else if (cnt3>=5000) {
			pwm3 = -90;
		} else if (cnt3>=4000) {
			pwm3 = -50;
		} else if (cnt3>=3000) {
			pwm3 =  0;
		} else if (cnt3>=2000) {
			pwm3 = 90;
		} else if (cnt3>=1000) {
			pwm3 = 50;
		} else {
			pwm3 =  0;
		}
		
		pwm1 = 0;
		pwm2 = 0;
		pwm4 = 0;
	break;
	
	case 5:
		if	(cnt1<=100)R_PG_IO_PORT_Write_P5(0xf);
		else if	(cnt1<=200)R_PG_IO_PORT_Write_P5(0x0);
		else if	(cnt1<=300)R_PG_IO_PORT_Write_P5(0xf);
		else if	(cnt1<=400)R_PG_IO_PORT_Write_P5(0x0);
		else	cnt1 = 0;
		
		if(!sw01&&cnt3>=500) pattern = 1, cnt3 = 0;
		
		if(cnt3>=6000){
			cnt3 = 0;
		} else if (cnt3>=5000) {
			pwm4 = -90;
		} else if (cnt3>=4000) {
			pwm4 = -50;
		} else if (cnt3>=3000) {
			pwm4 =  0;
		} else if (cnt3>=2000) {
			pwm4 = 90;
		} else if (cnt3>=1000) {
			pwm4 = 50;
		} else {
			pwm4 =  0;
		}
		pwm1 = 0;
		pwm2 = 0;
		pwm3 = 0;
	break;
	
	case 6:
		if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		
		if(!sw01&&cnt3>=2000){
			pattern = 1;
			cnt3 = 0;
		} else {
			pwm1 = 0;
			pwm2 = 0;
		}
	break;
break;
}//pattern
}//while
}//main

/*void Mtu2IcCmAIntFunc(void) 
{     //コンペアマッチA割り込み発生時処理
	
}*/

void Cmt0IntFunc(void){//1ms_timer
	signed int b1,b2,b3,b4;
	cnt1++;
	cnt2++;
	cnt3++;
	cnt_flash++;
	
	R_PG_IO_PORT_Read_P55(&sw01);//スイッチ入力
	
	if( pwm1 >= 0 ) {
		b1 = 4798 *  pwm1 / 100;
		R_PG_Timer_SetTGR_B_MTU_U0_C0(b1);//PWM出力1
		R_PG_IO_PORT_Write_PB4(1);
	} else {
		b1 = 4798 * -pwm1 / 100;
		R_PG_Timer_SetTGR_B_MTU_U0_C0(b1);//PWM出力1
		R_PG_IO_PORT_Write_PB4(0);
	}

	if( pwm2 >= 0 ) {
		b2 = 4798 *  pwm2 / 100;
		R_PG_Timer_SetTGR_D_MTU_U0_C0(b2);//PWM出力2
		R_PG_IO_PORT_Write_PB2(1);
	} else {
		b2 = 4798 * -pwm2 / 100;
		R_PG_Timer_SetTGR_D_MTU_U0_C0(b2);//PWM出力2
		R_PG_IO_PORT_Write_PB2(0);
	}

	if( pwm3 >= 0 ) {
		b3 = 4798 *  pwm3 / 100;
		R_PG_Timer_SetTGR_B_MTU_U0_C3(b3);//PWM出力3
		R_PG_IO_PORT_Write_PB6(1);
	} else {
		b3 = 4798 * -pwm3 / 100;
		R_PG_Timer_SetTGR_B_MTU_U0_C3(b3);//PWM出力3
		R_PG_IO_PORT_Write_PB6(0);
	}

	if( pwm4 >= 0 ) {
		b4 = 4798 *  pwm4 / 100;
		R_PG_Timer_SetTGR_D_MTU_U0_C3(b4);//PWM出力4
		R_PG_IO_PORT_Write_PB7(1);
	} else {
		b4 = 4798 * -pwm4 / 100;
		R_PG_Timer_SetTGR_D_MTU_U0_C3(b4);//PWM出力4
		R_PG_IO_PORT_Write_PB7(0);
	}
	
	R_PG_Timer_GetCounterValue_MTU_U0_C1( & enc1 );
	R_PG_Timer_GetCounterValue_MTU_U0_C2( & enc2 );

	gyro_read();

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

/*void spi_write( unsigned char data )
{
	unsigned char data_tr[ 1 ];
	unsigned char data_re[ 1 ];
	volatile short data;
	
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 1);
	R_PG_IO_PORT_Write_P5(0xf);
	//printf("msd_write = 0x%x\n", data_tr[ 0 ]);
}*/
void gyro_start( void )
{
	unsigned char data_tr[ 3 ];
	unsigned char data_re[ 3 ];
	unsigned short j;
	
	data_tr[0]  = 0x6b;
	data_tr[1]  = 0x80;//0x00
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P5(0xf);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x1a;
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P5(0xf);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x1b;
	data_tr[1]  = 0x18;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P5(0xf);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x1c;
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P5(0xf);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x68;
	data_tr[1]  = 0x07;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P5(0xf);
	for( j=0; j<10000; j++ );
	
	/*
	data_tr[0] = 0x37;
	data_tr[1] = 0x02;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P5(0xf);

	data_tr[0]  = 0x6a;
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P5(0xf);
	
	data_tr[0]  = 0x6c;
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P5(0xf);
	
	data_tr[0]  = 0x23;
	data_tr[1]  = 0xf8;//0x00
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P5(0xf);*/
}

void gyro_read( void )
{
	unsigned char data_tr[ 7 ], data_re[ 7 ], low, high;
	
	data_tr[0]  = 0x3b | 0x80;
	data_tr[1]  = 0x3c | 0x80;
	data_tr[2]  = 0x3d | 0x80;
	data_tr[3]  = 0x3e | 0x80;
	data_tr[4]  = 0x3f | 0x80;
	data_tr[5]  = 0x40 | 0x80;
	
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 7);
	R_PG_IO_PORT_Write_P5(0xf);
	
	high = data_re[1];
	low  = data_re[2];
	acc_x = high << 8 | low;
	
	high = data_re[3];
	low  = data_re[4];
	acc_y= high << 8 | low;
	
	high = data_re[5];
	low  = data_re[6];
	acc_z= high << 8 | low;
	
	
	data_tr[0]  = 0x43 | 0x80;
	data_tr[1]  = 0x44 | 0x80;
	data_tr[2]  = 0x45 | 0x80;
	data_tr[3]  = 0x46 | 0x80;
	data_tr[4]  = 0x47 | 0x80;
	data_tr[5]  = 0x48 | 0x80;
	
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 7);
	R_PG_IO_PORT_Write_P5(0xf);
	
	high = data_re[1];
	low  = data_re[2];
	gyro_x= high << 8 | low;
	
	high = data_re[3];
	low  = data_re[4];
	gyro_y= high << 8 | low;
	
	high = data_re[5];
	low  = data_re[6];
	gyro_z= high << 8 | low;
}

unsigned char who_am_i_read( void )
{
	unsigned char data_tr[ 2 ];
	unsigned char data_re[ 2 ];
	//unsigned char data;
	
	data_tr[0] = 0x75 | 0x80;
	data_tr[1] = 0x00;
	
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	//R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 1);
	R_PG_IO_PORT_Write_P5(0xf);
	
	//data = data_re[0];
	//ret = data & 0x00ff;
	
	//printf("msd_read = 0x%x\n", ret);
	return  data_re[1];
}

/*
unsigned char spi_read( void ){	
	unsigned char	data_tr_dummy[] = { 0x75 }, data_re[ 1 ] = { 0xff }, ret;
	volatile short	data;
	R_PG_IO_PORT_Write_P5(0x0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr_dummy, data_re, 1);
	R_PG_IO_PORT_Write_P5(0xf);
	
	ret = data_re[0];
	//ret = data & 0x00ff;
	return  ret;
}*/