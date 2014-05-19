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
#if PL_HAS_RTOS
  #include "RTOS.h"
#endif
#if PL_HAS_SEMAPHORE
  #include "Sem.h"
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif
#if PL_HAS_LINE_SENSOR
  #include "Reflectance.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_SHELL_TRACE
  #include "ShellTrace.h"
#endif
#if PL_HAS_PID
  #include "Pid.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
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
#if PL_HAS_RTOS
  RTOS_Init();
#endif
#if PL_HAS_SEMAPHORE
  SEM_Init();
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_SHELL_QUEUE
  SQUEUE_Init();
#endif
#if PL_HAS_LINE_SENSOR
  REF_Init();
#endif
#if PL_HAS_MOTOR
  MOT_Init();
#endif
#if PL_HAS_ACCEL
  ACCEL_Init();
#endif
#if PL_HAS_RTOS_TRACE
  if (RTOSTRC1_uiTraceStart()==0) {
    for(;;){} /* error starting trace recorder. Not setup for enough queues/tasks/etc? */
  }
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Init();
#endif
#if PL_HAS_SHELL_TRACE
  TRACE_Init();
#endif
#if PL_HAS_PID
  PID_Init();
#endif
#if PL_HAS_DRIVE
  DRV_Init();
#endif
#if PL_HAS_ULTRASONIC
  US_Init();
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
#if PL_HAS_REMOTE
  REMOTE_Init();
#endif
}

void PL_Deinit(void) {
#if PL_HAS_REMOTE
  REMOTE_Deinit();
#endif
#if PL_HAS_RADIO
  RNETA_Deinit();
#endif
#if PL_HAS_ULTRASONIC
  US_Deinit();
#endif
#if PL_HAS_DRIVE
  DRV_Deinit();
#endif
#if PL_HAS_PID
  PID_Init();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Deinit();
#endif
#if PL_HAS_SHELL_TRACE
  TRACE_Deinit();
#endif
#if PL_HAS_ACCEL
  ACCEL_Deinit();
#endif
#if PL_HAS_MOTOR
  MOT_Deinit();
#endif
#if PL_HAS_LINE_SENSOR
  REF_Deinit();
#endif
#if PL_HAS_SHELL_QUEUE
  SQUEUE_Deinit();
#endif
#if PL_HAS_SHELL
  SHELL_Deinit();
#endif
#if PL_HAS_SEMAPHORE
  SEM_Deinit();
#endif
#if PL_HAS_RTOS
  RTOS_Deinit();
#endif
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
