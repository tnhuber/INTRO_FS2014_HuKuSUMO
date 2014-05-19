/**
 * \file
 * \brief Platform Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This implements the platform interface. 
 * Here the platform gets initialized, and all platform dependent macros get defined.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project, e.g. 'bool' */
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_SRB   (defined(PL_BOARD_IS_SRB))
  /*!< Macro is defined through compiler option for the SRB board */
#define PL_IS_FRDM  (defined(PL_BOARD_IS_FRDM))
  /*!< Macro is defined through compiler option for the FRDM board */

/* here all the different 'enable' macros for the application are defined */
#define PL_HAS_LED            (1)
  /*!< Set to 1 if we have LEDs available, 0 otherwise */
#define PL_HAS_EVENTS         (1)
  /*!< Set to 1 if we have the Event module implemented, 0 otherwise */
#define PL_HAS_TIMER          (1)
  /*!< Set to 1 if we have the Timer module implemented, 0 otherwise */
#define PL_HAS_LED_HEARTBEAT  (0)
  /*!< Set to 1 if we have a LED heartbeat, 0 otherwise */
#define PL_HAS_KEYS           (1)
  /*!< Set to 1 if we have push buttons (keys) implemented, 0 otherwise */
#define PL_HAS_KBI            (PL_IS_SRB)
  /*!< Set to 1 if we have use keyboard interrupt */
#define PL_HAS_TRIGGER        (1)
  /*!< Set to 1 if we have use trigger */
#define PL_HAS_BUZZER         (1)
  /*!< Set to 1 if we have a buzzer */
#define PL_HAS_DEBOUNCE       (1)
  /*!< Set to 1 if we have debounce the keys */
#define PL_HAS_RTOS           (1)
  /*!< If we are using an RTOS */
#define PL_HAS_SEMAPHORE      (1)
  /*!< If we are using test tasks for semaphores */
#define PL_HAS_SHELL          (1)
  /*!< If we have a shell */
#define PL_HAS_BLUETOOTH      (1 && PL_IS_FRDM)
  /*!< If we are using an RTOS */
#define PL_HAS_SHELL_QUEUE    (1)
  /*!< If we have a message queue for the shell */
#define PL_HAS_LINE_SENSOR    (1 && PL_IS_FRDM)
  /*!< If we are having a line sensor */
#define PL_HAS_MOTOR          (1 && PL_IS_FRDM)
  /*!< Set to one if having DC motor driver */
#define PL_HAS_ACCEL          (1)
  /*!< Set to one if having acceleration sensor */
#define PL_HAS_CONFIG_NVM     (1)
  /*!< Set to one if using non-volatile memory for configuration data */

#define PL_HAS_QUADRATURE     (1 && PL_IS_FRDM)
  /*!< Set to one if having quadrature sensor */
#define PL_HAS_MOTOR_TACHO    (1 && PL_HAS_QUADRATURE)
  /*!< Set to one if we measure the speed */
#define PL_HAS_SHELL_TRACE    (1)
  /*!< Set to one if we trace values to the shell */

#define PL_HAS_PID            (1 && PL_HAS_MOTOR)
  /*!< Set to one if we we have motor PID closed loop control */
#define PL_HAS_DRIVE          (1 && PL_HAS_PID)
  /*!< Set to one if we we have a drive task */
#define PL_HAS_ULTRASONIC     (1 && PL_IS_FRDM)
  /*!< Set to one if we have an ultrasonic distance measurement sensor */
#define PL_HAS_RADIO          (0)
  /*!< Set to one if we have a radio transceiver */

#define PL_HAS_REMOTE         (0)
  /*!< Set to one for remote controller support */
#define PL_APP_ACCEL_CONTROL_SENDER (1 && PL_HAS_REMOTE && PL_IS_SRB)
  /*!< Set to one for SRB as sender */
#define PL_HAS_FREEMASTER     (0)
  /*!< Set to one if we are using FreeMaster. Need to disable UART in Shell! */
#define PL_HAS_WATCHDOG       (0)
  /*!< Set to one if using watchdog timer */

#define PL_HAS_ACCEL_OFF      (1 && PL_HAS_ACCEL && PL_HAS_MOTOR)
  /*!< Set to one if turning the robot upside down turns off the engines */

#define PL_HAS_RTOS_TRACE     (1 && PL_HAS_RTOS && PL_IS_FRDM)
  /*!< Set to one if using Percepio Trace */

#if PL_IS_FRDM
  #define PL_NOF_LEDS       3
     /*!< FRDM board has 3 LEDs (RGB) */
  #define PL_NOF_KEYS       1
     /*!< Number of push buttons on the SRB board */
  #define PL_BUZZER_IS_ON_OFF (0)
     /*!< Set to 1 if buzzer is using on-off signal */
  #define PL_BUZZER_IS_SW_PWM (1)
     /*!< Set to 1 if buzzer needs a software PWM signal */
  #define PL_BUZZER_IS_HW_PWM (0)
     /*!< Set to 1 if buzzer uses a hardware PWM signal */
#elif PL_IS_SRB
  #define PL_NOF_LEDS       5
     /*!< We have 5 LED's on the SRB board */
  #define PL_NOF_KEYS       4
     /*!< Number of push buttons on the SRB board */
  #define PL_BUZZER_IS_ON_OFF (1)
     /*!< Set to 1 if buzzer is using on-off signal */
  #define PL_BUZZER_IS_SW_PWM (0)
     /*!< Set to 1 if buzzer needs a software PWM signal */
  #define PL_BUZZER_IS_HW_PWM (0)
     /*!< Set to 1 if buzzer uses a hardware PWM signal */
#else
  #error "unknown configuration?"
#endif

/*!
 * \brief Platform initialization
 */
void PL_Init(void);

/*!
 * \brief Platform de-initialization
 */
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
