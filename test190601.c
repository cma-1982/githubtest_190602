#include "R_PG_default190601.h"//PDGで生成された設定
#include "SCI.h"
int	cnt1,an03;
char	sw01;
short	result[14];

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
	printf( "%d,%d\n",an03,sw01 );
	
	
}

}
void Cmt0IntFunc(void){//1ms_timer
	cnt1++;
}