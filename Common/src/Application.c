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
#include "WAIT1.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
  #include "RTOS.h"
#endif
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif

BaseType_t APP_EnterTicklessIdle(void) {
  return pdTRUE;
}

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

#if PL_HAS_RTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
  uint16_t msCnt;
  
  (void)pvParameters; /* parameter not used */
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
    msCnt += 20;
    if (msCnt>1000) {
      LED1_Neg();
      msCnt = 0;
    }
  }
}
#else
static void APP_Loop(void) {
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
  } /* for */
}
#endif

void APP_Run(void) {
#if PL_HAS_RTOS_TRACE
  if (!RTOSTRC1_uiTraceStart()) {
    for(;;) {} /* failed! */
  }
#endif
  PL_Init();
  EVNT_SetEvent(EVNT_INIT);
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(
        MainTask,  /* pointer to the task */
        "Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
#else
  APP_Loop();
#endif
  PL_Deinit();
}
