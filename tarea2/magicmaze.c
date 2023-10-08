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

typedef struct {
    casilla** mapa;
    struct map* norte;
    struct map* sur;
    struct map* izq;
    struct map* der;
} map;

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

map* loadMaps(int** tps_list){
    int num_tableros = 9; //numero de tableros a procesar

    DIR* directory = opendir("./maps"); //directorio con los tableros
    struct dirent* entrada;
    
    //mapa->tablero->lineas->casillas/fichas

    map* mapas;
    
    mapas = (map*)malloc(num_tableros*sizeof(map));
    
    for (int i = 0; i<num_tableros; i++){
        mapas[i].mapa = (casilla**)malloc(5*sizeof(casilla*));
        mapas[i].norte = NULL;
        mapas[i].sur = NULL;
        mapas[i].izq = NULL;
        mapas[i].der = NULL;
        for (int j = 0; j<5;j++){
            mapas[i].mapa[j] = (casilla*)malloc(5*sizeof(casilla));
            for (int k = 0; k<5;k++){
                mapas[i].mapa[j][k].contenido = (char*)malloc(2*sizeof(char));
                //mapas[i][j][k].contenido[0] = '0';
                //mapas[i][j][k].contenido[1] = '0';
            }
        }
    }

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
    int prob1, prob2;
    int tesoro, especial; //ints pero que son tratados como booleanos para marcar cuando aparezca un tesoro o especial
    int tesoro_count = 4;
    int probT, probEsp;

    int tps_index = 0;
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
            
            probT = rand()%100;
            if (probT > 50){
                tesoro = 1;
            }

            for (int i = 0; i<5;i++){
                getline(&linea,&largoLin,archivo);

    

                //printf("%s\n",linea);

                token = strtok(linea, delimit);

                srand (time(NULL));

                while (token != NULL){

                    prob1 = rand() % 100; //probabilidad casillas especiales
                    prob2 = rand() % 100; //prob tesoro
                    probEsp = rand() %100;
                    printf("probs: %d %d %d",prob1, prob2, probEsp);

                    if (strncmp(token,"0",2) == 0 ){
                        if ((probEsp < 25)&&(especial == 0) && (file_count != 0) ){
                            if (prob1 < 25){
                                token = "Bc";
                            }
                            if ((prob1 > 25)&&(prob1 < 50)){
                                token = "Bt";
                            }
                            if ((prob1 > 50)&&(prob1 < 75)){
                                token = "Bn";
                            }
                            if (prob1 > 75){
                                token = "TP";
                                tps_list[tps_index][0] = file_count;
                                tps_list[tps_index][1] = i;
                                tps_list[tps_index][2] = y_cas;
                                tps_index++;
                            }

                            especial = 1;
                        }
                        if ((prob2 < 25) && (tesoro == 0) && (file_count != 0) && (tesoro_count > 0)){
                            switch (tesoro_count){
                                case 1:
                                    token = "T1";
                                    break;
                                case 2:
                                    token = "T2";
                                    break;
                                case 3:
                                    token = "T3";
                                    break;
                                case 4:
                                    token = "T4";
                                    break;
                            }
                            tesoro = 1;
                            tesoro_count--;
                        }

                        strncpy(mapas[file_count].mapa[i][y_cas].contenido,token,2);    
                    }
                    if (strncmp(token,"0\r",2)==0){
                        token = "0";
                        if ((probEsp < 25)&&(especial == 0) && (file_count != 0) ){
                            if (prob1 < 25){
                                token = "Bc";
                            }
                            if ((prob1 > 25)&&(prob1 < 50)){
                                token = "Bt";
                            }
                            if ((prob1 > 50)&&(prob1 < 75)){
                                token = "Bn";
                            }
                            if (prob1 > 75){
                                token = "TP";
                                tps_list[tps_index][0] = file_count;
                                tps_list[tps_index][1] = i;
                                tps_list[tps_index][2] = y_cas;
                                tps_index++;
                            }

                            especial = 1;
                        }
                        if ((prob2 < 25) && (tesoro == 0) && (file_count != 0) && (tesoro_count > 0)){
                            switch (tesoro_count){
                                case 1:
                                    token = "T1";
                                    break;
                                case 2:
                                    token = "T2";
                                    break;
                                case 3:
                                    token = "T3";
                                    break;
                                case 4:
                                    token = "T4";
                                    break;
                            }
                            
                            tesoro = 1;
                            tesoro_count--;
                        }
                        strncpy(mapas[file_count].mapa[i][y_cas].contenido,token,2);   
                    }
                    if (strncmp(token,"B\r",2)==0){
                        token = "B";
                        strncpy(mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"/\r",2)==0){
                        token = "/";
                        strncpy(mapas[file_count].mapa[i][y_cas].contenido,token,2);   
                    }else{
                        strncpy(mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    
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
            tesoro = 0;
            especial = 0;
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

    // MAP GENERATION SEGMENT
    map* maps;
    int** tps;

    tps = (int**)malloc(8*sizeof(int*));
    for (int i = 0; i < 8;i++){
        tps[i] = (int*)malloc(3*sizeof(int));
    }

    maps = loadMaps(tps);

    for (int i = 0;i < 8;i++){
        printf("%d %d %d\n", tps[i][0], tps[i][1], tps[i][2]);
    }

    for(int k = 0; k<9;k++){
        printf("mapa %d:\n",k);
        for (int i = 0; i<5;i++){
            for (int j = 0; j<5;j++){
                printf("%s ", maps[k].mapa[i][j].contenido);
            }
            printf("\n");
        }
    }

    //PROCESS GENERATION
    int inMapa[2];
    int outMapa[2];
    int j2[2];
    int j3[2];
    int j4[2];
    pid_t map_ppid;
    pid_t j1,j2,j3,j4;

    j1 = fork();

    if (j1 != 0){

        map_ppid = ppid();
        j2 = fork();

    }

    free(maps);

    return 0;
}