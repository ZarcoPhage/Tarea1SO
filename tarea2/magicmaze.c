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
    int posis[9][3];
    int count;
} tps_descubiertos;

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
    int id_accion; //1 para buscar, 2 para explorar, 3 para mover
    int cantidad_x; //0 si hace accion
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

    for (int i = 0; i<4;i++){
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
                        //printf("jug1 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[0].posX = y_cas;
                        game->jugadores[0].posY = i;
                        game->jugadores[0].posZ = file_count;
                        //printf("pos jug: %d %d %d \n",game->jugadores[0].posX,game->jugadores[0].posY,game->jugadores[0].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J2",2) == 0){
                        //printf("jug2 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[1].posX = y_cas;
                        game->jugadores[1].posY = i;
                        game->jugadores[1].posZ = file_count;
                        //printf("pos jug: %d %d %d \n",game->jugadores[1].posX,game->jugadores[1].posY,game->jugadores[1].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J3",2) == 0){
                        //printf("jug3 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[2].posX = y_cas;
                        game->jugadores[2].posY = i;
                        game->jugadores[2].posZ = file_count;
                        //printf("pos jug: %d %d %d \n",game->jugadores[2].posX,game->jugadores[2].posY,game->jugadores[2].posZ);
                        strncpy(game->mapas[file_count].mapa[i][y_cas].contenido,token,2);
                    }
                    if (strncmp(token,"J4",2) == 0){
                        //printf("jug4 encontrado en: %d %d %d",y_cas,i,file_count);
                        game->jugadores[3].posX = y_cas;
                        game->jugadores[3].posY = i;
                        game->jugadores[3].posZ = file_count;
                        //printf("pos jug: %d %d %d \n",game->jugadores[3].posX,game->jugadores[3].posY,game->jugadores[3].posZ);
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

void copy(int* a, int* b){
    for (int i = 0; i<4 ; i++){
        b[i] = a[i];
    }
    return;
}

map* insert(map* line, int* t, char* c){
    int x = t[1];
    int y = t[2];
    int z = t[3];

    strcpy(line[z].mapa[y][x].contenido, c );
    printf("flag de contenido cambiado = %s \n ", line[z].mapa[y][x].contenido);

    return line;

}


int* move(int* a){
    switch (a[0])
    {
    case 0:
        a[1]= a[1]+1;
        break;
    
    case 1:
        a[2]= a[2]+1;
        break;
    
    case 2:
        a[1]= a[1]-1;
        break;
    
    default:
        a[2]= a[2]-1;
        break;
    }

    return a;
}

int check(map* m, int* t){
    if(t[1]>=5 || t[1] < 0 || t[2] < 0 || t[2] >= 5){
        return 1;
    }
    if (!(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "/")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "E")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "B")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "J1")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "J2")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "J3")) || !(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "J4"))){
        printf("Chocaste %s \n", m[t[3]].mapa[t[2]][t[1]].contenido);
        return 1;
    }
    return 0;
}
//tp cambiada
void tp(map* m, tps_descubiertos* tps, int* t){
    tps_descubiertos buffer;
    printf("Mine 1\n");
    for (int i =0; i<3; i++){
        buffer.posis[0][i] = t[i+1];
        printf("buffer %d", t[i+1]);
    }

    if (tps->count == 0){
        printf("Mine 2\n");
        tps->count = 1;
        tps->posis[0][0] = buffer.posis[0][0];
        tps->posis[0][1] = buffer.posis[0][1];
        tps->posis[0][2] = buffer.posis[0][2];
        
        return;
    }
    else if (tps->count == 1 && (tps->posis[0][0] == buffer.posis[0][0]) && (tps->posis[0][1] == buffer.posis[0][1]) && (tps->posis[0][2] == buffer.posis[0][2] ))
    {
        return;
    }
    
    else{
        int flags = 0;
        for(int i = 0; i<tps->count; i++){
            printf("antes de la flag %d, %d, %d\n",buffer.posis[0][0], buffer.posis[0][1], buffer.posis[0][2]);
            printf("antes de la flag %d, %d, %d\n",tps->posis[i][0], tps->posis[i][1], tps->posis[i][2]);
            if((tps->posis[i][0] == buffer.posis[0][0]) && (tps->posis[i][1] == buffer.posis[0][1]) && (tps->posis[i][2] == buffer.posis[0][2] )){
                printf("Hello \n");
                flags = 1;
            }

            if (flags) {
                for (int j=0 ; j<3 ; j++){
                    if(i == 0){
                        printf("En el if %d\n", i);
                        t[j+1] = tps->posis[tps->count-1][j];
                    }

                    else t[j+1] = tps->posis[i-1][j];
                }
                printf("Tp viejo \n");
                return ;
            }
            else if (i==tps->count-1)
             {
                printf("mine 4, nuevo Tp\n");
                
                tps->posis[tps->count][0] = buffer.posis[0][0];
                tps->posis[tps->count][1] = buffer.posis[0][1];
                tps->posis[tps->count][2] = buffer.posis[0][2];
                tps->count = tps->count + 1;
                printf("%d\n", tps->count);
                return ;
                i = tps->count;
            }
        }

        return;
    }
 

}
//Check_sp Cambiada
void check_sp(map* m, int* t, int* turn, tps_descubiertos* tps){
    if (!(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "Bt"))){
        *turn= *turn +5;
        printf("+ 5 turnos\nTienes %d turnos maximos\n", *turn);
        return ;
    }
    if (!(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "Bn"))){
        *turn = *turn -3;
        printf("- 3 turnos\nTienes %d turnos maximos\n", *turn);
        return ;
    }
    if (!(strcmp(m[t[3]].mapa[t[2]][t[1]].contenido,  "TP"))){
        tp(m, tps, t);
        for (int i = 0; i< tps->count; i++){
            printf("tp :%d -> %d %d %d\n", i, tps->posis[i][0],tps->posis[i][1],tps->posis[i][2]);
        }
        return ;
    }
    return ;
}



int* changeDirection(int* t, int d){
    t[0] = d;
    return t; 

}
//visual Cambiada
void visual(map* line, int* t, int* save, char* c, tps_descubiertos* tps){

    insert(line, save, "0");
    for (int i = 0; i<tps->count ; i++){
        if(strcmp(line[tps->posis[i][2]].mapa[tps->posis[i][1]][tps->posis[i][0]].contenido,"J1") || strcmp(line[tps->posis[i][2]].mapa[tps->posis[i][1]][tps->posis[i][0]].contenido,"J2") || strcmp(line[tps->posis[i][2]].mapa[tps->posis[i][1]][tps->posis[i][0]].contenido,"J3") || strcmp(line[tps->posis[i][2]].mapa[tps->posis[i][1]][tps->posis[i][0]].contenido,"J4"))
        strcpy(line[tps->posis[i][2]].mapa[tps->posis[i][1]][tps->posis[i][0]].contenido,"TP");
    }
    insert(line, t, c);

}

int* move_in_map(map* m, int* t, int d, int* max_turn, char* jugador, tps_descubiertos* tps){
    int save[4];
    copy(t, save);


    if (t[0]> 3 || t[0]<0) return t;
    for (int i = 0; i<d; i++){
        move(t);
        if (check(m,t) || d == 0){
            copy(save, t);
            t[0] = 4;
            return t;
        }
        check_sp(m, t , max_turn, tps);
        printf("mine 5 %d %d %d\n", t[1], t[2],t[3]);

        
    }
    visual(m, t, save, jugador, tps);    

    return t;

}

map* explore(map* m, int* t){
    int buffer[4];
    copy(t, buffer);
    move(buffer);
    if (!(strcmp(m[t[3]].mapa[buffer[2]][buffer[1]].contenido,  "B"))){
        insert(m, buffer, "C");
        return m;
    }
    printf("No puedes explorar aqui\n");
    return m;
}

map* open(map* m, int* t){
    int buffer[4];
    copy(t, buffer);
    move(buffer);
    if (!(strcmp(m[t[3]].mapa[buffer[2]][buffer[1]].contenido,  "E"))){
        insert(m, buffer, "C");
        return m;
    }
    printf("No puedes abrir aqui\n");
    return m;
}

int main(){
    juego game;

    // MAP GENERATION SEGMENT
    //map* maps;
    int** tps;

    tps = (int**)malloc(8*sizeof(int*));
    for (int i = 0; i < 8;i++){
        tps[i] = (int*)malloc(3*sizeof(int));
        tps[i][0] = 666;
        tps[i][1] = 666;
        tps[i][2] = 666;
    }

    loadMaps(&game,tps);

    tps_descubiertos tps_des;
    for (int i = 0; i<9 ; i++){
        for (int j = 0; j<3; j++){
            tps_des.posis[i][j] = -1;
        }
    }
    tps_des.count = 0;

    /*
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
    }*/

    int rounds = 15;

    //PROCESS GENERATION
    int inMap[2];
    int outMap[2];
    int pj1[2]; // escritura de hijos a padre
    int pj2[2];
    int pj3[2];
    int pj4[2];
    
    if(pipe(inMap) == -1 || pipe(outMap) == -1 || pipe(pj1) == -1 || pipe(pj2) == -1 || pipe(pj3) == -1 || pipe(pj4) == -1){
        printf("Error creating pipes ph \n");
        return -1;
    }

    pid_t map_ppid;
    pid_t pidj1,pidj2,pidj3,pidj4;
    int num_act, id_dir, cant_desp = 0;
    accion act;
    map_ppid = getpid();
    jugador auxJ;
    jugador* rollback;

    rollback = (jugador*)malloc(4*sizeof(jugador));
    //printf("map %d",map_ppid);

    puts("Bienvenido a magic maze!");

    printf("%d %d %d %d\n", game.jugadores[0].rol,game.jugadores[1].rol,game.jugadores[2].rol,game.jugadores[3].rol);

    for (int i = 0; i<rounds; i++){
        printf("RONDA %d\n",i+1);
        for (int z = 0; z<4; <++){
            rollback.jugadores[z].posX = game.jugadores[k].posX;
            rollback.jugadores[z].posY = game.jugadores[k].posY;
            rollback.jugadores[z].posZ = game.jugadores[k].posZ;
        }
        
        for (int k = 0; k<4;k++){
            auxJ.posX = game.jugadores[k].posX;
            auxJ.posY = game.jugadores[k].posY;
            auxJ.posZ = game.jugadores[k].posZ;
            auxJ.rol = 0;
                //close(outMap[0]);
            write(outMap[1],&auxJ,sizeof(jugador));
                //close(outMap[1]);
        }
        
        pidj1 = fork();
        if (pidj1==0){
            if (game.jugadores[0].rol == 1){ //rol buscar
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J1, posicion: mapa %d x:%d y:%d\n acciones:\n 1) buscar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;

                close(pj1[0]);
                write(pj1[1],&act,sizeof(accion));
                close(pj1[0]);
                
            }
            if (game.jugadores[0].rol == 2){ //rol explore
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J1, posicion actual: mapa %d x:%d y:%d\n acciones:\n 1) Explorar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj1[0]);
                write(pj1[1],&act,sizeof(accion));
                close(pj1[0]);
            }

            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
            close(pj1[1]);
            read(pj1[0],&act,sizeof(accion));
            printf("received: %d %d %d\n",act.id_accion, act.cantidad_x, act.direccion);
        }
        pidj2 = fork();
        if (pidj2==0){
            if (game.jugadores[1].rol == 1){ //rol buscar
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J2, posicion: mapa %d x:%d y:%d\n acciones:\n 1) buscar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj2[0]);
                write(pj2[1],&act,sizeof(accion));
                close(pj2[1]);
            }
            if (game.jugadores[1].rol == 2){ //rol explore
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J2, posicion: mapa %d x:%d y:%d\n acciones:\n 1) Explorar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj2[0]);
                write(pj2[1],&act,sizeof(accion));
                close(pj2[1]);
            }
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
            close(pj2[1]);
            read(pj2[0],&act,sizeof(accion));
            close(pj2[0]);
            printf("received: %d %d %d\n",act.id_accion, act.cantidad_x, act.direccion);
        }
        pidj3 = fork();
        if (pidj3==0){
            if (game.jugadores[2].rol == 1){ //rol buscar
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J3, posicion: mapa %d x:%d y:%d\n acciones:\n 1) buscar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj3[0]);
                write(pj3[1],&act,sizeof(accion));
                close(pj3[1]);
            }
            if (game.jugadores[2].rol == 2){ //rol explore
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J3, posicion: mapa %d x:%d y:%d\n acciones:\n 1) Explorar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj3[0]);
                write(pj3[1],&act,sizeof(accion));
                close(pj3[1]);
            }
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
            
        }else{
            wait();
            close(pj3[1]);
            read(pj3[0],&act,sizeof(accion));
            close(pj3[0]);
            printf("received: %d %d %d\n",act.id_accion, act.cantidad_x, act.direccion);
        }
        pidj4 = fork();
        if (pidj4==0){
            if (game.jugadores[3].rol == 1){ //rol buscar
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J4, posicion: mapa %d x:%d y:%d\n acciones:\n 1) buscar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj4[0]);
                write(pj4[1],&act,sizeof(accion));
                close(pj4[1]);
            }
            if (game.jugadores[3].rol == 2){ //rol explore
                read(outMap[0],&auxJ,sizeof(jugador));
                printf("TURNO J4, posicion: mapa %d x:%d y:%d\n acciones:\n 1) Explorar 2) moverse\n INGRESA TU ACCION: ",auxJ.posZ,auxJ.posX,auxJ.posY);
                scanf("%d", &num_act);
                printf("Puedes realizar esta accion en alguna direccion\n 1) arriba \n 2) abajo \n 3) izquierda \n 4) derecha \n INGRESA TU DIRECCIÓN: ");
                scanf("%d", &id_dir);
                if (num_act == 1){
                    cant_desp = 0;
                }else{
                    printf("cuantas casillas deseas moverte?\n INGRESE NUMERO: ");
                    scanf("%d",&cant_desp);
                }
                act.id_accion = num_act;
                act.cantidad_x = cant_desp;
                act.direccion = id_dir;
                close(pj4[0]);
                write(pj4[1],&act,sizeof(accion));
                close(pj4[1]);
            }
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
        }else{
            wait();
            close(pj4[1]);
            read(pj4[0],&act,sizeof(accion));
            close(pj4[1]);
            printf("received: %d %d %d\n",act.id_accion, act.cantidad_x, act.direccion);
        }
    }

    printf("%d -> %d\n", getppid(),getpid());
    
    return 0;
}