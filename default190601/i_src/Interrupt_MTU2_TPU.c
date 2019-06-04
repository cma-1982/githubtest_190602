/*""FILE COMMENT""*************************************************************
* System Name	: Interrupt program for RX63Nxx
* File Name		: Interrupt_MTU2.c
* Version		: 1.21
* Contents		: Interrupt handlers for when the MTU and TPU share a vector.
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 
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
* Declaration	: void Interrupt_MTUn_TGIA0(void)
*------------------------------------------------------------------------------
* Function		: TGIAn interrupt processing
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

#if FAST_INTC_VECTOR == VECT_MTU0_TGIA0
#pragma interrupt Interrupt_MTU0_TGIA0_and_TPU6_TGI6A(vect=VECT_MTU0_TGIA0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGIA0_and_TPU6_TGI6A(vect=VECT_MTU0_TGIA0)
#endif
void Interrupt_MTU0_TGIA0_and_TPU6_TGI6A(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN0)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func1_callback_func[0] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func1_callback_func[0]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
		/* Call the user function */
		if (rpdl_TPU_TGRA_callback_func[6] != PDL_NO_FUNC)
		{
			rpdl_TPU_TGRA_callback_func[6]();
		}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU1_TGIA1
#pragma interrupt Interrupt_MTU1_TGIA1_and_TPU7_TGI7A(vect=VECT_MTU1_TGIA1, fint)
#else
#pragma interrupt Interrupt_MTU1_TGIA1_and_TPU7_TGI7A(vect=VECT_MTU1_TGIA1)
#endif
void Interrupt_MTU1_TGIA1_and_TPU7_TGI7A(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN1)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func1_callback_func[1] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func1_callback_func[1]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
		/* Call the user function */
		if (rpdl_TPU_TGRA_callback_func[7] != PDL_NO_FUNC)
		{
			rpdl_TPU_TGRA_callback_func[7]();
		}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU2_TGIA2
#pragma interrupt Interrupt_MTU2_TGIA2_and_TPU8_TGI8A(vect=VECT_MTU2_TGIA2, fint)
#else
#pragma interrupt Interrupt_MTU2_TGIA2_and_TPU8_TGI8A(vect=VECT_MTU2_TGIA2)
#endif
void Interrupt_MTU2_TGIA2_and_TPU8_TGI8A(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN2)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func1_callback_func[2] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func1_callback_func[2]();
		}
	}
	else
	{
		/* TPU */	
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
		/* Call the user function */
		if (rpdl_TPU_TGRA_callback_func[8] != PDL_NO_FUNC)
		{
			rpdl_TPU_TGRA_callback_func[8]();
		}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU3_TGIA3
#pragma interrupt Interrupt_MTU3_TGIA3_and_TPU9_TGI9A(vect=VECT_MTU3_TGIA3, fint)
#else
#pragma interrupt Interrupt_MTU3_TGIA3_and_TPU9_TGI9A(vect=VECT_MTU3_TGIA3)
#endif
void Interrupt_MTU3_TGIA3_and_TPU9_TGI9A(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN3)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func1_callback_func[3] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func1_callback_func[3]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
		/* Call the user function */
		if (rpdl_TPU_TGRA_callback_func[9] != PDL_NO_FUNC)
		{
			rpdl_TPU_TGRA_callback_func[9]();
		}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU4_TGIA4
#pragma interrupt Interrupt_MTU4_TGIA4_and_TPU10_TGI10A(vect=VECT_MTU4_TGIA4, fint)
#else
#pragma interrupt Interrupt_MTU4_TGIA4_and_TPU10_TGI10A(vect=VECT_MTU4_TGIA4)
#endif
void Interrupt_MTU4_TGIA4_and_TPU10_TGI10A(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN4)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func1_callback_func[4] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func1_callback_func[4]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
		/* Call the user function */
		if (rpdl_TPU_TGRA_callback_func[10] != PDL_NO_FUNC)
		{
			rpdl_TPU_TGRA_callback_func[10]();
		}
#endif
	}
}

/*""FUNC COMMENT""*************************************************************
* Module outline: Timer interrupt processing
*------------------------------------------------------------------------------
* Declaration	: void Interrupt_MTUn_TGIBn(void)
*------------------------------------------------------------------------------
* Function		: TGIBn interrupt processing
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

#if FAST_INTC_VECTOR == VECT_MTU0_TGIB0
#pragma interrupt Interrupt_MTU0_TGIB0a_and_TPU6_TGI6B(vect=VECT_MTU0_TGIB0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGIB0a_and_TPU6_TGI6B(vect=VECT_MTU0_TGIB0)
#endif
void Interrupt_MTU0_TGIB0a_and_TPU6_TGI6B(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN0)
	{
		/* MTU */		
		/* Call the user function */
		if (rpdl_MTU2_func2_callback_func[0] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func2_callback_func[0]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRB_callback_func[6] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRB_callback_func[6]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU1_TGIB1
#pragma interrupt Interrupt_MTU1_TGIB1_and_TPU7_TGI7B(vect=VECT_MTU1_TGIB1, fint)
#else
#pragma interrupt Interrupt_MTU1_TGIB1_and_TPU7_TGI7B(vect=VECT_MTU1_TGIB1)
#endif
void Interrupt_MTU1_TGIB1_and_TPU7_TGI7B(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN1)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func2_callback_func[1] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func2_callback_func[1]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRB_callback_func[7] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRB_callback_func[7]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU2_TGIB2
#pragma interrupt Interrupt_MTU2_TGIB2_and_TPU8_TGI8B(vect=VECT_MTU2_TGIB2, fint)
#else
#pragma interrupt Interrupt_MTU2_TGIB2_and_TPU8_TGI8B(vect=VECT_MTU2_TGIB2)
#endif
void Interrupt_MTU2_TGIB2_and_TPU8_TGI8B(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN2)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func2_callback_func[2] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func2_callback_func[2]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRB_callback_func[8] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRB_callback_func[8]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU3_TGIB3
#pragma interrupt Interrupt_MTU3_TGIB3_and_TPU9_TGI9B(vect=VECT_MTU3_TGIB3, fint)
#else
#pragma interrupt Interrupt_MTU3_TGIB3_and_TPU9_TGI9B(vect=VECT_MTU3_TGIB3)
#endif
void Interrupt_MTU3_TGIB3_and_TPU9_TGI9B(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN3)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func2_callback_func[3] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func2_callback_func[3]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRB_callback_func[9] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRB_callback_func[9]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU4_TGIB4
#pragma interrupt Interrupt_MTU4_TGIB4_and_TPU10_TGI10B(vect=VECT_MTU4_TGIB4, fint)
#else
#pragma interrupt Interrupt_MTU4_TGIB4_and_TPU10_TGI10B(vect=VECT_MTU4_TGIB4)
#endif
void Interrupt_MTU4_TGIB4_and_TPU10_TGI10B(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN4)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func2_callback_func[4] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func2_callback_func[4]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRB_callback_func[10] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRB_callback_func[10]();
			}
#endif
	}
}

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

#if FAST_INTC_VECTOR == VECT_MTU0_TGIC0
#pragma interrupt Interrupt_MTU0_TGIC0_and_TPU6_TGI6C(vect=VECT_MTU0_TGIC0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGIC0_and_TPU6_TGI6C(vect=VECT_MTU0_TGIC0)
#endif
void Interrupt_MTU0_TGIC0_and_TPU6_TGI6C(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN0)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func3_callback_func[0] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func3_callback_func[0]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRC_callback_func[6] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRC_callback_func[6]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU3_TGIC3
#pragma interrupt Interrupt_MTU3_TGIC3_and_TPU9_TGI9C(vect=VECT_MTU3_TGIC3, fint)
#else
#pragma interrupt Interrupt_MTU3_TGIC3_and_TPU9_TGI9C(vect=VECT_MTU3_TGIC3)
#endif
void Interrupt_MTU3_TGIC3_and_TPU9_TGI9C(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN3)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func3_callback_func[3] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func3_callback_func[3]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRC_callback_func[9] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRC_callback_func[9]();
			}
#endif
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

#if FAST_INTC_VECTOR == VECT_MTU0_TGID0
#pragma interrupt Interrupt_MTU0_TGID0_and_TPU6_TGI6D(vect=VECT_MTU0_TGID0, fint)
#else
#pragma interrupt Interrupt_MTU0_TGID0_and_TPU6_TGI6D(vect=VECT_MTU0_TGID0)
#endif
void Interrupt_MTU0_TGID0_and_TPU6_TGI6D(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN0)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func4_callback_func[0] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func4_callback_func[0]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRD_callback_func[6] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRD_callback_func[6]();
			}
#endif
	}
}

#if FAST_INTC_VECTOR == VECT_MTU3_TGID3
#pragma interrupt Interrupt_MTU3_TGID3_and_TPU9_TGI9D(vect=VECT_MTU3_TGID3, fint)
#else
#pragma interrupt Interrupt_MTU3_TGID3_and_TPU9_TGI9D(vect=VECT_MTU3_TGID3)
#endif
void Interrupt_MTU3_TGID3_and_TPU9_TGI9D(void)
{
	/* Are MTU or TPU interrupts selected? */
	if(0 == ICU.SEL.BIT.CN3)
	{
		/* MTU */
		/* Call the user function */
		if (rpdl_MTU2_func4_callback_func[3] != PDL_NO_FUNC)
		{
			rpdl_MTU2_func4_callback_func[3]();
		}
	}
	else
	{
		/* TPU */
#if !defined (DEVICE_PACKAGE_100_PIN) && !defined (DEVICE_PACKAGE_64_PIN) && !defined (DEVICE_PACKAGE_48_PIN)
			/* Call the user function */
			if (rpdl_TPU_TGRD_callback_func[9] != PDL_NO_FUNC)
			{
				rpdl_TPU_TGRD_callback_func[9]();
			}
#endif
	}
}

/* End of file */
