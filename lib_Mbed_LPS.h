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
* DigitalOut led(LED1);
* 
* void interruption_serie(void);
* 
* 
* int main()
* {
*     if(!checkIDs()) return 0;
*     pc.attach(&interruption_serie);
*     
*     while(1)
*     {
*         led = !led;
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

/** MBED_ID est un define correspondant a une chaine de caracteres contenant l'ID attendu du Mbed
 */
#define MBED_ID "101000000000000000000002F7F204A764cc6e6a004f5a3470ff1975de9d0ddd" // MBED_ID se trouvant dans MBED.HTM entre auth= et &loader=

/** Permet d'obtenir l'ID unique du Mbed
 *
 *  @param ID pointeur sur une chaine de caractere contenant l'ID unique du Mbed
 */
void getMbedID(char *ID);

/** Renvoie true si l'ID unique du Mbed correspond à celui attendu
 *
 */
bool checkIDs(void);

/** Renvoie une chaine de caractere contenant le nom du dernier fichier cree sur le Mbed
 *
 */
char * getLastMbedFileName(void);

#endif