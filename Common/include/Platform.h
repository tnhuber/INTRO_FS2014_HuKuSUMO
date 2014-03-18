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
#define PL_HAS_TRIGGER  1
  /*!< Set to 1 if we have use trigger */
#define PL_HAS_BUZZER   1
  /*!< Set to 1 if we have a buzzer */
#define PL_HAS_DEBOUNCE 1
  /*!< Set to 1 if we have debounce the keys */
#define PL_HAS_SHELL    0
  /*!< Set to 1 if we have use a shell */

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
