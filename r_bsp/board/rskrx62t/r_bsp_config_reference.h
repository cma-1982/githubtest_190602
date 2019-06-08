/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_config_reference.h
* Device(s)    : RX62T
* Description  : The file r_bsp_config.h is used to configure your BSP. r_bsp_config.h should be included
*                somewhere in your package so that the r_bsp code has access to it. This file (r_bsp_config_reference.h)
*                is just a reference file that the user can use to make their own r_bsp_config.h file.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 12.03.2012 1.00    First Release        
*         : 03.05.2012 1.10    Added BSP_CFG_USER_BOOT_ENABLE option.
*         : 26.06.2012 1.15    Added MCU product part number section. Added option for ROM Code Protect. Added callback 
*                              function options for exception interrupts.
*         : 16.07.2012 1.20    Fixed bug with exception callback function names.
*                              macro options.
*         : 09.08.2012 1.30    Added BSP_CFG_IO_LIB_ENABLE macro.
*         : 20.09.2012 1.40    Added BSP_CFG_USER_LOCKING_ENABLED and BSP_CFG_USER_LOCKING_TYPE macros.
*         : 19.11.2012 1.50    Updated code to use 'BSP_' and 'BSP_CFG_' prefix for macros.
*         : 17.01.2013 1.60    Moved BSP_CFG_IO_LIB_ENABLE macro since it is now used in conjunction with 
*                              BSP_CFG_HEAP_BYTES. Added comments for disabling heap above BSP_CFG_HEAP_BYTES. 
*                              Added BSP_CFG_PARAM_CHECKING_ENABLE macro for configuring global parameter checking.
***********************************************************************************************************************/
#ifndef R_BSP_CONFIG_REF_HEADER_FILE
#define R_BSP_CONFIG_REF_HEADER_FILE

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
/* Enter the product part number for your MCU. This information will be used to obtain information about your MCU such 
   as package and memory size. 
   To help parse this information, the part number will be defined using multiple macros.
   R 5 F 56 2T A B D FH
   | | | |  |  | | | |  Macro Name              Description
   | | | |  |  | | | |__BSP_CFG_MCU_PART_PACKAGE      = Package type, number of pins, and pin pitch
   | | | |  |  | | |____not used                      = Products with wide temperature range
   | | | |  |  | |______BSP_CFG_MCU_PART_CAN_INCLUDED = CAN included/not included
   | | | |  |  |________BSP_CFG_MCU_PART_MEMORY_SIZE  = ROM, RAM, and Data Flash Capacity
   | | | |  |___________BSP_CFG_MCU_PART_GROUP        = Group name  
   | | | |______________BSP_CFG_MCU_PART_SERIES       = Series name
   | | |________________BSP_CFG_MCU_PART_MEMORY_TYPE  = Type of memory (Flash, ROMless)
   | |__________________not used                      = Renesas MCU
   |____________________not used                      = Renesas semiconductor product. 
   */

/* Package type. Set the macro definition based on values below:
   Character(s) = Value for macro = Package Type/Number of Pins/Pin Pitch
   FH           = 0x0             = LQFP/112/0.65
   FP           = 0x1             = LQFP/100/0.50
   FF           = 0x2             = LQFP/80/0.65
   FM           = 0x3             = LQFP/64/0.50
*/
#define BSP_CFG_MCU_PART_PACKAGE        (0x1)

/* Whether CAN is included or not. 
   Character(s) = Value for macro = Description
   A            = true            = 5V MCU, CAN x 1 channel
   B            = true            = 3V MCU, CAN x 1 channel
   C            = false           = 5V MCU, No CAN
   D            = false           = 3V MCU, No CAN
*/
#define BSP_CFG_MCU_PART_CAN_INCLUDED   (true)

/* ROM, RAM, and Data Flash Capacity. 
   Character(s) = Value for macro = ROM Size/Ram Size/Data Flash Size
   A            = 0xA             = 256KB/16KB/32KB
   7            = 0x7             = 128KB/8KB/8KB
   6            = 0x6             = 64KB/8KB/8KB
*/
#define BSP_CFG_MCU_PART_MEMORY_SIZE    (0xA)

/* Group name. 
   Character(s) = Value for macro = Description
   2T           = 0x0             = RX62T Group
*/
#define BSP_CFG_MCU_PART_GROUP          (0x0)

/* Series name. 
   Character(s) = Value for macro = Description
   56           = 0x0             = RX600 Series
*/  
#define BSP_CFG_MCU_PART_SERIES         (0x0)

/* Memory type. 
   Character(s) = Value for macro = Description
   F            = 0x0             = Flash memory version
*/
#define BSP_CFG_MCU_PART_MEMORY_TYPE    (0x0)

/* The 'BSP_DECLARE_STACK' macro is checked so that the stack is only declared in one place (resetprg.c). Every time a 
   '#pragma stacksize' is encountered, the stack size is increased. This prevents multiplication of stack size. */
#if defined(BSP_DECLARE_STACK)
/* User Stack size in bytes. The Renesas RX toolchain sets the stack size using the #pragma stacksize directive. */
#pragma stacksize su=0x400
/* Interrupt Stack size in bytes. The Renesas RX toolchain sets the stack size using the #pragma stacksize directive. */
#pragma stacksize si=0x400
#endif

/* Heap size in bytes.
   To disable the heap you must follow these steps:
   1) Set this macro (BSP_CFG_HEAP_BYTES) to 0.
   2) Set the macro BSP_CFG_IO_LIB_ENABLE to 0.
   3) Disable stdio from being built into the project library. This is done by going into the Renesas RX Toolchain 
      settings and choosing the Standard Library section. After that choose 'Standard Library' for Category in HEW or 
      choose 'Contents' in E2Studio. This will present a list of modules that can be included. Uncheck the box for
      stdio.h. 
*/
#define BSP_CFG_HEAP_BYTES              (0x400)

/* Initializes C input & output library functions.
   0 = Disable I/O library initialization in resetprg.c. If you are not using stdio then use this value.
   1 = Enable I/O library initialization in resetprg.c. This is default and needed if you are using stdio. */
#define BSP_CFG_IO_LIB_ENABLE           (1)

/* After reset MCU will operate in Supervisor mode. To switch to User mode, set this macro to '1'. For more information
   on the differences between these 2 modes see the CPU >> Processor Mode section of your MCU's hardware manual.
   0 = Stay in Supervisor mode.
   1 = Switch to User mode.
*/
#define BSP_CFG_RUN_IN_USER_MODE        (0)

/* When using User Boot Mode the reset vector is fetched from a different address than Single-Chip Mode. This option
   puts the reset address in the User Boot Reset Vector so that it will be fetched correctly. The user is still 
   responsible for setting the MCU pins appropriately. If User Boot is selected then the user should make sure that 
   they setup a constant data section in their linker named 'UBSETTINGS' at address 0xFF7FFFFC. 
   0 = Single-Chip or USB Boot Mode (Nothing is placed in User Boot Reset Vector address)
   1 = User Boot Mode
*/
#define BSP_CFG_USER_BOOT_ENABLE        (0)

/* Set your desired ID code. NOTE, leave at the default (all 0xFF's) if you do not wish to use an ID code. If you set 
   this value and program it into the MCU then you will need to remember the ID code because the debugger will ask for 
   it when trying to connect. Note that the E1/E20 will ignore the ID code when programming the MCU during debugging.
   If you set this value and then forget it then you can clear the ID code by connecting up in serial boot mode using 
   FDT. The ID Code is 16 bytes long. The macro below define the ID Code in 4-byte sections. */
/* Lowest 4-byte section, address 0xFFFFFFA0. From MSB to LSB: Control Code, ID code 1, ID code 2, ID code 3. */
#define BSP_CFG_ID_CODE_LONG_1          (0xFFFFFFFF)
/* 2nd ID Code section, address 0xFFFFFFA4. From MSB to LSB: ID code 4, ID code 5, ID code 6, ID code 7. */
#define BSP_CFG_ID_CODE_LONG_2          (0xFFFFFFFF)
/* 3rd ID Code section, address 0xFFFFFFA8. From MSB to LSB: ID code 8, ID code 9, ID code 10, ID code 11. */
#define BSP_CFG_ID_CODE_LONG_3          (0xFFFFFFFF)
/* 4th ID Code section, address 0xFFFFFFAC. From MSB to LSB: ID code 12, ID code 13, ID code 14, ID code 15. */
#define BSP_CFG_ID_CODE_LONG_4          (0xFFFFFFFF)

/* Clock configuration options.
   The input clock frequency is specified and then the system clocks are set by specifying the multipliers used. The
   multiplier settings are used to set the clock registers in resetprg.c. If a 12M.5Hz clock is used and the 
   ICLK is 100MHz, PCLK is 50MHz, and BCLK is 12.5MHz then the settings would be:
   BSP_CFG_XTAL_HZ = 12500000
   BSP_CFG_ICK_MUL = 8       : (BSP_CFG_XTAL_HZ * BSP_CFG_ICK_MUL) = 100MHz
   BSP_CFG_PCK_MUL = 4       : (BSP_CFG_XTAL_HZ * BSP_CFG_PCK_MUL) = 50MHz
   BSP_CFG_BCK_MUL = 1       : (BSP_CFG_XTAL_HZ * BSP_CFG_BCK_MUL) = 12.5MHz
*/
/* XTAL - Input clock frequency in Hz */
#define BSP_CFG_XTAL_HZ                 (12500000)
/* System Clock Multiplier (ICK).
   Available Multipliers: x1, x2, x4, x8. */
#define BSP_CFG_ICK_MUL                 (8)
/* Peripheral Clock Multiplier (PCK).
   Available Multipliers: x1, x2, x4. */
#define BSP_CFG_PCK_MUL                 (4)

/* Below are callback functions that can be used for detecting MCU exceptions, undefined interrupt sources, and 
   bus errors. If the user wishes to be alerted of these events then they will need to define the macro as a 
   function to be called when the event occurs. For example, if the user wanted the function 
   excep_undefined_instr_isr() to be called when an undefined interrupt source ISR is triggered then they would
   do the following:
   #define BSP_CFG_UNDEFINED_INT_ISR_CALLBACK   undefined_interrupt_cb
   If the user does not wish to be alerted of these events then they should comment out the macros.
   
   NOTE: When a callback function is called it will be called from within a ISR. This means that the function
         will essentially be an interrupt and will hold off other interrupts that occur in the system while it
         is executing. For this reason, it is recommended to keep these callback functions short as to not
         decrease the real-time response of your system.
*/
/* Callback for Supervisor Instruction Violation Exception. */
//#define BSP_CFG_EXCEP_SUPERVISOR_ISR_CALLBACK           supervisor_instr_cb

/* Callback for Undefined Instruction Exception. */
//#define BSP_CFG_EXCEP_UNDEFINED_INSTR_ISR_CALLBACK      undefined_instr_cb

/* Callback for Floating Point Exception. */
//#define BSP_CFG_EXCEP_FPU_ISR_CALLBACK                  floating_point_cb

/* Callback for Non-maskable Interrupt. */
//#define BSP_CFG_NMI_ISR_CALLBACK                        nmi_cb

/* Callback for all undefined interrupt vectors. User can set a breakpoint in this function to determine which source
   is creating unwanted interrupts. */
//#define BSP_CFG_UNDEFINED_INT_ISR_CALLBACK              undefined_interrupt_cb

/* Callback for Bus Error Interrupt. */
//#define BSP_CFG_BUS_ERROR_ISR_CALLBACK                  bus_error_cb

/* ROM Code Protection is a feature that can prohibit PROM programmers from reading or writing flash memory.
   There are 3 different options that can be chosen:
   0    = ROM code protection 1 = Both reading and writing to the user area and user boot area are prohibited.
   1    = ROM code protection 2 = Reading from the user area and user boot area are prohibited.
   Else = Protection disabled   = Reading and writing are allowed.
*/
#define BSP_CFG_ROM_CODE_PROTECT_VALUE  (0xFFFFFFFF)

/* This macro lets other modules no if a RTOS is being used.
   0 = RTOS is not used. 
   1 = RTOS is used.
*/
#define BSP_CFG_RTOS_USED               (0)

/* By default modules will use global locks found in mcu_locks.c. If the user is using a RTOS and would rather use its
   locking mechanisms then they can change this macro. 
   NOTE: If '1' is chosen for this macro then the user must also change the next macro 'BSP_CFG_USER_LOCKING_TYPE'.
   0 = Use default locking (non-RTOS)
   1 = Use user defined locking mechanism. 
*/
#define BSP_CFG_USER_LOCKING_ENABLED    (0)

/* If the user decides to use their own locking mechanism with FIT modules then they will need to redefine the typedef
   that is used for the locks. If the user is using a RTOS then they would likely redefine the typedef to be 
   a semaphore/mutex type of their RTOS. Use the macro below to set the type that will be used for the locks. 
   NOTE: If BSP_CFG_USER_LOCKING_ENABLED == 0 then this typedef is ignored.
   NOTE: Do not surround the type with parentheses '(' ')'.
*/
#define BSP_CFG_USER_LOCKING_TYPE       bsp_lock_t

/* If the user decides to use their own locking mechanism with FIT modules then they will need to define the functions
   that will handle the locking and unlocking. These functions should be defined below. 
   If BSP_CFG_USER_LOCKING_ENABLED is != 0:
   R_BSP_HardwareLock(mcu_lock_t hw_index) will call BSP_CFG_USER_LOCKING_HW_LOCK_FUNCTION(mcu_lock_t hw_index)
   R_BSP_HardwareUnlock(mcu_lock_t hw_index) will call BSP_CFG_USER_LOCKING_HW_UNLOCK_FUNCTION(mcu_lock_t hw_index)
       NOTE:With these functions the index into the array holding the global hardware locks is passed as the parameter.
   R_BSP_SoftwareLock(BSP_CFG_USER_LOCKING_TYPE * plock) will call 
   BSP_CFG_USER_LOCKING_SW_LOCK_FUNCTION(BSP_CFG_USER_LOCKING_TYPE * plock)
   R_BSP_SoftwareUnlock(BSP_CFG_USER_LOCKING_TYPE * plock) will call 
   BSP_CFG_USER_LOCKING_SW_UNLOCK_FUNCTION(BSP_CFG_USER_LOCKING_TYPE * plock)
       NOTE:With these functions the actual address of the lock to use is passed as the parameter.   
   NOTE: These functions must return a boolean. If lock was obtained or released successfully then return true. Else, 
         return false. 
   NOTE: If BSP_CFG_USER_LOCKING_ENABLED == 0 then this typedef is ignored.
   NOTE: Do not surround the type with parentheses '(' ')'.
*/
#define BSP_CFG_USER_LOCKING_HW_LOCK_FUNCTION      my_hw_locking_function
#define BSP_CFG_USER_LOCKING_HW_UNLOCK_FUNCTION    my_hw_unlocking_function
#define BSP_CFG_USER_LOCKING_SW_LOCK_FUNCTION      my_sw_locking_function
#define BSP_CFG_USER_LOCKING_SW_UNLOCK_FUNCTION    my_sw_unlocking_function

/* By default FIT modules will check input parameters to be valid. This is helpful during development but some users
   will want to disable this for production code. The reason for this would be to save execution time and code space. 
   This macro is a global setting for enabling or disabling parameter checking. Each FIT module will also have its
   own local macro for this same purpose. By default the local macros will take the global value from here though
   they can be overridden. Therefore, the local setting has priority over this global setting. Disabling parameter
   checking should only used when inputs are known to be good and the increase in speed or decrease in code space is 
   needed. 
   0 = Global setting for parameter checking is disabled. 
   1 = Global setting for parameter checking is enabled (Default).
*/
#define BSP_CFG_PARAM_CHECKING_ENABLE               (1)

#endif /* R_BSP_CONFIG_REF_HEADER_FILE */



