#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
//#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>

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

typedef struct {
    int id_accion;
    int cantidad_x;
    int direccion;
} accion;

typedef struct {
    int posX;
    int posY;
    int posZ;
    int rol;
} jugador;


typedef struct{
    jugador* jugadores;
    map* mapas;
    int tes_recol;
} juego;
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

void loadMaps(juego* game, int** tps_list){
    srand (time(NULL));
    game->jugadores = (jugador*)malloc(4*sizeof(jugador));

    int probRol;

    for (int i = 0; i<3;i++){
        probRol = rand()%100;
        if (probRol<50){ // IDROL 1 ES BUSCAR, IDROL 2 ES ESCALERAS
            game->jugadores[i].rol = 1;
        } else{
            game->jugadores[i].rol = 2;
        }
    }

    game->tes_recol = 0;

    int num_tableros = 9; //numero de tableros a procesar

    DIR* directory = opendir("./maps"); //directorio con los tableros
    struct dirent* entrada;
    
    //mapa->tablero->lineas->casillas/fichas

    //map* mapas;
    
    game->mapas = (map*)malloc(num_tableros*sizeof(map));
    
    for (int i = 0; i<num_tableros; i++){
        game->mapas[i].mapa = (casilla**)malloc(5*sizeof(casilla*));
        game->mapas[i].norte = NULL;
        game->mapas[i].sur = NULL;
        game->mapas[i].izq = NULL;
        game->mapas[i].der = NULL;
        for (int j = 0; j<5;j++){
            game->mapas[i].mapa[j] = (casilla*)malloc(5*sizeof(casilla));
            for (int k = 0; k<5;k++){
                game->mapas[i].mapa[j][k].contenido = (char*)malloc(2*sizeof(char));
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
                return;
            }
            
            probT = rand()%100;
            if (probT > 50){
                tesoro = 1;
            }

            for (int i = 0; i<5;i++){
                getline(&linea,&largoLin,archivo);

    

                //printf("%s\n",linea);

                token = strtok(linea, delimit);

                while (token != NULL){

                    prob1 = rand() % 100; //probabilidad casillas especiales
                    prob2 = rand() % 100; //prob tesoro
                    probEsp = rand() %100;
                    //printf("probs: %d %d %d",prob1, prob2, probEsp);

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

                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);    
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
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);   
                    }
                    if (strncmp(token,"B\r",2)==0){
                        token = "B";
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"/\r",2)==0){
                        token = "/";
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);   
                    }

                    if (strncmp(token,"J1",2) == 0){
                        printf("jug1 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[0].posX = y_cas;
                        game->jugadores[0].posY = i;
                        game->jugadores[0].posZ = file_count;
                        printf("pos jug: %d %d %d \n",game->jugadores[0].posX,game->jugadores[0].posY,game->jugadores[0].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J2",2) == 0){
                        printf("jug2 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[1].posX = y_cas;
                        game->jugadores[1].posY = i;
                        game->jugadores[1].posZ = file_count;
                        printf("pos jug: %d %d %d \n",game->jugadores[1].posX,game->jugadores[1].posY,game->jugadores[1].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J3",2) == 0){
                        printf("jug3 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[2].posX = y_cas;
                        game->jugadores[2].posY = i;
                        game->jugadores[2].posZ = file_count;
                        printf("pos jug: %d %d %d \n",game->jugadores[2].posX,game->jugadores[2].posY,game->jugadores[2].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J4",2) == 0){
                        printf("jug4 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[3].posX = y_cas;
                        game->jugadores[3].posY = i;
                        game->jugadores[3].posZ = file_count;
                        printf("pos jug: %d %d %d \n",game->jugadores[3].posX,game->jugadores[3].posY,game->jugadores[3].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    else{
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
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

    return;
}

int main(){
    juego game;

    // MAP GENERATION SEGMENT
    //map* maps;
    int** tps;

    tps = (int**)malloc(8*sizeof(int*));
    for (int i = 0; i < 8;i++){
        tps[i] = (int*)malloc(3*sizeof(int));
    }

    loadMaps(&game,tps);

    for (int i = 0;i < 8;i++){
        printf("%d %d %d\n", tps[i][0], tps[i][1], tps[i][2]);
    }

    for(int k = 0; k<9;k++){
        printf("mapa %d:\n",k);
        for (int i = 0; i<5;i++){
            for (int j = 0; j<5;j++){
                printf("%s ", game.mapas[k].mapa[i][j].contenido);
            }
            printf("\n");
        }
    }

    int rounds = 15;

    //PROCESS GENERATION
    int inMapa[2];
    int outMapa[2];
    int pj2[2];
    int pj3[2];
    int pj4[2];
    
    if(pipe(inMapa) == -1 || pipe(outMapa) == -1 || pipe(pj2) == -1 || pipe(pj3) == -1 || pipe(pj4) == -1){
        printf("Error creating pipes ph \n");
        return -1;
    }

    pid_t map_ppid;
    pid_t pidj1,pidj2,pidj3,pidj4;

    map_ppid = getpid();
    //printf("map %d",map_ppid);

    for (int i = 0; i<rounds; i++){
        pidj1 = fork();
        if (pidj1==0){
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
        }
        pidj2 = fork();
        if (pidj2==0){
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
        }
        pidj3 = fork();
        if (pidj3==0){
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
        }
        pidj4 = fork();
        if (pidj4==0){
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
        }else{
            wait();
        }
    }

    




    printf("%d -> %d\n", getppid(),getpid());
    
    return 0;
}