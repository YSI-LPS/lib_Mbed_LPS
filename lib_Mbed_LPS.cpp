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

#include "lib_Mbed_LPS.h"

/** Permet d'obtenir l'ID unique du Mbed
 *
 *  @param ID pointeur sur une chaine de caractere contenant l'ID unique du Mbed
 */
void getMbedID(char *ID)
{
    LocalFileSystem local("mbed");
    FILE *fp = NULL;
    char * chp;
    
    fp = fopen("/mbed/MBED.htm", "r");
    if(!fp)     printf("Could not open directory!\r\n");
    else
    {
        fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s url=http://mbed.org/start?auth=%s", ID);
        chp = strchr(ID,'&');
        *chp = '\0';
        fclose(fp);
    }
}

/** Renvoie true si l'ID unique du Mbed correspond à celui attendu
 *
 */
bool checkIDs(void)
{
    char ID[100];
    getMbedID(&ID[0]);
    if(strncmp(ID, MBED_ID, strlen(MBED_ID)) != 0)
    {
        printf("unknown Mbed\r\n");
        return false;
    }
    return true;
}

/** Renvoie une chaine de caractere contenant le nom du dernier fichier cree sur le Mbed
 *
 */
char * getLastMbedFileName(void)
{
    LocalFileSystem local("mbed");
    DIR *d;
    struct dirent *p;
    static char file_name[20];
 
    d = opendir("/mbed");
    if (d != NULL) 
    {
        while((p = readdir(d)) != NULL) sprintf(file_name,"%s", p->d_name);
    }
    else 
    {
        printf("Could not open directory!\r\n");
    }
    closedir(d);
    return file_name;
}