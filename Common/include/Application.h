/**
 * \file
 * \brief Main Application Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Interface to the main application module. 
 * From here the application runs and performs all tasks.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

/*!
 * \brief Debug printing function
 * \param str Debug string to print
 */
void APP_DebugPrint(unsigned char *str);

/*!
 * \brief Application main start and main routine 
 */
void APP_Start(void);

#endif /* APPLICATION_H_ */
