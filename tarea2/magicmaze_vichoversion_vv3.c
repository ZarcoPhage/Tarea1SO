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
                    

                    y_cas++;

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


    closedir(directory);

    return mapas;
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

    // MAP GENERATION SEGMENT
    map* maps;

    int** tps;


    int num;
    char choose;
    int j1[4];
    int max_turn = 8;
    tps_descubiertos tps_des;
    for (int i = 0; i<9 ; i++){
        for (int j = 0; j<3; j++){
            tps_des.posis[i][j] = -1;
        }
    }
    tps_des.count = 0;


    j1[0] = 0;
    j1[1] = 1;
    j1[2] = 1;
    j1[3] = 4;



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

    for (int i = 0; i < max_turn; i++){

        printf("\nTurn %d \nEnter your next movement: \n", i);
        scanf(" %c", &choose);

        if (choose == 'X') return 0;

        else if (choose == 'M')
        {
            printf("\nEnter direccion: \n");
            scanf("%d", &num);
            changeDirection(j1, num);
            printf("Enter movement: \n");
            scanf("%d", &num);
            move_in_map(maps, j1, num, &max_turn, "J1", &tps_des);
            if (j1[0]< 0 || j1[0] > 3 ){
                i--;
                printf("you need to re do the turn.\n");
        }
        for(int i = 0; i < 5; i++){
            for(int j = 0;  j < 5 ; j++){
            printf("%s ", maps[j1[3]].mapa[i][j].contenido);
            }
        printf("\n");
        }
    }

        else if (choose == 'E') {
            explore(maps, j1);
        }
        else if (choose == 'O') {
            open(maps, j1);
        }

        else {
            printf(" re do your turn \n");
            i--;
        }


    }






    free(maps);

    return 0;
}