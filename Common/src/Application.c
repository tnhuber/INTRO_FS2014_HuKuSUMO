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
#if PL_HAS_PID
  #include "Pid.h"
  #include "Tacho.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_RADIO
  #include "RadioSMAC.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
  #include "RStdIO.h"
#endif
#if PL_HAS_ACCEL_OFF
  #include "Accel.h"
  #include "Motor.h"
  #include "Shell.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#include "Trigger.h"

void APP_DebugPrint(unsigned char *str) {
#if PL_HAS_SHELL
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}

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
  case EVNT_SW1_LPRESSED:
#if PL_HAS_REMOTE
    if (REMOTE_GetOnOff()) {
      REMOTE_SetOnOff(FALSE); /* turn off */
#if PL_HAS_BUZZER
     (void)BUZ_Beep(300, 200);
     WAIT1_WaitOSms(500);
     (void)BUZ_Beep(300, 200);
#endif
    } else {
      REMOTE_SetOnOff(TRUE); /* turn on */
#if PL_HAS_BUZZER
     (void)BUZ_Beep(300, 200);
#endif
    }
#endif
    break;
  case EVNT_SW1_PRESSED:
    LED1_Neg();
#if PL_HAS_BUZZER
  (void)BUZ_Beep(300, 500);
#endif
    break;
#endif
  case EVNT_SW1_RELEASED:
   break;
#if PL_NOF_KEYS>=2
  case EVNT_SW2_LPRESSED:
#if PL_HAS_REMOTE && PL_APP_ACCEL_CONTROL_SENDER
    (void)RSTDIO_SendToTxStdio(RSTDIO_QUEUE_TX_IN, "buzzer buz 800 400\r\n", sizeof("buzzer buz 800 400\r\n")-1);
#endif
    break;
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
#if PL_HAS_RADIO
    default:
      RADIO_AppHandleEvent(event); /* call Radio event handler */
      break;
#else
    default:
      break;
#endif      
  }
}

#if PL_HAS_ULTRASONIC
static portTASK_FUNCTION(PingTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    (void)US_Measure_us();
    FRTOS1_vTaskDelay(300/portTICK_RATE_MS);
  }
}
#endif

#if PL_HAS_RTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
  uint16_t msCnt;
  
  (void)pvParameters; /* parameter not used */
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
#if PL_HAS_ACCEL_OFF
    {
      int16_t x, y, z;
      bool isEnabled;
      uint8_t res;
      
      res = MMA1_isEnabled(&isEnabled);
      if (res==ERR_OK && isEnabled) {
        ACCEL_GetValues(&x, &y, &z);
        if (z>800) {
          MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
          MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
  #if PL_HAS_DRIVE
          DRV_SetSpeed(0, 0);
  #endif
          SHELL_SendString((unsigned char*)"Engines stopped!\r\n");
        }
      } else {
        SHELL_SendString((unsigned char*)"Accelerometer disabled?\r\n");
        (void)MMA1_Enable();
      }
    }
#endif /* PL_HAS_ACCEL_OFF */
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
    msCnt += 20;
    if ((msCnt>=1000)) { /* every second */
      LED1_Neg();
      msCnt = 0;
    }
  } /* for */
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

void APP_Start(void) {
#if PL_HAS_RTOS_TRACE
  if (!RTOSTRC1_uiTraceStart()) {
    for(;;) {} /* failed! */
  }
#endif
  PL_Init();
  EVNT_SetEvent(EVNT_INIT);
#if PL_HAS_ULTRASONIC
  if (FRTOS1_xTaskCreate(
        PingTask,  /* pointer to the task */
        "Ping", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
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
