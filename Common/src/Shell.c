/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#if PL_NOF_LEDS>=1
  #include "LED1.h"
#endif
#if PL_NOF_LEDS>=2
  #include "LED2.h"
#endif
#if PL_NOF_LEDS>=3
  #include "LED3.h"
#endif
#if PL_NOF_LEDS>=4
  #include "LED4.h"
#endif
#if PL_NOF_LEDS>=5
  #include "LED5.h"
#endif
#if PL_HAS_BLUETOOTH
  #include "BT1.h"
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
  #include "MMA1.h"
#endif
#if PL_HAS_CONFIG_NVM
  #include "NVM_Config.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
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
  #include "RNET1.h"
  #include "RNet_App.h"
  #include "RNetConf.h"
#endif
#if RNET_CONFIG_REMOTE_STDIO
  #include "RStdIO.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif

void SHELL_SendString(unsigned char *msg) {
#if PL_HAS_SHELL_QUEUE
  /*! \todo Implement function using queues */
  SQUEUE_SendString(msg);
#else
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
#endif
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if PL_HAS_RTOS
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#endif
#if PL_NOF_LEDS>=1
#if LED1_PARSE_COMMAND_ENABLED
  LED1_ParseCommand,
#endif
#endif
#if PL_NOF_LEDS>=2
#if LED2_PARSE_COMMAND_ENABLED
  LED2_ParseCommand,
#endif
#endif
#if PL_NOF_LEDS>=3
#if LED3_PARSE_COMMAND_ENABLED
  LED3_ParseCommand,
#endif
#endif
#if PL_NOF_LEDS>=4
#if LED4_PARSE_COMMAND_ENABLED
  LED4_ParseCommand,
#endif
#endif
#if PL_NOF_LEDS>=5
#if LED5_PARSE_COMMAND_ENABLED
  LED5_ParseCommand,
#endif
#endif
#if PL_HAS_BLUETOOTH
#if BT1_PARSE_COMMAND_ENABLED
  BT1_ParseCommand,
#endif
#endif
#if PL_HAS_LINE_SENSOR
  REF_ParseCommand,
#endif
#if PL_HAS_MOTOR
  MOT_ParseCommand,
#endif
#if PL_HAS_BUZZER
  BUZ_ParseCommand,
#endif
#if PL_HAS_ACCEL
#if defined(MMA1_PARSE_COMMAND_ENABLED)
  MMA1_ParseCommand,
#endif
#endif
#if PL_HAS_CONFIG_NVM
  /* no parser yet */
#endif
#if PL_HAS_QUADRATURE
#if Q4CLeft_PARSE_COMMAND_ENABLED
  Q4CLeft_ParseCommand,
#endif
#if Q4CRight_PARSE_COMMAND_ENABLED
  Q4CRight_ParseCommand,
#endif
#endif /* PL_HAS_QUADRATURE */
#if PL_HAS_MOTOR_TACHO
  TACHO_ParseCommand,
#endif
#if PL_HAS_SHELL_TRACE
  TRACE_ParseCommand,
#endif
#if PL_HAS_PID
  PID_ParseCommand,
#endif
#if PL_HAS_DRIVE
  DRV_ParseCommand,
#endif
#if PL_HAS_ULTRASONIC
  US_ParseCommand,
#endif
#if PL_HAS_RADIO
  RNET1_ParseCommand,
  RNETA_ParseCommand,
#endif
#if PL_HAS_REMOTE
  REMOTE_ParseCommand,
#endif
  NULL /* Sentinel */
};

#if PL_HAS_BLUETOOTH
/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};
static unsigned char bluetooth_buf[48];
#endif

static unsigned char localConsole_buf[48];

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
#if RNET_CONFIG_REMOTE_STDIO
  static unsigned char radio_cmd_buf[48];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
#if CLS1_DEFAULT_SERIAL
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
#endif
  
  (void)pvParameters; /* not used */
#if CLS1_DEFAULT_SERIAL
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
#endif
  for(;;) {
#if CLS1_DEFAULT_SERIAL
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
#endif
#if RNET_CONFIG_REMOTE_STDIO
    RSTDIO_Print(ioLocal); /* dispatch incoming messages */
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), ioRemote, CmdParserTable);
#endif
#if PL_HAS_BLUETOOTH
    (void)CLS1_ReadAndParseWithCommandTable(bluetooth_buf, sizeof(bluetooth_buf), &BT_stdio, CmdParserTable);
#endif
#if PL_HAS_SHELL_QUEUE
    {
      /*! \todo Handle shell queue */
      unsigned char ch;

      while((ch=SQUEUE_ReceiveChar()) && ch!='\0') {
        ioLocal->stdOut(ch);
#if PL_HAS_BLUETOOTH
        BT_stdio.stdOut(ch); /* copy on Bluetooth */
#endif
      }
    }
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}
#endif /* PL_HAS_RTOS */

void SHELL_Init(void) {
#if PL_HAS_BLUETOOTH
  bluetooth_buf[0] = '\0';
#endif
  localConsole_buf[0] = '\0';
  CLS1_Init();
#if !CLS1_DEFAULT_SERIAL && PL_HAS_BLUETOOTH
  (void)CLS1_SetStdio(&BT_stdio); /* use the Bluetooth stdio as default */
#endif
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

void SHELL_Deinit(void) {
  CLS1_Deinit();
}
#endif /* PL_HAS_SHELL */
