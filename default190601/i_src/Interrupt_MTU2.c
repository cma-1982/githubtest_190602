/*""FILE COMMENT""*************************************************************
* System Name	: Interrupt program for RX63Nxx
* File Name		: Interrupt_MTU2.c
* Version		: 1.21
* Contents		: Interrupt handlers for the MTU channels.
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 1. Some interrupt vectors are shared with the TPU. The
*				: handlers for these can be found in file Interrupt_MTU_TPU.c.
*			    : 2. Some MTU interrupts are group interrupts. The handlers for
*				: these can be found in file Interrupt_INTC.c.
*******************************************************************************
* Copyright, 2014. Renesas Electronics Corporation and Renesas Solutions Corp.
*******************************************************************************
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FILE COMMENT END""*********************************************************/

#include "r_pdl_mtu2.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"


/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGICn(void)
*------------------------------------------------------------------------------
* Function		: TGICn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_func3_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU4_TGIC4
#pragma interrupt Interrupt_MTU4_TGIC4(vect=VECT_MTU4_TGIC4, fint)
#else
#pragma interrupt Interrupt_MTU4_TGIC4(vect=VECT_MTU4_TGIC4)
#endif
void Interrupt_MTU4_TGIC4(void)
{
	/* Call the user function */
	if (rpdl_MTU2_func3_callback_func[4] != PDL_NO_FUNC)
	{
		rpdl_MTU2_func3_callback_func[4]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIDn(void)
*------------------------------------------------------------------------------
* Function		: TGIDn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_func4_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU4_TGID4
#pragma interrupt Interrupt_MTU4_TGID4(vect=VECT_MTU4_TGID4, fint)
#else
#pragma interrupt Interrupt_MTU4_TGID4(vect=VECT_MTU4_TGID4)
#endif
void Interrupt_MTU4_TGID4(void)
{
	/* Call the user function */
	if (rpdl_MTU2_func4_callback_func[4] != PDL_NO_FUNC)
	{
		rpdl_MTU2_func4_callback_func[4]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIEn(void)
*------------------------------------------------------------------------------
* Function		: TGIEn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_TGRE_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU0_TGIE0
#pragma interrupt Interrupt_MTU0_TGIE0(vect=VECT_MTU0_TGIE0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGIE0(vect=VECT_MTU0_TGIE0)
#endif
void Interrupt_MTU0_TGIE0(void)
{
	/* Call the user function */
	if (rpdl_MTU2_TGRE_callback_func[0] != PDL_NO_FUNC)
	{
		rpdl_MTU2_TGRE_callback_func[0]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIFn(void)
*------------------------------------------------------------------------------
* Function		: TGIFn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_TGRF_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU0_TGIF0
#pragma interrupt Interrupt_MTU0_TGIF0(vect=VECT_MTU0_TGIF0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGIF0(vect=VECT_MTU0_TGIF0)
#endif
void Interrupt_MTU0_TGIF0(void)
{
	/* Call the user function */
	if (rpdl_MTU2_TGRF_callback_func[0] != PDL_NO_FUNC)
	{
		rpdl_MTU2_TGRF_callback_func[0]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TCIVn(void)
*------------------------------------------------------------------------------
* Function		: TCIVn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_Overflow_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/
#if FAST_INTC_VECTOR == VECT_MTU4_TCIV4
#pragma interrupt Interrupt_MTU4_TCIV4(vect=VECT_MTU4_TCIV4, fint)
#else
#pragma interrupt Interrupt_MTU4_TCIV4(vect=VECT_MTU4_TCIV4)
#endif
void Interrupt_MTU4_TCIV4(void)
{
	/* Call the user function */
	if (rpdl_MTU2_Overflow_callback_func[4] != PDL_NO_FUNC)
	{
		rpdl_MTU2_Overflow_callback_func[4]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIUn(void)
*------------------------------------------------------------------------------
* Function		: TGIUn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_func1_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU5_TGIU5
#pragma interrupt Interrupt_MTU5_TGIU5(vect=VECT_MTU5_TGIU5, fint)
#else
#pragma interrupt Interrupt_MTU5_TGIU5(vect=VECT_MTU5_TGIU5)
#endif
void Interrupt_MTU5_TGIU5(void)
{
	/* Call the user function */
	if (rpdl_MTU2_func1_callback_func[5] != PDL_NO_FUNC)
	{
		rpdl_MTU2_func1_callback_func[5]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIVn(void)
*------------------------------------------------------------------------------
* Function		: TGIVn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_func2_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU5_TGIV5
#pragma interrupt Interrupt_MTU5_TGIV5(vect=VECT_MTU5_TGIV5, fint)
#else
#pragma interrupt Interrupt_MTU5_TGIV5(vect=VECT_MTU5_TGIV5)
#endif
void Interrupt_MTU5_TGIV5(void)
{
	/* Call the user function */
	if (rpdl_MTU2_func2_callback_func[5] != PDL_NO_FUNC)
	{
		rpdl_MTU2_func2_callback_func[5]();
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIWn(void)
*------------------------------------------------------------------------------
* Function		: TGIWn interrupt processing
*------------------------------------------------------------------------------
* Argument		: Nothing
*------------------------------------------------------------------------------
* Return value	: Nothing
*------------------------------------------------------------------------------
* Input			: 
* Output		: 
*------------------------------------------------------------------------------
* Use function	: rpdl_MTU2_func3_callback_func[n]
*------------------------------------------------------------------------------
* Notes			: 
*------------------------------------------------------------------------------
* History		: 2014.04.04
*				: Ver 1.21
*				: CS release
*""FUNC COMMENT END""*********************************************************/

#if FAST_INTC_VECTOR == VECT_MTU5_TGIW5
#pragma interrupt Interrupt_MTU5_TGIW5(vect=VECT_MTU5_TGIW5, fint)
#else
#pragma interrupt Interrupt_MTU5_TGIW5(vect=VECT_MTU5_TGIW5)
#endif
void Interrupt_MTU5_TGIW5(void)
{
	/* Call the user function */
	if (rpdl_MTU2_func3_callback_func[5] != PDL_NO_FUNC)
	{
		rpdl_MTU2_func3_callback_func[5]();
	}
}

/* End of file */
