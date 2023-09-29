#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
//#include "funciones.h"
#include <ctype.h>
#include <time.h>

void concat(char* buffer, int buf_size, char* s1, char* s2){
    int i,j,k;
    //printf("string a concat: %s %s\n", s1,s2);
    j=0;
    for(k = 0; k<(int)strlen(s1); k++){
        buffer[j] = s1[k];
        j++;
    }
    for(i = 0; i<(int)strlen(s2);i++){
        buffer[j] = s2[i];
        //puts(buffer);
        j++;
    }
    buffer[j] = '\0';
    //printf("buffer final: %s\n", buffer);
}

char** procesarTxt(const char* nombre_archivo){
    char* base_path = "testCases/";
    char* path = (char*)malloc(sizeof(char)*(strlen(nombre_archivo)+strlen(base_path)+1));
    concat(path,strlen(nombre_archivo)+strlen(base_path)+1,base_path,(char*)nombre_archivo);
    //puts(path);
    FILE* archivo;
    archivo = fopen(path, "r");
    char** map_buffer;
    map_buffer = (char**)malloc(sizeof(char*)*5);
    for (int i = 0; i<5 ; i++){
        map_buffer[i]=(char*)malloc(sizeof(char)*25);
    }
    int i = 0;
    char buffer[25];
    while(fgets(buffer, 25, archivo)!= NULL){
        
        map_buffer[i]=buffer;
        printf("%s", map_buffer[i]);
        i++;
    }
    fclose(archivo);
    return map_buffer;
}


int main(){
    
    DIR* directory = opendir("./testCases");
    struct dirent* entrada;
    int cantidad_sopas = 0;
    
    if (directory == NULL){
        puts("Error al abrir el directorio");
        return 1;
    }

    char*** maps;
    maps = (char***)malloc(sizeof(char**)*9);
    for(int i = 0; i<9 ; i++){
        maps[i] = (char**)malloc(sizeof(char*)*5);
        for(int j = 0; j<5; j++){
            maps[i][j]= (char*)malloc(sizeof(char)*25);
        }
    }
    while ( ( entrada=readdir(directory) ) ){
        if ( strstr(entrada->d_name, ".txt") != NULL){
            
            printf("archivo en proceso: %s\n", entrada->d_name);    
            maps[cantidad_sopas] = procesarTxt(entrada->d_name);
            //puts("archivo procesado");
            for (int i = 0; i<5 ; i++){
                printf("%s\n", maps[cantidad_sopas][i]);


            }
            
            cantidad_sopas++;
        }
    }
    //free(maps);
    printf("cantidad archivos procesados = %d\n", cantidad_sopas);
    closedir(directory);
    return 0;
}