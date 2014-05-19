/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_HAS_TIMER
#include "Timer.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
#if PL_HAS_LED_HEARTBEAT
  /* timer interrupt is calling us every TMR_TICK_MS ms */
  static uint16_t cnt = 0; /* using static local variable */

  cnt++;
  if (cnt==1000/TMR_TICK_MS) { /* every second */
    /* using event method */
    EVNT_SetEvent(EVNT_LED_HEARTBEAT);
    cnt = 0; /* reset counter */
  }
#endif
#if PL_HAS_TRIGGER
  TRG_IncTick();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Sample(); /*! \todo Need to perform maybe sampling at a lower speed */
#endif
}

/*! \brief Timer driver initialization */
void TMR_Init(void) {
  /* nothing needed right now */
}

/*! \brief Timer driver de-initialization */
void TMR_Deinit(void) {
  /* nothing needed right now */
}
#endif /*PL_HAS_TIMER*/
