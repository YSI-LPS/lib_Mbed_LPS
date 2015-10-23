/** Lib Mbed LPS
*
* Copyright (c) 2014, cstyles (http://mbed.org)
*
* Exemple:
* @code
* #include "mbed.h"
* #include "lib_Mbed_LPS.h"
* 
* 
* Serial pc(USBTX,USBRX);
* 
* void interruption_serie(void);
* 
* 
* int main()
* {
*     if(checkIDs()) return 0;
*     pc.attach(&interruption_serie);
*     
*     while(1)
*     {
*         wait(0.25);
*     }
* }
* 
* void interruption_serie(void)
* {
*     char caractere = pc.getc();
*     switch(caractere) 
*     {
*         case '?':
*             pc.printf("%s\r\n",getLastMbedFileName());
*         break;
*     }
* }
* @endcode
* @file          lib_Mbed_LPS.h 
* @purpose       library for Mbed LPS
* @date          2015
* @author        Yannic Simon
*/

#ifndef DEF_lib_Mbed_LPS_H
#define DEF_lib_Mbed_LPS_H

#include "mbed.h"

void getMbedID(char *ID);

bool checkIDs(void);

char * getLastMbedFileName(void);

#endif