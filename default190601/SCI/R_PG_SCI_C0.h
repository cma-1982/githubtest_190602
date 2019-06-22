/******************************************************************************
* DISCLAIMER
* Please refer to http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010-2013 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_SCI_C0.h
* Version      : 1.00
* Description  : 
******************************************************************************
* History : 22.06.2019 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

bool R_PG_SCI_Set_C0(void);
bool R_PG_SCI_I2CMode_Send_C0(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_SCI_I2CMode_SendWithoutStop_C0(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_SCI_I2CMode_GenerateStopCondition_C0(void);
bool R_PG_SCI_GetSentDataCount_C0(uint16_t * count);
bool R_PG_SCI_I2CMode_Receive_C0(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_SCI_I2CMode_RestartReceive_C0(bool addr_10bit, uint16_t slave, uint8_t * data, uint16_t count);
bool R_PG_SCI_GetReceivedDataCount_C0(uint16_t * count);
bool R_PG_SCI_I2CMode_GetEvent_C0(bool * nack);
bool R_PG_SCI_StopModule_C0(void);



