/**
 * \file
 * \brief Platform implementation module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This implements the platform module. 
 * Here the platform gets initialized, and all platform dependent macros get defined.
 */

#include "Platform.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_DEBOUNCE
  #include "Debounce.h"
#endif

#if PL_HAS_LED
static void PL_LedInit(void) {
  /* all LED's off by default */
  #if PL_NOF_LEDS>=1
  LED1_Off();
  #endif
  #if PL_NOF_LEDS>=2
  LED2_Off();
  #endif
  #if PL_NOF_LEDS>=3
  LED3_Off();
  #endif
  #if PL_NOF_LEDS>=4
  LED4_Off();
  #endif
  #if PL_NOF_LEDS>=5
  LED5_Off();
  #endif
}
#endif /* PL_HAS_LED */

#if PL_HAS_LED
static void PL_LedDeinit(void) {
  /* all LED's off by default */
  #if PL_NOF_LEDS>=1
  LED1_Off();
  #endif
  #if PL_NOF_LEDS>=2
  LED2_Off();
  #endif
  #if PL_NOF_LEDS>=3
  LED3_Off();
  #endif
  #if PL_NOF_LEDS>=4
  LED4_Off();
  #endif
  #if PL_NOF_LEDS>=5
  LED5_Off();
  #endif
}
#endif /* PL_HAS_LED */

void PL_Init(void) {
#if PL_HAS_LED
  PL_LedInit();
#endif  
#if PL_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_HAS_TIMER
  TMR_Init();
#endif
#if PL_HAS_KEYS
  KEY_Init();
#endif
#if PL_HAS_TRIGGER
  TRG_Init();
#endif
#if PL_HAS_BUZZER
  BUZ_Init();
#endif
#if PL_HAS_DEBOUNCE
  DBNC_Init();
#endif
}

void PL_Deinit(void) {
#if PL_HAS_DEBOUNCE
  DBNC_Deinit();
#endif
#if PL_HAS_BUZZER
  BUZ_Deinit();
#endif
#if PL_HAS_TRIGGER
  TRG_Deinit();
#endif
#if PL_HAS_KEYS
  KEY_Init();
#endif
#if PL_HAS_TIMER
  TMR_Deinit();
#endif
#if PL_HAS_EVENTS
  EVNT_Deinit();
#endif
#if PL_HAS_LED
  PL_LedDeinit();
#endif
}
