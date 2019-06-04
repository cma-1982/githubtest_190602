/******************************************************************************
* DISCLAIMER
* Please refer to http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_Timer_MTU_U0_C5.h
* Version      : 1.00
* Description  : 
******************************************************************************
* History : 04.06.2019 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

bool R_PG_Timer_Set_MTU_U0_C5(void);
bool R_PG_Timer_StartCount_MTU_U0_C5(void);
bool R_PG_Timer_StartCount_MTU_U0_C5_U(void);
bool R_PG_Timer_StartCount_MTU_U0_C5_V(void);
bool R_PG_Timer_StartCount_MTU_U0_C5_W(void);
bool R_PG_Timer_HaltCount_MTU_U0_C5(void);
bool R_PG_Timer_HaltCount_MTU_U0_C5_U(void);
bool R_PG_Timer_HaltCount_MTU_U0_C5_V(void);
bool R_PG_Timer_HaltCount_MTU_U0_C5_W(void);
bool R_PG_Timer_GetCounterValue_MTU_U0_C5(uint16_t * counter_u_val, uint16_t * counter_v_val, uint16_t * counter_w_val);
bool R_PG_Timer_SetCounterValue_MTU_U0_C5(uint16_t counter_u_val, uint16_t counter_v_val, uint16_t counter_w_val);
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_U(uint16_t counter_u_val);
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_V(uint16_t counter_v_val);
bool R_PG_Timer_SetCounterValue_MTU_U0_C5_W(uint16_t counter_w_val);
bool R_PG_Timer_GetTGR_MTU_U0_C5(uint16_t * tgr_u_val, uint16_t * tgr_v_val, uint16_t * tgr_w_val);
bool R_PG_Timer_SetTGR_U_MTU_U0_C5(uint16_t tgr_u_val);
bool R_PG_Timer_SetTGR_V_MTU_U0_C5(uint16_t tgr_v_val);
bool R_PG_Timer_SetTGR_W_MTU_U0_C5(uint16_t tgr_w_val);
bool R_PG_Timer_GetRequestFlag_MTU_U0_C5(bool * cm_ic_u, bool * cm_ic_v, bool * cm_ic_w);



