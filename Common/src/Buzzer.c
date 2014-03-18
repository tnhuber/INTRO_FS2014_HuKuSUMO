/*
 * Buzzer.c
 *
 *  Created on: Aug 29, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_BUZZER
#include "Buzzer.h"
#include "BUZ1.h"
#include "Trigger.h"

#ifdef __HC08__
#pragma MESSAGE DISABLE C5904 /* division by zero */
#endif

#if PL_BUZZER_IS_SW_PWM
typedef struct {
  uint16_t buzIterationCntr, buzPeriodTicks;
} BUZ_TrgInfo;

static volatile BUZ_TrgInfo trgInfo;
#endif

static void BUZ_Toggle(void *dataPtr) {
#if PL_BUZZER_IS_HW_PWM
  (void)dataPtr; /* not used */
  (void)BUZ1_SetRatio16(0);  
#elif PL_BUZZER_IS_ON_OFF
  (void)dataPtr; /* not used */
  BUZ1_ClrVal(); /* turn buzzer off */
#elif PL_BUZZER_IS_SW_PWM
  BUZ_TrgInfo *trgInfo = (BUZ_TrgInfo *)dataPtr;
  
  if (trgInfo->buzIterationCntr==0) {
    BUZ1_ClrVal(); /* turn buzzer off */
  } else {
    trgInfo->buzIterationCntr--;
    BUZ1_NegVal();
    (void)TRG_SetTrigger(TRG_BUZ_BEEP, trgInfo->buzPeriodTicks, BUZ_Toggle, trgInfo);
  }
#else
  #error "Unknown hardware configuration?"
#endif
}

uint8_t BUZ_Beep(uint16_t freq, uint16_t durationMs) {
#if PL_BUZZER_IS_HW_PWM
  (void)BUZ1_SetRatio16(freq<<4);  
  return TRG_SetTrigger(TRG_BUZ_BEEP, durationMs/TRG_TICKS_MS, BUZ_Toggle);
#elif PL_BUZZER_IS_ON_OFF
  (void)freq; /* not used */
  BUZ1_SetVal(); /* turn buzzer on */
  return TRG_SetTrigger(TRG_BUZ_BEEP, durationMs/TRG_TICKS_MS, BUZ_Toggle, NULL);
#elif PL_BUZZER_IS_SW_PWM
  if (trgInfo.buzIterationCntr==0) { /* only if no buzzer is running right now */
    BUZ1_SetVal(); /* turn buzzer on */
    trgInfo.buzPeriodTicks = (1000*TRG_TICKS_MS)/freq;
    trgInfo.buzIterationCntr = durationMs/TRG_TICKS_MS/trgInfo.buzPeriodTicks;
    return TRG_SetTrigger(TRG_BUZ_BEEP, trgInfo.buzPeriodTicks, BUZ_Toggle, (void*)&trgInfo);
  } else {
    return ERR_BUSY;
  }
#else
  #error "Unknown hardware configuration?"
  return ERR_FAILED;
#endif
}

void BUZ_Deinit(void) {
  /* nothing to do */
}

void BUZ_Init(void) {
#if PL_BUZZER_IS_HW_PWM
  BUZ1_Enable();
  BUZ1_SetRatio16(0); /* off */ 
#elif PL_BUZZER_IS_ON_OFF
  BUZ1_ClrVal(); /* turn buzzer off */
#elif PL_BUZZER_IS_SW_PWM
  BUZ1_SetVal(); /* turn buzzer on */
  trgInfo.buzPeriodTicks = 0;
  trgInfo.buzIterationCntr = 0;
#endif
}

#endif /* PL_HAS_BUZZER */
