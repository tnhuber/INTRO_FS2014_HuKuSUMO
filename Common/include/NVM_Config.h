/**
 * \file
 * \brief Non-Volatile memory configuration handling.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the infrastructure to store configuration data
 * into non-volatile FLASH memory on the microcontroller.
 */

#ifndef CONFIGNVM_H_
#define CONFIGNVM_H_

#include "Platform.h"

#if PL_IS_FRDM
  #define NVMC_FLASH_START_ADDR    0x1FC00 
  /*!< NVRM_Config, start address of configuration data in flash */
#elif PL_IS_SRB
  #define NVMC_FLASH_START_ADDR    0xFBB0 
  /*!< NVRM_Config, start address of configuration data in flash */
#else
  #error "unknown target?"
#endif

/* macros for identify erased flash memory */
#define NVMC_FLASH_ERASED_UINT8  0xFF
  /*!< erased byte in flash */
#define NVMC_FLASH_ERASED_UINT16 0xFFFF
  /*!< erased word in flash */

#define NVMC_REFLECTANCE_DATA_START_ADDR  (NVMC_FLASH_START_ADDR)
#define NVMC_REFLECTANCE_DATA_SIZE        (8*2*2) /* maximum of 8 sensors (min and max) values with 16 bits */
#define NVMC_REFLECTANCE_END_ADDR         (NVMC_REFLECTANCE_DATA_START_ADDR+NVMC_REFLECTANCE_DATA_SIZE)

uint8_t NVMC_SaveReflectanceData(void *data, uint16_t dataSize);
void *NVMC_GetReflectanceData(void);


#endif /* CONFIGNVM_H_ */
