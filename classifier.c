#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "funciones.h"
#include <ctype.h>
#include <time.h>

int main(){
    //realizar validacion de directorios
    if (directory_initialization() == 0){
        puts("directorios ya creados");
    }
    
    DIR* directory = opendir("./testCases");
    struct dirent* entrada;
    int cantidad_sopas = 0;
    
    if (directory == NULL){
        puts("Error al abrir el directorio");
        return 1;
    }

   
    while ( ( entrada=readdir(directory) ) ){
        
        if ( strstr(entrada->d_name, ".txt") != NULL){
            cantidad_sopas++;
            //printf(" %s\n", entrada->d_name);    
            procesarTxt(entrada->d_name);
            //puts("archivo procesado");
        
        }
    }
    printf("cantidad archivos procesados = %d\n", cantidad_sopas);
    closedir(directory);
    return 0;
}