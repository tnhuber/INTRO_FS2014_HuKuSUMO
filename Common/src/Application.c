/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "WAIT1.h"
#include "LED.h"
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif

static void APP_EvntHandler(EVNT_Handle event) {
  switch(event) { 
    case EVNT_INIT:
      LED1_On();
      WAIT1_Waitms(100);
      LED1_Off();
      break;

#if PL_HAS_LED_HEARTBEAT
    case EVNT_LED_HEARTBEAT:
      LED3_Neg();
      break;
#endif
#if PL_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
    LED1_Neg();
#if PL_HAS_BUZZER
  (void)BUZ_Beep(300, 500);
#endif
    break;
#endif
#if PL_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
    LED2_Neg();
    break;
#endif
#if PL_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
    LED3_Neg();
    break;
#endif
#if PL_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
    LED4_Neg();
    break;
#endif

    default:
      break;
  }
}

static void APP_Loop(void) {
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
  } /* for */
}

void APP_Run(void) {
  PL_Init();
  EVNT_SetEvent(EVNT_INIT);
  APP_Loop();
  PL_Deinit();
}
