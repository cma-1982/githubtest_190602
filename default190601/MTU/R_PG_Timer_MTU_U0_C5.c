/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_Timer_MTU_U0_C5.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
* Limitations  : 
******************************************************************************
* History : 04.06.2019 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_pdl_mtu2.h"
#include "r_pdl_intc.h"
#include "r_pdl_definitions.h"
#include "R_PG_IntFuncsExtern.h"


/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_Set_MTU_U0_C5(void)
*
* Function Name: R_PG_Timer_Set_MTU_U0_C5
*
* Description  : MTUの設定
*
* Arguments    : なし
*
* Return Value : true  : 設定が正しく行われた場合
*              : false : 設定に失敗した場合
*
* Calling Functions : R_MTU2_Create
*                   : R_MTU2_Create_load_defaults
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_Set_MTU_U0_C5(void)
{
	R_MTU2_Create_structure parameters;

	R_MTU2_Create_load_defaults( &parameters );

	parameters.counter_operation = PDL_MTU2_CLKU_PCLK_DIV_1 | PDL_MTU2_CLKV_PCLK_DIV_1 | PDL_MTU2_CLKW_PCLK_DIV_1;
	parameters.TGR_U_V_W_operation = PDL_MTU2_U_CM | PDL_MTU2_V_CM | PDL_MTU2_W_CM;

	return R_MTU2_Create(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_StartCount_MTU_U0_C5(void)
*
* Function Name: R_PG_Timer_StartCount_MTU_U0_C5
*
* Description  : MTUのカウント動作開始
*
* Arguments    : なし
*
* Return Value : true  : カウント動作の再開が正しく行われた場合
*              : false : カウント動作の再開に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_StartCount_MTU_U0_C5(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_START_U | PDL_MTU2_START_V | PDL_MTU2_START_W;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_StartCount_MTU_U0_C5_U(void)
*
* Function Name: R_PG_Timer_StartCount_MTU_U0_C5_U
*
* Description  : MTUのカウント動作開始 (U相)
*
* Arguments    : なし
*
* Return Value : true  : カウント動作の再開が正しく行われた場合
*              : false : カウント動作の再開に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_StartCount_MTU_U0_C5_U(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_START_U;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_StartCount_MTU_U0_C5_V(void)
*
* Function Name: R_PG_Timer_StartCount_MTU_U0_C5_V
*
* Description  : MTUのカウント動作開始 (V相)
*
* Arguments    : なし
*
* Return Value : true  : カウント動作の再開が正しく行われた場合
*              : false : カウント動作の再開に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_StartCount_MTU_U0_C5_V(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_START_V;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_StartCount_MTU_U0_C5_W(void)
*
* Function Name: R_PG_Timer_StartCount_MTU_U0_C5_W
*
* Description  : MTUのカウント動作開始 (W相)
*
* Arguments    : なし
*
* Return Value : true  : カウント動作の再開が正しく行われた場合
*              : false : カウント動作の再開に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_StartCount_MTU_U0_C5_W(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_START_W;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_HaltCount_MTU_U0_C5(void)
*
* Function Name: R_PG_Timer_HaltCount_MTU_U0_C5
*
* Description  : MTUのカウント動作を一時停止
*
* Arguments    : なし
*
* Return Value : true  : 停止に成功した場合
*              : false : 停止に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_HaltCount_MTU_U0_C5(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_STOP_U | PDL_MTU2_STOP_V | PDL_MTU2_STOP_W;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_HaltCount_MTU_U0_C5_U(void)
*
* Function Name: R_PG_Timer_HaltCount_MTU_U0_C5_U
*
* Description  : MTUのカウント動作を一時停止 (U相)
*
* Arguments    : なし
*
* Return Value : true  : 停止に成功した場合
*              : false : 停止に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_HaltCount_MTU_U0_C5_U(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_STOP_U;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_HaltCount_MTU_U0_C5_V(void)
*
* Function Name: R_PG_Timer_HaltCount_MTU_U0_C5_V
*
* Description  : MTUのカウント動作を一時停止 (V相)
*
* Arguments    : なし
*
* Return Value : true  : 停止に成功した場合
*              : false : 停止に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_HaltCount_MTU_U0_C5_V(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_STOP_V;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_HaltCount_MTU_U0_C5_W(void)
*
* Function Name: R_PG_Timer_HaltCount_MTU_U0_C5_W
*
* Description  : MTUのカウント動作を一時停止 (W相)
*
* Arguments    : なし
*
* Return Value : true  : 停止に成功した場合
*              : false : 停止に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_HaltCount_MTU_U0_C5_W(void)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_MTU2_STOP_W;
	parameters.register_selection = PDL_NO_DATA;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_GetCounterValue_MTU_U0_C5(uint16_t * counter_u_val, uint16_t * counter_v_val, uint16_t * counter_w_val)
*
* Function Name: R_PG_Timer_GetCounterValue_MTU_U0_C5
*
* Description  : MTUのカウンタ値を取得
*
* Arguments    : uint16_t * counter_u_val : カウンタU値の格納先
*              : uint16_t * counter_v_val : カウンタV値の格納先
*              : uint16_t * counter_w_val : カウンタW値の格納先
*
* Return Value : true  : 取得に成功した場合
*              : false : 取得に失敗した場合
*
* Calling Functions : R_MTU2_ReadChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_GetCounterValue_MTU_U0_C5(uint16_t * counter_u_val, uint16_t * counter_v_val, uint16_t * counter_w_val)
{
	uint16_t * local_u = PDL_NO_PTR;
	uint16_t * local_v = PDL_NO_PTR;
	uint16_t * local_w = PDL_NO_PTR;

	if( counter_u_val ){
		local_u = counter_u_val;
	}
	if( counter_v_val ){
		local_v = counter_v_val;
	}
	if( counter_w_val ){
		local_w = counter_w_val;
	}

	return R_MTU2_ReadChannel(
		5,
		PDL_NO_PTR,
		local_u,
		local_v,
		local_w,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetCounterValue_MTU_U0_C5(uint16_t counter_u_val, uint16_t counter_v_val, uint16_t counter_w_val)
*
* Function Name: R_PG_Timer_SetCounterValue_MTU_U0_C5
*
* Description  : MTUのカウンタ値を設定
*
* Arguments    : uint16_t counter_u_val : カウンタUに設定する値
*              : uint16_t counter_v_val : カウンタVに設定する値
*              : uint16_t counter_w_val : カウンタWに設定する値
*
* Return Value : true  : カウンタ値の設定に成功した場合
*              : false : カウンタ値の設定に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetCounterValue_MTU_U0_C5(uint16_t counter_u_val, uint16_t counter_v_val, uint16_t counter_w_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_COUNTER_U | PDL_MTU2_REGISTER_COUNTER_V | PDL_MTU2_REGISTER_COUNTER_W;
	parameters.TCNT_TCNTU_value = counter_u_val;
	parameters.TGRA_TCNTV_value = counter_v_val;
	parameters.TGRB_TCNTW_value = counter_w_val;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetCounterValue_MTU_U0_C5_U(uint16_t counter_u_val)
*
* Function Name: R_PG_Timer_SetCounterValue_MTU_U0_C5_U
*
* Description  : MTUのカウンタ値を設定 (U相)
*
* Arguments    : uint16_t counter_u_val : カウンタに設定する値
*
* Return Value : true  : カウンタ値の取得が正しく行われた場合
*              : false : カウンタ値の取得に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_U(uint16_t counter_u_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_COUNTER_U;
	parameters.TCNT_TCNTU_value = counter_u_val;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetCounterValue_MTU_U0_C5_V(uint16_t counter_v_val)
*
* Function Name: R_PG_Timer_SetCounterValue_MTU_U0_C5_V
*
* Description  : MTUのカウンタ値を設定 (V相)
*
* Arguments    : uint16_t counter_v_val : カウンタに設定する値
*
* Return Value : true  : カウンタ値の取得が正しく行われた場合
*              : false : カウンタ値の取得に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_V(uint16_t counter_v_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_COUNTER_V;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = counter_v_val;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetCounterValue_MTU_U0_C5_W(uint16_t counter_w_val)
*
* Function Name: R_PG_Timer_SetCounterValue_MTU_U0_C5_W
*
* Description  : MTUのカウンタ値を設定 (W相)
*
* Arguments    : uint16_t counter_w_val : カウンタに設定する値
*
* Return Value : true  : カウンタ値の取得が正しく行われた場合
*              : false : カウンタ値の取得に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_W(uint16_t counter_w_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_COUNTER_W;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = counter_w_val;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_GetTGR_MTU_U0_C5(uint16_t * tgr_u_val, uint16_t * tgr_v_val, uint16_t * tgr_w_val)
*
* Function Name: R_PG_Timer_GetTGR_MTU_U0_C5
*
* Description  : ジェネラルレジスタの値の取得
*
* Arguments    : uint16_t * tgr_u_val : ジェネラルレジスタU値の格納先
*              : uint16_t * tgr_v_val : ジェネラルレジスタV値の格納先
*              : uint16_t * tgr_w_val : ジェネラルレジスタW値の格納先
*
* Return Value : true  : 取得に成功した場合
*              : false : 取得に失敗した場合
*
* Calling Functions : R_MTU2_ReadChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_GetTGR_MTU_U0_C5(uint16_t * tgr_u_val, uint16_t * tgr_v_val, uint16_t * tgr_w_val)
{
	uint16_t * local_u = PDL_NO_PTR;
	uint16_t * local_v = PDL_NO_PTR;
	uint16_t * local_w = PDL_NO_PTR;

	if( tgr_u_val ){
		local_u = tgr_u_val;
	}
	if( tgr_v_val ){
		local_v = tgr_v_val;
	}
	if( tgr_w_val ){
		local_w = tgr_w_val;
	}

	return R_MTU2_ReadChannel(
		5,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		local_u,
		local_v,
		local_w,
		PDL_NO_PTR
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetTGR_U_MTU_U0_C5(uint16_t tgr_u_val)
*
* Function Name: R_PG_Timer_SetTGR_U_MTU_U0_C5
*
* Description  : ジェネラルレジスタの値の設定 (TGRU)
*
* Arguments    : uint16_t tgr_u_val : ジェネラルレジスタに設定する値
*
* Return Value : true  : 設定が正しく行われた場合
*              : false : 設定に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetTGR_U_MTU_U0_C5(uint16_t tgr_u_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_TGRU;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = tgr_u_val;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetTGR_V_MTU_U0_C5(uint16_t tgr_v_val)
*
* Function Name: R_PG_Timer_SetTGR_V_MTU_U0_C5
*
* Description  : ジェネラルレジスタの値の設定 (TGRV)
*
* Arguments    : uint16_t tgr_v_val : ジェネラルレジスタに設定する値
*
* Return Value : true  : 設定が正しく行われた場合
*              : false : 設定に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetTGR_V_MTU_U0_C5(uint16_t tgr_v_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_TGRV;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = tgr_v_val;
	parameters.TGRE_TGRW_value = PDL_NO_DATA;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SetTGR_W_MTU_U0_C5(uint16_t tgr_w_val)
*
* Function Name: R_PG_Timer_SetTGR_W_MTU_U0_C5
*
* Description  : ジェネラルレジスタの値の設定 (TGRW)
*
* Arguments    : uint16_t tgr_w_val : ジェネラルレジスタに設定する値
*
* Return Value : true  : 設定が正しく行われた場合
*              : false : 設定に失敗した場合
*
* Calling Functions : R_MTU2_ControlChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_SetTGR_W_MTU_U0_C5(uint16_t tgr_w_val)
{
	R_MTU2_ControlChannel_structure parameters;

	parameters.control_setting = PDL_NO_DATA;
	parameters.register_selection = PDL_MTU2_REGISTER_TGRW;
	parameters.TCNT_TCNTU_value = PDL_NO_DATA;
	parameters.TGRA_TCNTV_value = PDL_NO_DATA;
	parameters.TGRB_TCNTW_value = PDL_NO_DATA;
	parameters.TGRC_TGRU_value = PDL_NO_DATA;
	parameters.TGRD_TGRV_value = PDL_NO_DATA;
	parameters.TGRE_TGRW_value = tgr_w_val;
	parameters.TGRF_value = PDL_NO_DATA;
	parameters.TADCOBRA_value = PDL_NO_DATA;
	parameters.TADCOBRB_value = PDL_NO_DATA;

	return R_MTU2_ControlChannel(
		5,
		&parameters
	);

}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_GetRequestFlag_MTU_U0_C5(bool * cm_ic_u, bool * cm_ic_v, bool * cm_ic_w)
*
* Function Name: R_PG_Timer_GetRequestFlag_MTU_U0_C5
*
* Description  : MTUの割り込み要求フラグの取得とクリア
*
* Arguments    : bool * cm_ic_u : コンペアマッチ/インプットキャプチャUフラグの格納先
*              : bool * cm_ic_v : コンペアマッチ/インプットキャプチャVフラグの格納先
*              : bool * cm_ic_w : コンペアマッチ/インプットキャプチャWフラグの格納先
*
* Return Value : true  : 取得に成功した場合
*              : false : 取得に失敗した場合
*
* Calling Functions : R_MTU2_ReadChannel
*
* Details      : 詳細についてはリファレンスマニュアルを参照してください。
******************************************************************************/
bool R_PG_Timer_GetRequestFlag_MTU_U0_C5(bool * cm_ic_u, bool * cm_ic_v, bool * cm_ic_w)
{
	uint8_t data;
	bool res;

	res = R_MTU2_ReadChannel(
		5,
		&data,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR,
		PDL_NO_PTR
	);

	if( cm_ic_u ){
		*cm_ic_u = data & 0x01;
	}
	if( cm_ic_v ){
		*cm_ic_v = (data >> 1) & 0x01;
	}
	if( cm_ic_w ){
		*cm_ic_w = (data >> 2) & 0x01;
	}

	return res;
}



