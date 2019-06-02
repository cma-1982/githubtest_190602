//====================================//
// インクルード									//
//====================================//
#include "SCI.h"

//====================================//
// グローバル変数の宣言							//
//====================================//

///////////////////////////////////////////////////////////////////////////
// モジュール名 init_SCI1								//
// 処理概要     SCI1の初期化								//
// 引数         mode: 通信方式 rate:ボーレートをbpsで入力		//
// 戻り値       なし									//
///////////////////////////////////////////////////////////////////////////
void init_SCI1( char rate )
{
	unsigned char brr,abcs;
	
	
	// ボーレート選択
	if ( rate == RATE_9600 ) {
		abcs = 0;
		brr = 155;
	} else if ( rate == RATE_14400 ) {
		abcs = 0;
		brr = 103;
	} else if ( rate == RATE_19200 ) {
		abcs = 0;
		brr = 77;
	} else if ( rate == RATE_38400 ) {
		abcs = 0;
		brr = 38;
	} else if ( rate == RATE_57600 ) {
		abcs = 0;
		brr = 25;
	} else if ( rate == RATE_115200 ) {
		abcs = 0;
		brr = 12;
	} else if ( rate == RATE_230400 ) {
		abcs = 1;
		brr = 12;
	} else if ( rate == RATE_500000 ) {
		abcs = 0;
		brr = 2;
	} else if ( rate == RATE_750000 ) {
		abcs = 0;
		brr = 1;
	} else if ( rate == RATE_1000000 ) {
		abcs = 1;
		brr = 2;
	} else if ( rate == RATE_1500000 ) {
		abcs = 0;
		brr = 0;
	} else if ( rate == RATE_3000000 ) {
		abcs = 1;
		brr = 0;
	}
	
	// SCI1
	SYSTEM.PRCR.WORD = 0xA502;		// Release protect
	MSTP(SCI1) = 0;				// Wake up SCI1
	SYSTEM.PRCR.WORD = 0xA500;		// Protect
	
	SCI1.SCR.BYTE = 0;			// Set PFC of external pin used
	
	PORT2.ODR1.BIT.B4 = 0;		// P26 CMOS出力
	PORT3.ODR0.BIT.B0 = 0;		// P30 CMOS出力
	
	IEN( SCI1, RXI1 ) = 1;	// RXI割り込み開始
	IEN( SCI1, TXI1 ) = 0;	// TXI割り込み開始
	IEN( SCI1, TEI1 ) = 0;	// TEIE割り込み開始
	
	// Set MPC
	PORT3.PMR.BIT.B0 = 0;		// Disable PB1: peripheral
	PORT2.PMR.BIT.B6 = 0;		// Disable PB0: peripheral
	MPC.PWPR.BIT.B0WI = 0;		// Release protect
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P30PFS.BIT.PSEL = 0x0A;	// Set PB1: TXD1
	MPC.P26PFS.BIT.PSEL = 0x0A;	// Set PB0: RXD1
	MPC.PWPR.BIT.PFSWE = 0;		// Protect
	MPC.PWPR.BIT.B0WI = 1;
	PORT3.PMR.BIT.B0 = 1;		// PB1: peripheral
	PORT2.PMR.BIT.B6 = 1;		// PB0: peripheral
	
	// SCI1 Settings
	SCI1.SCR.BIT.CKE = 0;		// Disable CKE
	SCI1.SMR.BIT.CKS = 0;		// PCLK
	SCI1.SMR.BIT.MP = 0;		// マルチプロセッサ通信機能を禁止
	
	SCI1.SIMR1.BIT.IICM = 0;		// シリアルインタフェースモード
	SCI1.SPMR.BYTE = 0;			// クロック遅れ、反転なし
	SCI1.SCMR.BIT.SMIF = 0;		// シリアルコミュニケーションインターフェイスモード
	SCI1.SCMR.BIT.SDIR = 0;		// LSBファースト
	SCI1.SEMR.BIT.ACS0 = 0;		// 外部クロック入力
	SCI1.SEMR.BIT.ABCS = abcs;	// 1ビット転送期間中のクロックサイクル数　0: 16 1: 8
	
	SCI1.SMR.BIT.STOP = 0;		// 1 stop bit
	SCI1.SMR.BIT.PM = 0;		// none parity
	SCI1.SMR.BIT.CHR = 0;		// 8bit data length
	SCI1.SMR.BIT.CM = 0;		// 調歩同期式
	SCI1.BRR = brr;				// 12: 115200bps 1:750000bps 0:1500000bps
	SCI1.SCR.BIT.RIE = 1;		// RXI割り込み要求
	SCI1.SCR.BIT.TE = 1;			// Enable TX
	SCI1.SCR.BIT.RE = 1;			// Enable RX
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 charput								//
// 処理概要     printfの出力(printfで使用する)					//
// 引数         data:出力する一文字							//
// 戻り値       なし									//
///////////////////////////////////////////////////////////////////////////
void charput( uint8_t data )
{
	while(SCI1.SSR.BIT.TEND == 0);
	SCI1.TDR = data;
	SCI1.SSR.BIT.TEND = 0;
}
///////////////////////////////////////////////////////////////////////////
// モジュール名 charget								//
// 処理概要     scanfの入力(scanfで使用する)					//
// 引数         なし									//
// 戻り値       data:入力した一文字							//
///////////////////////////////////////////////////////////////////////////
char charget(void)
{
	uint8_t data;
	return data;
}
