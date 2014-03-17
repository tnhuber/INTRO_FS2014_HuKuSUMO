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

static void APP_EvntHandler(EVNT_Handle event) {
  switch(event) { 
    case EVNT_INIT:
      LED1_On();
      WAIT1_Waitms(100);
      LED1_Off();
      break;
    default:
      break;
  }
}

static void APP_Loop(void) {
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
  } /* for */
}

void APP_Run(void) {
  PL_Init();
  EVNT_SetEvent(EVNT_INIT);
  APP_Loop();
  PL_Deinit();
}
