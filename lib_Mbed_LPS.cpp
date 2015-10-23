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

#include "lib_Mbed_LPS.h"


#define MBED_ID "101000000000000000000002F7F17DC0acd36051775585b8c16ad6431f445cd5" // MBED_ID se trouvant dans MBED.HTM entre auth= et &loader=


void getMbedID(char *ID)
{
    LocalFileSystem local("mbed");
    FILE *fp = NULL;
    char * chp;
    
    fp = fopen("/mbed/MBED.htm", "r");
    if(!fp)     printf("erreur ouverture du fichier MBED.htm\r\n");
    else
    {
        fscanf(fp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s url=http://mbed.org/start?auth=%s", ID);
        chp = strchr(ID,'&');
        *chp = '\0';
        fclose(fp);
    }
}

bool checkIDs(void)
{
    char ID[100];
    getMbedID(&ID[0]);
    if(strncmp(ID, MBED_ID, strlen(MBED_ID)) != 0)
    {
        printf("unknown Mbed\r\n");
        return true;
    }
    return false;
}

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
        printf("Could not open directory!\n");
    }
    closedir(d);
    return file_name;
}