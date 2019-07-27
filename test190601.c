#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
#include "iodefine.h"
#include "E2dataFlash.h"


void 		spi_write( unsigned char data );
unsigned char	who_am_i_read( void );
void		gyro_start( void );
void		gyro_read( void );
void		ui_ctrl( void );
void		pwm_ctrl( void );

short		pattern;
short		cnt1,cnt2,cnt3,cntled;
char		timer4k, sensor_out;
short		sen1L,sen2L,sen3L,sen4L,sen1H,sen2H,sen3H,sen4H,sen1,sen2,sen3,sen4,batad,VR1,VR2;
signed int	pwm1,pwm2,pwm3,pwm4;
short		gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
int		gx;
char		eep_data;
char		dip, stsw, upsw, dnsw;
short		led, sen_pwm;
short		result[14];
char		senddata[5], receivedata[5];
int		enc;
short		spi_data;

int		reg1, reg2, reg3;
unsigned char 	data_tr_reg[ 3 ];
unsigned char 	data_re_reg[ 3 ];

void main(void)
{

while(1){

switch( pattern ){
	case 0:
			/*senddata[0] = 0x00, senddata[1] = 0x00;//データ読む
			R_PG_SCI_I2CMode_Send_C0(0,0xa0,senddata,2);//I2C送信_ビット幅、アドレス、内容、送る数
			R_PG_SCI_I2CMode_Receive_C0(0,0xa1,receivedata,1);
			eep_data = receivedata[0];*/
			//R_PG_IO_PORT_Write_P5(0xf);

	data_tr_reg[0]  = 0x37 | 0x80;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr_reg, data_re_reg, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	reg1 = data_re_reg[1];
	
			gyro_start();

	data_tr_reg[0]  = 0x37 | 0x80;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr_reg, data_re_reg, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	reg2 = data_re_reg[1];
	
			pattern = 1;
				
			//initFlash();
	break;
	
	case 1:
		//if(cnt2>=100)printf( "sen1=%4d, sen2=%4d, sen3=%4d, sen4=%4d, bat=%4d, vr1=%4d, vr2=%4d, enc=%8d\r",sen1,sen2,sen3,sen4,batad,VR1,VR2,enc),cnt2 = 0;
		//if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		//if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		if(cnt2>=300)printf( "pattern = %2d, accx = %5d, accy = %5d, accz = %5d, gyrox = %5d, gyroy = %5d, gyroz = %5d, reg1 = %5x, reg2 = %5x,\r", pattern, acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, reg1, reg2 ), cnt2 = 0;

		sensor_out = 1;
		
		     if( cntled < 200 ) led = 0x11;
		else if( cntled < 400 ) led = 0x22;
		else if( cntled < 600 ) led = 0x44;
		else if( cntled < 800 ) led = 0x88;
		else cntled = 0;
		
		if(stsw&&cnt3>=500) {
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
		if(stsw&&cnt3>=500) pattern = 3, cnt3 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0x0f;
		
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
		sensor_out = 0;
		pwm2 = 0;
		pwm3 = 0;
		pwm4 = 0;
	break;
	
	case 3:
		if(stsw&&cnt3>=500) pattern = 4, cnt3 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0xf0;
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
		if(stsw&&cnt3>=500) pattern = 5, cnt3 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0xcc;
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
		if(stsw&&cnt3>=500) pattern = 6, cnt3 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0x33;
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
		if(stsw&&cnt3>=500) pattern = 1, cnt3 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0xff;
		pwm1 = 0;
		pwm2 = 0;
		pwm3 = 0;
		pwm4 = 0;
	break;
	
	case 7:
		if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		
		if(stsw&&cnt3>=2000){
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

void Cmt0IntFunc(void){//0.25ms_timer
	
	timer4k++;
	switch( timer4k ){
		
		case 1:
			R_PG_ADC_12_StartConversionSW_S12AD0();//AD変換開始
			R_PG_ADC_12_GetResult_S12AD0(result);//AD変換値をレジスタに格納
			sen4H = result[1];
			sen3H = result[2];
			sen2H = result[3];
			sen1H = result[4];
			batad = result[5];
			VR1   = result[6];
			VR2   = result[7];
			R_PG_ADC_12_StopConversion_S12AD0();
			
			R_PG_IO_PORT_Write_P15(0);//センサ発光ＯＦＦ
			
			sen1 = sen1H - sen1L;
			sen2 = sen2H - sen2L;
			sen3 = sen3H - sen3L;
			sen4 = sen4H - sen4L;
			
			
			cnt1++;
			cnt2++;
			cnt3++;
			cntled++;
			cnt_flash++;
			ui_ctrl();
			R_PG_Timer_GetCounterValue_MTU_U0_C2( & enc );//エンコーダ値取得
		break;
		
		case 2:
			//servoctrl?
			pwm_ctrl();
		break;

		case 3:
			if( pattern != 0 )gyro_read();
		break;
		
		case 4:
			R_PG_ADC_12_StartConversionSW_S12AD0();//AD変換開始
			R_PG_ADC_12_GetResult_S12AD0(result);//AD変換値をレジスタに格納
			sen4L = result[1];
			sen3L = result[2];
			sen2L = result[3];
			sen1L = result[4];
			R_PG_ADC_12_StopConversion_S12AD0();
			
			if(sensor_out)R_PG_IO_PORT_Write_P15(1);//センサ発光ＯＮ
			
			timer4k = 0;
		break;
	}
}

void pwm_ctrl( void )
{
	signed int b1,b2,b3,b4;
	
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
}

void ui_ctrl( void )
{
	char a,b,c,d,e,f,g,h;
	
	R_PG_IO_PORT_Read_PD0(&a);
	R_PG_IO_PORT_Read_PD1(&b);
	R_PG_IO_PORT_Read_PD2(&c);
	R_PG_IO_PORT_Read_PD3(&d);
	dip = !d + (!c*2) + (!b*4) + (!a*8);
	
	R_PG_IO_PORT_Read_PD6(&e);
	R_PG_IO_PORT_Read_PD5(&f);
	R_PG_IO_PORT_Read_PD4(&g);
	stsw = !e;
	upsw = !f;
	dnsw = !g;
	
	R_PG_IO_PORT_Write_PA(~led);
}

/*void spi_write( unsigned char data )
{
	unsigned char data_tr[ 1 ];
	unsigned char data_re[ 1 ];
	volatile short data;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 1);
	R_PG_IO_PORT_Write_P50(1);
	//printf("msd_write = 0x%x\n", data_tr[ 0 ]);
}*/
void gyro_start( void )
{
	unsigned char data_tr[ 3 ];
	unsigned char data_re[ 3 ];
	unsigned short j;
	
	/*data_tr[0]  = 0x1a;
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	

	
	data_tr[0]  = 0x23;
	data_tr[1]  = 0x00;//0xf8
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	

	
	data_tr[0]  = 0x68;
	data_tr[1]  = 0x07;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x6a;
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);*/
		
	data_tr[0]  = 0x6b;
	data_tr[1]  = 0x00;//0x80
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0] = 0x37;
	data_tr[1] = 0x02;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x1a;
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x1b;
	data_tr[1]  = 0x18;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x1c;
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	/*data_tr[0]  = 0x6c;
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);*/
}

void gyro_read( void )
{
	unsigned char data_tr[ 15 ], data_re[ 15 ], low, high;
	
	data_tr[0]  = 0x3b | 0x80;
	data_tr[1]  = 0x3c | 0x80;
	data_tr[2]  = 0x3d | 0x80;
	data_tr[3]  = 0x3e | 0x80;
	data_tr[4]  = 0x3f | 0x80;
	data_tr[5]  = 0x40 | 0x80;
	data_tr[6]  = 0x41 | 0x80;
	data_tr[7]  = 0x42 | 0x80;
	data_tr[8]  = 0x43 | 0x80;
	data_tr[9]  = 0x44 | 0x80;
	data_tr[10] = 0x45 | 0x80;
	data_tr[11] = 0x46 | 0x80;
	data_tr[12] = 0x47 | 0x80;
	data_tr[13] = 0x48 | 0x80;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 15);
	R_PG_IO_PORT_Write_P50(1);
	
	high = data_re[1];
	low  = data_re[2];
	acc_x = high << 8 | low;
	
	high = data_re[3];
	low  = data_re[4];
	acc_y= high << 8 | low;
	
	high = data_re[5];
	low  = data_re[6];
	acc_z= high << 8 | low;
	
	high = data_re[9];
	low  = data_re[10];
	gyro_x= high << 8 | low;
	
	high = data_re[11];
	low  = data_re[12];
	gyro_y= high << 8 | low;
	
	high = data_re[13];
	low  = data_re[14];
	gyro_z= high << 8 | low;
}

unsigned char who_am_i_read( void )
{
	unsigned char data_tr[ 2 ];
	unsigned char data_re[ 2 ];
	//unsigned char data;
	
	data_tr[0] = 0x75 | 0x80;
	data_tr[1] = 0x00;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	//R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 1);
	R_PG_IO_PORT_Write_P50(1);
	
	//data = data_re[0];
	//ret = data & 0x00ff;
	
	//printf("msd_read = 0x%x\n", ret);
	return  data_re[1];
}

/*
unsigned char spi_read( void ){	
	unsigned char	data_tr_dummy[] = { 0x75 }, data_re[ 1 ] = { 0xff }, ret;
	volatile short	data;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr_dummy, data_re, 1);
	R_PG_IO_PORT_Write_P50(1);
	
	ret = data_re[0];
	//ret = data & 0x00ff;
	return  ret;
}*/