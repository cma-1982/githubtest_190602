#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
#include "iodefine.h"
#include "E2dataFlash.h"


void 		spi_write( unsigned char data );
unsigned char	who_am_i_read( void );
void		gyro_start( void );
void		gyro_read( void );
void		ui_ctrl( void );
void		markercheck( void );
void 		servo1_ctrl( void );
void 		motor_ctrl( void );
void		pwm_ctrl( void );
void		servo_angle( void );
void		distance_reset( void );

short		pattern;
short		cnt1,cnt2,cnt3,cntled;
char		timer4k, timer5ms, sensor_out;
short		sen1L,sen2L,sen3L,sen4L,sen1H,sen2H,sen3H,sen4H,senTR,senTL,senMR,senML,batad,VR1,VR2;
signed long	kp1,kd1,kp2,kd2, scb1, scb2, servo2_t, servo1angle, servo2angle;
signed long	turnangle, degoffset, tspeed, speed, cspeed, Ybuff;
signed int	pwm1,pwm2,pwm3,pwm4;
short		gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, deg_x, deg_y, deg_z;
int		gx;
char		eep_data;
char		dip, stsw, upsw, dnsw;
short		led, sen_pwm;
short		result[14];
char		senddata[5], receivedata[5];
unsigned short	enc, enc_buff;
short		acc;
unsigned long	distance, distanceline, distanceline_mkl, distanceline_mkr, distanceline_goal;
short		spi_data;
char		mpflag, run, mklflag, mkrflag, goalflag, mk;


void main(void)
{
	gyro_start();
	//R_FlashDataAreaAccess(0xFFFF, 0xFFFF);
while(1){

switch( pattern ){
	case 0:
			mpflag = 0;
			run = 0;
			sensor_out = 0;
			distance = 0;
			
		if(stsw&&cnt1>=300) {
			pattern = 1;
			cnt1 = 0;
		}
		if( batad <= 3300 ){ //バッテリー電圧７Ｖ以下
			     if( cntled < 200 ) led = 0xf0;
			else if( cntled < 400 ) led = 0x00;
			else cntled = 0;
		} else {
			led = speed;
		}
	break;
	
	case 1:
		//if(cnt2>=100)printf( "senTR=%4d, senTL=%4d, senMR=%4d, senML=%4d, bat=%4d, vr1=%4d, vr2=%4d, enc=%8d\r",senTR,senTL,senMR,senML,batad,VR1,VR2,enc),cnt2 = 0;
		//if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		//if(cnt2>=100)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		//if(cnt2>=100)printf( "pattern = %2d, accx = %5d, accy = %5d, accz = %5d, gyrox = %5d, gyroy = %5d, deg_z = %7d,\r", pattern, acc_x, acc_y, acc_z, gyro_x, gyro_y, deg_z ), cnt2 = 0;
		//if(cnt2>=100)printf( "gyroz = %5d, deg_z = %7d, acc = %4d, speed = %4d, distance = %8d\r",  gyro_z, deg_z, acc, speed, distance ), cnt2 = 0;

		sensor_out = 1;
		mpflag = 1;
		run = 0;
		
		     if( cntled < 200 ) led = 0x0f;
		else if( cntled < 400 ) led = 0x00;
		else cntled = 0;
		
		if(cnt1>=3000) {
			pattern = 2;
			distance_reset();
			cnt1 = 0;
		}
	break;
	
	case 2:
		if( goalflag >= 2 ) {
			distanceline = distance;
			cnt1 = 0;
			pattern = 3;
		}
		
		tspeed = dip;
		sensor_out = 1;
		mpflag = 1;
		run = 1;
		
		if( batad <= 3100 ){ //バッテリー電圧７Ｖ以下
			     if( cntled < 200 ) led = 0xf0;
			else if( cntled < 400 ) led = 0x00;
			else cntled = 0;
		} else {
			led = 0x00;
		}
	break;
	
	case 3:
		if( (distance-distanceline) >= 100 && cnt1 >= 500 ) {
			distanceline = distance;
			cnt1 = 0;
			pattern = 4;
		}
		
		tspeed = 5;
		sensor_out = 1;
		mpflag = 1;
		run = 1;
		
		led = 0xff;
	break;
	
	case 4:
		sensor_out = 0;
		mpflag = 0;
		run = 0;
		
		led = 0xf0;
	break;
	
	case 5:
		if(stsw&&cnt1>=500) pattern = 6, cnt1 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0x33;
		if(cnt1>=6000){
			cnt1 = 0;
		} else if (cnt1>=5000) {
			pwm4 = -90;
		} else if (cnt1>=4000) {
			pwm4 = -50;
		} else if (cnt1>=3000) {
			pwm4 =  0;
		} else if (cnt1>=2000) {
			pwm4 = 90;
		} else if (cnt1>=1000) {
			pwm4 = 50;
		} else {
			pwm4 =  0;
		}
		pwm1 = 0;
		pwm2 = 0;
		pwm3 = 0;
	break;
	
	case 6:
		if(stsw&&cnt1>=500) pattern = 1, cnt1 = 0;
		if(cnt2>=300)printf( "pattern = %2d, DIP = %4x, st = %1d, up = %1d, dn = %1d\r", pattern, dip, stsw, upsw, dnsw ), cnt2 = 0;
		led = 0xff;
		pwm1 = 0;
		pwm2 = 0;
		pwm3 = 0;
		pwm4 = 0;
	break;
	
	case 7:
		if(cnt2>=100)printf( "pattern = %2d, eep = %6d\r", pattern, eep_data ),cnt2 = 0;
		
		if(stsw&&cnt1>=2000){
			pattern = 1;
			cnt1 = 0;
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
			
			senTR = (sen1H - sen1L)*2;
			senTL = sen2H - sen2L;
			senML = sen3H - sen3L;
			senMR = sen4H - sen4L;
			
			
			cnt1++;
			cnt2++;
			cnt3++;
			cntled++;
			cnt_flash++;
			timer5ms++;
			
			ui_ctrl();
			
			if( timer5ms >= 20 ){
			R_PG_Timer_GetCounterValue_MTU_U0_C2( & enc );//エンコーダ値取得
			speed = enc - enc_buff;
			enc_buff = enc;
			distance += speed;
			timer5ms = 0;
			}
		break;
		
		case 2:
			servo_angle();
			servo1_ctrl();
			motor_ctrl();
			pwm_ctrl();
			markercheck();
			
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
void distance_reset( void )
{
	distance = 0;
	distanceline = 0;
	distanceline_mkl = 0;
	distanceline_mkr = 0;
	distanceline_goal = 0;
}

void markercheck( void )
{
	int threshold, l, r, g;
	
	l = distance-distanceline_mkl;
	r = distance-distanceline_mkr;
	g = distance-distanceline_goal;
	
	threshold = 2500;
	
	if( senML > threshold ) mklflag++;
	else mklflag = 0;
	
	if( servo1angle < 500 && servo1angle > -500 && senMR > threshold ) mkrflag++;
	else mkrflag = 0;
	
	if( mklflag > 0 ) distanceline_mkl = distance, mklflag = 0;
	if( mkrflag > 1 ) distanceline_mkr = distance, mkrflag = 0;

	
	if( r > 15 && r < 40 && l > 60 && g > 80 ) goalflag++, mk = 1, distanceline_goal = distance;
	else mk = 0;
}

void servo1_ctrl( void ){
	int p, d, ret, sen_b;
	
	kp1 = 20;
	kd1 = 30;
	sen_b = (senTL-senTR);
	
	p = sen_b * kp1;
	d = (sen_b-scb1) * kd1;
	
	scb1 = sen_b;
	if( (senTL+senTR) >= 2300 ) ret = 0;
	else ret = p + d;
	ret = ret/64;
	
	     if( ret >=  120 ) ret =  120;
	else if( ret <= -120 ) ret = -120;
	
	     if( mpflag && sensor_out && servo1angle >=  1250 )	pwm4 =  20;
	else if( mpflag && sensor_out && servo1angle <= -1250 )	pwm4 = -20;
	else if( mpflag && sensor_out )			pwm4 = ret;
}

void motor_ctrl( void ){
	signed long   YP, YD, Yret, Rret, Lret, s, y, b;
	signed long   AP, accel, pwmlimit, alimit, acceleration;
	
	if( run ){
		acceleration = 5;
		pwmlimit = 150;
		
		turnangle = -servo1angle/2;
		degoffset = ( turnangle * speed );
		
		y = gyro_z/7;
		
		YP = ( y - degoffset ) * 10 ;
		YD = ( ( y - degoffset ) - Ybuff ) * 10;
		Yret = YP+YD;
		Ybuff = ( y - degoffset );
		Yret = Yret / 128;
		
		if( Yret > pwmlimit ) Yret = pwmlimit;
		else if( Yret < -pwmlimit ) Yret = -pwmlimit;
		
		Rret =  Yret;
		Lret = -Yret;
		
		if( 0 <= Yret ) alimit = pwmlimit - Yret;
		else            alimit = pwmlimit + Yret;
		
		
		b = servo1angle / 10;
		
		//     if( b >=  1 ) tspeed = tspeed-(tspeed*b/ 180);
		//else if( b <= -1 ) tspeed = tspeed-(tspeed*b/-180);
		//else		   tspeed = tspeed-(tspeed*1/ 180);
		
		if( tspeed ) {
			AP = ( speed - tspeed )*4;
			accel = AP;
			
			if      ( accel >  alimit ) accel =  alimit;
			else if ( accel < -alimit ) accel = -alimit;
			
			Rret += accel;
			Lret += accel;
		}
		
		if( Rret > pwmlimit ) Rret = pwmlimit;
		else if( Rret < -pwmlimit ) Rret = -pwmlimit;
		if( Lret > pwmlimit ) Lret = pwmlimit;
		else if( Lret < -pwmlimit ) Lret = -pwmlimit;
		
		pwm3 = Rret;
		pwm2 = Lret;
	} else {
		pwm3 = 0;
		pwm2 = 0;
	}
}

void pwm_ctrl( void ){
	signed int b1,b2,b3,b4,limit;
	
	limit = 150;
	
	     if( pwm2 >=  limit) pwm2 =  limit;
	else if( pwm2 <= -limit) pwm2 = -limit;
	     if( pwm3 >=  limit) pwm3 =  limit;
	else if( pwm3 <= -limit) pwm3 = -limit;
	     if( pwm4 >=  limit) pwm4 =  limit;
	else if( pwm4 <= -limit) pwm4 = -limit;
	
	if(!mpflag)pwm2=0,pwm3=0,pwm4=0;
	
	if( pwm2 >= 0 ) {
		b2 = 1199 *  pwm2 / 200;
		R_PG_Timer_SetTGR_D_MTU_U0_C0(b2);//PWM出力2
		R_PG_IO_PORT_Write_PB2(0);
	} else {
		b2 = 1199 * -pwm2 / 200;
		R_PG_Timer_SetTGR_D_MTU_U0_C0(b2);//PWM出力2
		R_PG_IO_PORT_Write_PB2(1);
	}
	
	if( pwm3 >= 0 ) {
		b3 = 1199 *  pwm3 / 200;
		R_PG_Timer_SetTGR_B_MTU_U0_C3(b3);//PWM出力3
		R_PG_IO_PORT_Write_PB6(1);
	} else {
		b3 = 1199 * -pwm3 / 200;
		R_PG_Timer_SetTGR_B_MTU_U0_C3(b3);//PWM出力3
		R_PG_IO_PORT_Write_PB6(0);
	}
	
	if( pwm4 >= 0 ) {
		b4 = 1199 *  pwm4 / 200;
		R_PG_Timer_SetTGR_D_MTU_U0_C3(b4);//PWM出力4
		R_PG_IO_PORT_Write_PB7(0);
	} else {
		b4 = 1199 * -pwm4 / 200;
		R_PG_Timer_SetTGR_D_MTU_U0_C3(b4);//PWM出力4
		R_PG_IO_PORT_Write_PB7(1);
	}
}

void servo_angle( void ){
	servo1angle = VR1 - 2100;
}

void ui_ctrl( void ){
	char a,b,c,d,e,f,g,h;
	
	R_PG_IO_PORT_Read_PD0(&a);
	R_PG_IO_PORT_Read_PD1(&b);
	R_PG_IO_PORT_Read_PD2(&c);
	R_PG_IO_PORT_Read_PD3(&d);
	dip = !d + (!c*2) + (!b*4) + (!a*8);
	
	R_PG_IO_PORT_Read_PD6(&e);
	R_PG_IO_PORT_Read_PD5(&f);
	R_PG_IO_PORT_Read_PD4(&g);
	dnsw = !e;
	upsw = !f;
	stsw = !g;
	
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
	
	data_tr[0]  = 0x6b;//PWR_MGMT_1
	data_tr[1]  = 0x00;//0x00
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0] = 0x37;//INT_PIN_CFG
	data_tr[1] = 0x02;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x1b;//GYRO_CONFIG
	data_tr[1]  = 0x18;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	
	data_tr[0]  = 0x1c;//ACCEL_CONFIG
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	/*
	data_tr[0]  = 0x1a;//CONFIG
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	for( j=0; j<10000; j++ );
	

	
	data_tr[0]  = 0x68;//SIGNAL_PATH_RESET
	data_tr[1]  = 0x07;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x6a;//USER_CTRL
	data_tr[1]  = 0x10;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x6c;//PWR_MGMT_2
	data_tr[1]  = 0x00;
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 3);
	R_PG_IO_PORT_Write_P50(1);
	for( j=0; j<10000; j++ );
	
	data_tr[0]  = 0x23;//FIFO_EN
	data_tr[1]  = 0xf8;//0x00
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);*/
}

void gyro_read( void ){
	unsigned char data_tr[ 7 ], data_re[ 7 ], low, high;
	
	/*data_tr[0]  = 0x3b | 0x80;
	data_tr[1]  = 0x3c | 0x80;
	data_tr[2]  = 0x3d | 0x80;
	data_tr[3]  = 0x3e | 0x80;
	data_tr[4]  = 0x3f | 0x80;
	data_tr[5]  = 0x40 | 0x80;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 7);
	R_PG_IO_PORT_Write_P50(1);
	
	high = data_re[1];
	low  = data_re[2];
	acc_x = high << 8 | low;
	
	high = data_re[3];
	low  = data_re[4];
	acc_y= high << 8 | low;
	
	high = data_re[5];
	low  = data_re[6];
	acc_z= high << 8 | low;*/
	
	
	data_tr[0]  = 0x43 | 0x80;
	data_tr[1]  = 0x44 | 0x80;
	data_tr[2]  = 0x45 | 0x80;
	data_tr[3]  = 0x46 | 0x80;
	data_tr[4]  = 0x47 | 0x80;
	data_tr[5]  = 0x48 | 0x80;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 7);
	R_PG_IO_PORT_Write_P50(1);
	
	high = data_re[1];
	low  = data_re[2];
	gyro_x= high << 8 | low;
	
	high = data_re[3];
	low  = data_re[4];
	gyro_y= high << 8 | low;
	
	high = data_re[5];
	low  = data_re[6];
	gyro_z= (high << 8 | low)-15;
	
	deg_z += gyro_z/64;
}

unsigned char who_am_i_read( void ){
	unsigned char data_tr[ 2 ];
	unsigned char data_re[ 2 ];
	
	data_tr[0] = 0x75 | 0x80;
	data_tr[1] = 0x00;
	
	R_PG_IO_PORT_Write_P50(0);
	R_PG_SCI_SPIMode_Transfer_C2( data_tr, data_re, 2);
	R_PG_IO_PORT_Write_P50(1);
	
	return  data_re[1];
}