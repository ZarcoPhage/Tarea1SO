#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
//#include "funciones.h"
#include <ctype.h>
#include <time.h>

typedef struct {
    char* contenido;
} casilla;

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

casilla*** loadMaps(){
    int num_tableros = 9; //numero de tableros a procesar

    DIR* directory = opendir("./maps"); //directorio con los tableros
    struct dirent* entrada;
    
    //mapa->tablero->lineas->casillas/fichas

    casilla*** mapas;
    
    mapas = (casilla***)malloc(num_tableros*sizeof(casilla**));
    
    for (int i = 0; i<num_tableros; i++){
        mapas[i] = (casilla**)malloc(5*sizeof(casilla*));
        for (int j = 0; j<5;j++){
            mapas[i][j] = (casilla*)malloc(5*sizeof(casilla));
            for (int k = 0; k<5;k++){
                mapas[i][j][k].contenido = (char*)malloc(2*sizeof(char));
                //mapas[i][j][k].contenido[0] = '0';
                //mapas[i][j][k].contenido[1] = '0';
            }
        }
    }

    /*

    for(int k = 0; k<num_tableros;k++){
        printf("mapa %d:\n",k);
        for (int i = 0; i<5;i++){
            for (int j = 0; j<5;j++){
                printf("%s ", mapas[k][i][j].contenido);
            }
            printf("\n");
        }
    }*/

    if (directory == NULL){
        puts("Error al abrir el directorio");
        //return 1;
    }

    int file_count = 0;
    char* token;
    const char delimit[2] = " ";
    char* linea = NULL;
    size_t largoLin = 0;
    int y_cas = 0;

    while ((entrada=readdir(directory)) && (file_count < 9) ){
        if ( strstr(entrada->d_name, ".txt") != NULL){
            char* nombre_archivo = entrada->d_name; //guardar nombre de archivos
            //printf("archivo en proceso: %s\n", nombre_archivo);    

            char* base_path = "maps/";
            char* path = (char*)malloc(sizeof(char)*(strlen(nombre_archivo)+strlen(base_path)+1)); 
            concat(path,strlen(nombre_archivo)+strlen(base_path)+1,base_path,(char*)nombre_archivo); //guarda el path del archivo a abrir
            
            //puts(path);
            
            FILE* archivo;
            archivo = fopen(path, "r");
            if (archivo == NULL){
                printf("error abriendo archivo: %s\n", nombre_archivo);
                return mapas;
            }

            for (int i = 0; i<5;i++){
                getline(&linea,&largoLin,archivo);

                //printf("%s\n",linea);

                token = strtok(linea, delimit);

                while (token != NULL){
                    //printf("%d %d %d\n",file_count,i,y_cas);
                    strncpy(mapas[file_count][i][y_cas].contenido,token,2);
                    //mapas[file_count][i][y_cas].contenido = token;
                    y_cas++;
                    //mapas[file_count][i][y_cas].contenido[1] = token[1];
                    //printf("%s\n",token);
                    token = strtok(NULL, delimit);
                }
                y_cas = 0;
                
                free(linea);
                linea=NULL;
            }
            file_count++;

        }
    }

/*
    for(int k = 0; k<num_tableros;k++){
        printf("mapa %d:\n",k);
        for (int i = 0; i<5;i++){
            for (int j = 0; j<5;j++){
                printf("%s ", mapas[k][i][j].contenido);
            }
            printf("\n");
        }
    }
*/

    closedir(directory);

    return mapas;
}


int main(){

    casilla*** maps;
    maps = loadMaps();

    for(int k = 0; k<9;k++){
        printf("mapa %d:\n",k);
        for (int i = 0; i<5;i++){
            for (int j = 0; j<5;j++){
                printf("%s ", maps[k][i][j].contenido);
            }
            printf("\n");
        }
    }

    free(maps);

    return 0;
}