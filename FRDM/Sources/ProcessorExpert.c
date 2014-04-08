/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-02-24, 12:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "CS1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "HF1.h"
#include "SW1.h"
#include "BitIoLdd4.h"
#include "BUZ1.h"
#include "BitIoLdd5.h"
#include "UTIL1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "BT1.h"
#include "Serial1.h"
#include "ASerialLdd2.h"
#include "LED_IR.h"
#include "LEDpin4.h"
#include "BitIoLdd6.h"
#include "RefCnt.h"
#include "IR1.h"
#include "BitIoLdd7.h"
#include "IR2.h"
#include "BitIoLdd8.h"
#include "IR3.h"
#include "BitIoLdd9.h"
#include "IR4.h"
#include "BitIoLdd10.h"
#include "IR5.h"
#include "BitIoLdd11.h"
#include "IR6.h"
#include "BitIoLdd12.h"
#include "FRTOS1.h"
#include "RTOSTRC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for (;;)
  {
	  LED1_Neg();
	  WAIT1_Waitms(500);
	  LED1_Neg();
	  LED2_Neg();
	  WAIT1_Waitms(500);
	  LED2_Off();
	  LED3_On();
	  WAIT1_Waitms(500);
	  LED3_Off();
  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
