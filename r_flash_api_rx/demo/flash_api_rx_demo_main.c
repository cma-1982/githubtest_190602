/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/******************************************************************************
* File Name	   : flash_api_rx600_demo_main.c
* Version	   : 2.20
* Device 	   : RX600 Series, RX200 Series
* Tool-Chain   : RX Family C Compiler
* H/W Platform : RSKRX62N, RSKRX610, YRDKRX62N, RSKRX630, RSKRX63N, RSKRX62T,
*                YRDKRX63N
* Description  : Demo code for using the Simple Flash API for RX. This code will
*                erase and write to all flash blocks except for the ones that
*                are holding this application.
* Operation    : 1. Compile the sample code.
*                2. Download code to the MCU
*                3. Place a breakpoint on the infinite loop at the end of the
*                   main() function. You can also place a breakpoint on the
*                   R_FlashDataAreaAccess() function to stop in between data
*                   flash and ROM operations.
*                4. Click 'Reset Go'.
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 21.12.2009 1.00    First Release
*         : 13.01.2010 1.10    Made function names and variables RAPI compliant
*         : 11.02.2010 1.20    Fixed other RAPI issues and fixed I flag issue
*         : 29.04.2010 1.30    Added support for RX621/N Group. Moved most
*                              device specific data to header file.
*         : 26.05.2010 1.40    Added support for RX62T Group
*         : 28.07.2010 1.41    Fixed bug when performing a blank check on an
*                              entire data flash block.  Also declared 
*                              functions not in the API as 'static'.
*		  : 23.08.2010 1.42    Updated source to raise the coding standard, to
*							   meet GSCE & RSK standards.
*         : 15.02.2011 1.43    Fixed bug in blank check routine when handling
*                              input arguments and moved _Flash_Init() to
*                              _Enter_PE_Mode() function.
*         : 21.04.2011 2.00    Added BGO capabilities for data flash. Made 
*                              some more changes to fit coding standard. Added
*                              ability to do ROM to ROM or DF to DF transfers.
*                              Added the ability to use the lock bit feature
*                              on ROM blocks.  Added BGO capabilities for
*                              ROM operations.
*         : 06.07.2011 2.10    Added support for RX630, RX631, and RX63N.
*                              Also added R_FlashEraseRange() for devices like
*                              RX63x that have finer granularity data flash.
*                              Various bug fixes as well. Example bug fix was
*                              removing DATA_FLASH_OPERATION_PIPL and 
*                              ROM_OPERATION_PIPL #defines since the IPL was
*                              not restored when leaving flash ready interrupt.
*         : 29.11.2011 2.20    Renamed private functions according to new 
*                              Coding Standard. Removed unused 'bytes' argument 
*                              from enter_pe_mode() function. Removed 'far' 
*                              keyword since it is not needed. Fixed where some 
*                              functions were being placed in RAM when this was
*                              not needed. Uses platform.h now instead of 
*                              having multiple iodefine_rxXXX.h's. Added 
*                              __evenaccess directive to FCU accesses. This 
*                              ensures proper bus width accesses. Added
*                              R_FlashCodeCopy() function. When clearing the
*                              FENTRYR register, the register is read back to
*                              ensure its value is 0x0000. Added call to 
*                              exit_pe_mode() when enter_pe_mode() function 
*                              fails to protect against reading ROM in P/E
*                              mode. Added option to use r_bsp package.
*         : 11.09.2012 2.30    Updated to meet FIT v0.7 spec. Now uses r_bsp
*                              locking. Removed FLASH_API_USE_R_BSP macro. Code 
*                              now automatically detects r_bsp. Moved MCU 
*                              specific information into 'ports' folder instead 
*                              of keep on expanding r_flash_api_rx_if.h.
*                              Added R_FlashGetVersion() function. Added 
*                              timeout for while() loop reading back FENTRYR 
*                              value.
*         : 29.11.2012 2.40    Updated to meet FIT v1.0 spec. Added support
*                              for RX62G and RX63T MCU groups. Cleaned up 
*                              code some by removing almost all preprocessor
*                              statements that tested against MCU groups. Now
*                              have 'targets' directory for easier addition
*                              of new MCUs. Updated to use r_bsp v2.00.
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Used for MCU intrinsics (e.g. nop();) */
#include <machine.h>

/* Configuration options for the Flash API. This is also included in 
   r_flash_api_rx.h and would normally not need to be included separately.
   It is included separately here so that the decision can be made to use
   the r_bsp package or not. */
#include "r_flash_api_rx_config.h"
/* Get board and MCU definitions. */
#include "platform.h"

#if !defined(R_BSP_VERSION_MAJOR)
#include "iodefine.h"
#include "mcu_info.h"
#endif

/* Used for Simple Flash API functions */
#include "r_flash_api_rx_if.h"
/* Used for getting flash info for testing. User would typically not need to 
   include this file with their projects. */
#include "r_flash_api_rx_private.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define PROG_SIZE       512
#define BUFF_SIZE       512

/* Amount of ROM that is being saved for code space.
   By default this is 16KB. This means that the top 16KB of ROM will not be 
   erased in this demo. */
#define ROM_RESERVED_BYTES      (16384)

/* If you want to test DF to DF or ROM to ROM transfers then first make sure
   to enable the feature in r_flash_api_rx_config.h by uncommenting the
   #define for 'FLASH_API_RX_CFG_FLASH_TO_FLASH'. */   
   
/* If you want to test DF to DF uncomment this #define */
//#define TEST_DF_TO_DF_TRANSFERS
/* If you want to test ROM to ROM transfers then uncomment this #define */
//#define TEST_ROM_TO_ROM_TRANSFERS

#if (defined(TEST_DF_TO_DF_TRANSFERS) || defined(TEST_ROM_TO_ROM_TRANSFERS)) \
    && !defined(FLASH_API_RX_CFG_FLASH_TO_FLASH)
ERROR!!! - In order to test flash to flash transfers you must first enable
this feature in r_flash_api_rx_config.h by uncommenting the define
for FLASH_API_RX_CFG_FLASH_TO_FLASH.
#endif

/* In your application feel free to enable both ROM to ROM and DF to DF 
   transfers. However, in this sample code there is only one program buffer
   so it cannot be in DF and ROM at the same time. This means that you can
   only test DF to DF or ROM to ROM in one test run. */
#if defined(TEST_DF_TO_DF_TRANSFERS) && defined(TEST_ROM_TO_ROM_TRANSFERS)
ERROR!!! - With this sample code you can only test DF to DF or ROM to ROM
transfers at one time. In your application feel free to use both though.
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
/* If testing DF to DF transfers then put program data in data flash block 0 */
#ifdef TEST_DF_TO_DF_TRANSFERS
#pragma address prog_buff 0x100000
#endif

/* If testing ROM to ROM transfers then put program data in ROM */
#ifdef TEST_ROM_TO_ROM_TRANSFERS
static const uint8_t prog_buff[BUFF_SIZE] = "hello world0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
#else
static uint8_t prog_buff[BUFF_SIZE] = "hello world0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
#endif
static uint8_t read_buff[BUFF_SIZE];
static uint32_t address;

/* Loop variable, put here for ease in use when debugging */
volatile uint32_t g_loop, g_ret;

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO) || defined(FLASH_API_RX_CFG_ROM_BGO)
/* Used to tell application whether previous flash operation has finished */
static uint8_t flash_is_ready;
#endif
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
/* Holds the outcome of the blank check operation */
static uint8_t blank_check_result;
#endif

void main(void);
static void flash_api_demo(void);
static void flash_api_demo_df_tests(void);
static void flash_api_demo_rom_tests(void);

#if !defined(FLASH_API_RX_CFG_IGNORE_LOCK_BITS) 
static void flash_api_demo_lock_bit_tests(void);
#endif
#if defined(FLASH_API_RX_CFG_ROM_BGO)
static void flash_api_demo_rom_bgo_init(void);
#endif

/* If you are testing ROM BGO then this sample code will need to be in RAM.
   The reason for this is that the API calls will be non-blocking so the 
   code will return to here. If the sample code was in ROM then when the
   API code returned it would try to fetch from ROM and would cause a flash
   access error. */
#ifdef FLASH_API_RX_CFG_ROM_BGO

/* We will also need some RAM space to hold the vector table */
static uint32_t ram_vector_table[256];

/* If using ROM BGO then this sample code needs to be in RAM */
#pragma section FRAM
#endif

/******************************************************************************
* Function Name: main
* Description  : Program starts here after Reset and initlization. Runs through
*                all functions of the Flash API.
* Arguments    : none
* Return Value : none
******************************************************************************/
void main (void)
{
#ifdef FLASH_API_RX_CFG_COPY_CODE_BY_API
    /* Before calling any other API functions the API code needs to be 
       copied to RAM. This can still be done the 'old way' by editting dbsct.c
       if desired. */
    R_FlashCodeCopy();
#endif

    /* Run Flash API tests. */
    flash_api_demo();

    while(1)
    {
        /* Infinite Loop */
    }
}

/******************************************************************************
* Function Name: flash_api_demo
* Description  : Runs through all functions of the Flash API.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void flash_api_demo (void)
{       
#ifdef FLASH_API_RX_CFG_ENABLE_ROM_PROGRAMMING
    flash_api_demo_rom_tests();
#endif /* FLASH_API_RX_CFG_ENABLE_ROM_PROGRAMMING */
    
    flash_api_demo_df_tests();    
     
    /*****************************/
    /* Tests are done            */
    /*****************************/    
}

/******************************************************************************
* Function Name: flash_api_demo_rom_tests
* Description  : Tests out the Flash API on the ROM
* Arguments    : none
* Return Value : none
******************************************************************************/
static void flash_api_demo_rom_tests (void)
{
    /* Loop counter. */
    uint32_t i;

#ifdef FLASH_API_RX_CFG_ROM_BGO    
    flash_api_demo_rom_bgo_init();
#endif
    
#if defined(TEST_DF_TO_DF_TRANSFERS)
    /* If we are testing DF to DF transfers then buffer data will be located
       in the DF. DF therefore needs to be enabled before ROM programming. */
    R_FlashDataAreaAccess(0xFFFF, 0xFFFF);
#endif
    
	/*****************************************************************/
	/*                    Write/Erase User Flash                     */
	/*****************************************************************/
    
    /* Test erasing and flashing ROM */
    
    /* Start off by finding first safe block to erase. We do not want to 
       erase the ROM where this application is located. */
    for (g_loop = 0; g_loop < ROM_NUM_BLOCKS; g_loop++)
    {
        /* 0x01000000 is the top of the ROM P/E range. */
        if (g_flash_BlockAddresses[g_loop] < (0x01000000 - ROM_RESERVED_BYTES))
        {
            break;
        }
    }
       
    for(g_loop; g_loop < ROM_NUM_BLOCKS; g_loop++) 
    {
    
        /* Get address for reading */
        address = (0xFF000000 | g_flash_BlockAddresses[g_loop]);

#if defined(FLASH_API_RX_CFG_ROM_BGO)
        /* Flash is ready */
        flash_is_ready = false;
#endif
        
#if (!defined(FLASH_API_RX_CFG_IGNORE_LOCK_BITS)) && (!defined(FLASH_API_RX_CFG_ROM_BGO))
        /* Lock bit tests should be done with ROM BGO disabled. There is
           no problem with using the two together, it would just have made
           the code below more complex. */
        flash_api_demo_lock_bit_tests();        
#else        
    
    	/************************/
    	/* Erase our Flash area */
    	/************************/
    	/* NOTE: You can watch the flash memory erasing/writing with the E1/E20
    	         within HEW if you enable "Debug the program using the CPU 
    	         re-write mode"  in the "System" tab of the 
                 "Configuration Properties" window when connecting */
        g_ret = R_FlashErase(g_loop); 
            
        /* Check for errors */
        if(g_ret != FLASH_SUCCESS)
        {
            while(1)
            {
                /* Error in demo. */
            }
        }    
        
#endif /* (!defined(FLASH_API_RX_CFG_IGNORE_LOCK_BITS)) && (!defined(FLASH_API_RX_CFG_ROM_BGO)) */

#if defined(FLASH_API_RX_CFG_ROM_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );
#endif
            
        /* Read area after erase */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            read_buff[i] = *(uint8_t *)(address + i);
        }
              
        /* Verify it was erased */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            if(read_buff[i] != 0xFF) 
            {
                while(1)
                {
                    /* Error in demo. */
                }
            }
        }
    
    	/*****************************/
    	/* Write our buffer to Flash */
    	/*****************************/
        g_ret = R_FlashWrite(address, (uint32_t)prog_buff, PROG_SIZE);
    
        /* Check for errors */
        if(g_ret != FLASH_SUCCESS) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }
        
#if defined(FLASH_API_RX_CFG_ROM_BGO)
        /* You will notice that here, instead of polling on the variable
           'flash_is_ready' we are polling on the function 
           R_FlashGetStatus() */
        while( R_FlashGetStatus() == FLASH_BUSY );
#endif                        
    
        /* Read back written area */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            read_buff[i] = *(uint8_t *)(address + i);
        }
        
        /* Verify */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            if(read_buff[i] != prog_buff[i]) 
            {
                while(1)
                {
                    /* Error in demo. */
                }
            }            
        }
    }    
}

#if defined(FLASH_API_RX_CFG_ROM_BGO)
/******************************************************************************
* Function Name: flash_api_demo_rom_bgo_init
* Description  : Moves the relocatable vector table to RAM.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void flash_api_demo_rom_bgo_init (void)
{
    /* Will hold INTB */
    uint32_t * flash_vect;

    /* If ROM BGO is used then the variable vector table will need to be 
       relocated to RAM. This code does this. */
    /* Get address of variable vector table in ROM */
    flash_vect = (uint32_t *)get_intb();
    
    /* Copy over variable vector table to RAM */
    for(i = 0; i < 256; i++ )
    {
        /* Copy over entry */
        ram_vector_table[i] = *flash_vect;
        
        /* Move pointer */
        flash_vect += 1;
    }
    
    /* Set INTB to ram address */

    #if __RENESAS_VERSION__ >= 0x01010000
    set_intb((void *)&ram_vector_table[0] );
    #else
    set_intb( (uint32_t)&ram_vector_table[0] );
    #endif            
}
#endif /* FLASH_API_RX_CFG_ROM_BGO */

#if (!defined(FLASH_API_RX_CFG_IGNORE_LOCK_BITS)) && (!defined(FLASH_API_RX_CFG_ROM_BGO))
/******************************************************************************
* Function Name: flash_api_demo_lock_bit_tests
* Description  : Tests out using lock bits with the Flash API. This function
*                will set the lock bits for all of the ROM blocks, test them,
*                and then erase the blocks to clear the lock bit.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void flash_api_demo_lock_bit_tests (void)
{
    /* Enable lock bit protection (this is default out of reset) */
    g_ret = R_FlashSetLockBitProtection(true);

    /* Should turn lock bit protection on */
    while( g_ret != FLASH_SUCCESS );

    /* Program lock bits */        
    g_ret = R_FlashProgramLockBit(g_loop);

    /* Should set lock bit successfully */
    while( g_ret != FLASH_SUCCESS );

    /* Read lock bit */
    g_ret = R_FlashReadLockBit(g_loop);

    /* Should return lock bit is set */
    while( g_ret != FLASH_LOCK_BIT_SET );

    /* Attempt an erase, should fail */
    g_ret = R_FlashErase(g_loop);

    /* Should return failure due to lock bit being set */
    while( g_ret != FLASH_FAILURE );        

    /* Attempt a write, should fail */
    g_ret = R_FlashWrite(address, (uint32_t)prog_buff, PROG_SIZE);

    /* Should return failure due to lock bit being set */
    while( g_ret != FLASH_FAILURE );                

    /* Disable lock bit protection */
    g_ret = R_FlashSetLockBitProtection(false);

    /* Should turn lock bit protection off */
    while( g_ret != FLASH_SUCCESS );

    /* Attempt erase again */
    g_ret = R_FlashErase(g_loop);

    /* Should return that erase was successful */
    while( g_ret != FLASH_SUCCESS );        

    /* Read lock bit */
    g_ret = R_FlashReadLockBit(g_loop);   

    /* Should return lock bit is not set */
    while( g_ret != FLASH_LOCK_BIT_NOT_SET );                    
}
#endif

/******************************************************************************
* Function Name: flash_api_demo_df_tests
* Description  : Tests out the Flash API on the data flash
* Arguments    : none
* Return Value : none
******************************************************************************/
static void flash_api_demo_df_tests (void)
{
    /* Loop counter. */
    uint32_t i;

    /*****************************************************************/
	/*                    Write/Erase Data Flash                     */
	/*****************************************************************/    
    
	/* After Data Flash Area is enabled, you can access Data Flash Memory */
    R_FlashDataAreaAccess(0xFFFF, 0xFFFF);
    
    /* If testing DF to DF transfers then the first DF block is reserved for holding
       the data */
#ifdef TEST_DF_TO_DF_TRANSFERS
    for(g_loop = 1; g_loop < DF_NUM_BLOCKS; g_loop++)
#else    
    for(g_loop = 0; g_loop < DF_NUM_BLOCKS; g_loop++)
#endif
    {
        /* Get beginning address of DF block */
        address = g_flash_BlockAddresses[BLOCK_DB0 + g_loop];
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Flash is ready */
        flash_is_ready = false;
#endif
        
    	/***************************/
    	/* Check if block is blank */
    	/***************************/
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_ENTIRE_BLOCK);
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );

        /* Flash is ready */
        flash_is_ready = false;
#endif
        
    	/************************/
    	/* Erase our Flash area */
    	/************************/
    	/* NOTE: You can watch the flash memory erasing/writing with the E1/E20
    	         within HEW if you enable "Debug the program using the CPU 
    	         re-write mode"  in the "System" tab of the 
                 "Configuration Properties" window when connecting */
        g_ret = R_FlashErase(BLOCK_DB0 + g_loop);
        
        /* Check for errors */
        if(g_ret != FLASH_SUCCESS) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );

        /* Flash is ready */
        flash_is_ready = false;
#endif
                
        /* Check Blank Checking using both methods of input: address and
           block number */
        /* First try with address */           
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_ENTIRE_BLOCK);
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );
        
        /* Copy over blank check result */
        g_ret = blank_check_result;
#endif        
        
        /* Should be FLASH_BLANK since it was just erased */
        if(g_ret != FLASH_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Flash is ready */
        flash_is_ready = false;
#endif        
        
        /* Now use block number */           
        g_ret = R_FlashDataAreaBlankCheck(BLOCK_DB0 + g_loop, BLANK_CHECK_ENTIRE_BLOCK);

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );
        
        /* Copy over blank check result */
        g_ret = blank_check_result;
#endif        
        
        /* Should be FLASH_BLANK since it was just erased */
        if(g_ret != FLASH_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }        

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Flash is ready */
        flash_is_ready = false;
#endif        
        
    	/*****************************/
    	/* Write our buffer to Flash */
    	/*****************************/
        g_ret = R_FlashWrite( address, (uint32_t)prog_buff, sizeof(read_buff));
        
        /* Check for errors */
        if(g_ret != FLASH_SUCCESS) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for flash operation to finish. In a real application we
           could go off and do real work. */
        while( flash_is_ready == false );
#endif        
        
        
        /* Should return error because not multiple of the programming size */
        g_ret = R_FlashWrite( address, (uint32_t)prog_buff, 15);
        
        /* Check for absence of errors */
        if(g_ret == FLASH_SUCCESS) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* You will notice that here, instead of polling on the variable
           'flash_is_ready' we are polling on the function 
           R_FlashGetStatus() */
        while( R_FlashGetStatus() == FLASH_BUSY );
#endif                
        
        /* Clear ret */
        g_ret = 0;
        
        /* Read back written area */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            read_buff[i] = *(uint8_t *)(address + i);
        }
        
        /* Verify */
        for(i = 0; i < sizeof(read_buff); i++) 
        {
            if(read_buff[i] != prog_buff[i]) 
            {
                while(1)
                {
                    /* Error in demo. */
                }
            }            
        }                
        
    	/******************************************************************/
    	/* More Blank Check tests, use debugger to see returned values    */
    	/******************************************************************/                
        /* Check Blank Checking using both methods of input: address and
           block number */
        /* First try with address */           
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_ENTIRE_BLOCK);  
        
#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* You will notice that here, instead of polling on the variable
           'flash_is_ready' we are polling on the function 
           R_FlashGetStatus() */
        while( R_FlashGetStatus() == FLASH_BUSY );
        
        /* Copy over blank check result */
        g_ret = blank_check_result;
#endif                
        
        
        /* Should return FLASH_NOT_BLANK (not blank) */
        if(g_ret != FLASH_NOT_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }
        
        /* Now use block number */           
        g_ret = R_FlashDataAreaBlankCheck(BLOCK_DB0 + g_loop, BLANK_CHECK_ENTIRE_BLOCK);

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* You will notice that here, instead of polling on the variable
           'flash_is_ready' we are polling on the function 
           R_FlashGetStatus() */
        while( R_FlashGetStatus() == FLASH_BUSY );
        
        /* Copy over blank check result */
        g_ret = blank_check_result;
#endif                
        
        /* Should return FLASH_NOT_BLANK (not blank) */
        if(g_ret != FLASH_NOT_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }        
                      
        /* Should return FLASH_NOT_BLANK (not blank) */
        /* Perform blank check on newly erased area. Smaller blank check
           does not use BGO so return is the correct result. */        
#if   defined(BLANK_CHECK_8_BYTE)
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_8_BYTE);
#elif defined(BLANK_CHECK_2_BYTE)
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_2_BYTE);
#endif        

        /* Should return FLASH_NOT_BLANK (blank) */
        if(g_ret != FLASH_NOT_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }                
                                        
        /* Should return FLASH_BLANK (blank) */
#if   defined(BLANK_CHECK_8_BYTE)
        g_ret = R_FlashDataAreaBlankCheck(address + sizeof(read_buff), BLANK_CHECK_8_BYTE);
#elif defined(BLANK_CHECK_2_BYTE)
        g_ret = R_FlashDataAreaBlankCheck(address + sizeof(read_buff), BLANK_CHECK_2_BYTE);
#endif        

        /* Should return FLASH_BLANK (blank) */
        if(g_ret != FLASH_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }                

#if defined(DF_GROUPED_BLOCKS)
        /* Test the erasing a range of data flash addresses if supported by MCU */
        g_ret = R_FlashEraseRange(address, DF_ERASE_BLOCK_SIZE*2);

        /* Check for errors */
        if(g_ret != FLASH_SUCCESS) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }    

        #if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)
        /* Wait for operation to finish */
        while( R_FlashGetStatus() == FLASH_BUSY );                    
        #endif             
    
        /* Perform blank check on newly erased area. Smaller blank check
           does not use BGO so return is the correct result. */
        g_ret = R_FlashDataAreaBlankCheck(address, BLANK_CHECK_2_BYTE);

        /* Should be FLASH_BLANK since it was just erased */
        if(g_ret != FLASH_BLANK) 
        {
            while(1)
            {
                /* Error in demo. */
            }
        }                                                               
#endif         
    } 
}
/******************************************************************************
End of function  flash_api_demo_df_tests
******************************************************************************/

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO)

/******************************************************************************
* Function Name: FlashBlankCheckDone
* Description  : Callback function for when blank check operation has finished
* Arguments    : result - FLASH_BLANK if block was blank
*                         FLASH_NOT_BLANK if block was not blank
* Return Value : none
******************************************************************************/
void FlashBlankCheckDone(uint8_t result)
{
    /* Copy result of blank check */
    blank_check_result = result;
    
    /* Signal flash operation is done */
    flash_is_ready = true;
}
/******************************************************************************
End of function  FlashBlankCheckDone
******************************************************************************/

#endif /* defined(FLASH_API_RX_CFG_DATA_FLASH_BGO) */

#if defined(FLASH_API_RX_CFG_DATA_FLASH_BGO) || defined(FLASH_API_RX_CFG_ROM_BGO)

/******************************************************************************
* Function Name: FlashEraseDone
* Description  : Callback function for when blank check operation has finished
* Arguments    : none
* Return Value : none
******************************************************************************/
void FlashEraseDone(void)
{
    /* Signal flash operation is done */
    flash_is_ready = true;
}
/******************************************************************************
End of function  FlashEraseDone
******************************************************************************/

/******************************************************************************
* Function Name: FlashWriteDone
* Description  : Callback function for when blank check operation has finished
* Arguments    : none
* Return Value : none
******************************************************************************/
void FlashWriteDone(void)
{
    /* Signal flash operation is done */
    flash_is_ready = true;
}
/******************************************************************************
End of function  FlashWriteDone
******************************************************************************/

/******************************************************************************
* Function Name: FlashError
* Description  : Callback function for when blank check operation has finished
* Arguments    : none
* Return Value : none
******************************************************************************/
void FlashError(void)
{
    /* Alert program or user that flash error has occurred */
    while(1)
    {
        /* Error in demo. */
    }
}
/******************************************************************************
End of function  FlashError
******************************************************************************/

#endif /* defined(FLASH_API_RX_CFG_DATA_FLASH_BGO) || defined(FLASH_API_RX_CFG_ROM_BGO) */

