#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int s_vertical(char *palabra, char **array, int tamano){
    int length = strlen(palabra)-1;
    //printf("length= %d, palabra = %s, tamano = %d\n", length, palabra, tamano);
    int alto= tamano;
    int ancho = alto*2 +1;
    int j =0;
    int i = 0;
    int k= 0;
    while (k<ancho){
        while (j<alto) {
            if (array[j][k]== palabra[i]){
                i++;
                if (i == length) {
                    //printf ("encontrado vertical, i = %d\n", i);
                    return 1;
                }
            }
            else { i = 0;}
            j++;
        }
        i=0;
        j = 0;
        k+=2;
    }
    //printf("no encontrado  \n");
    return 0;
};
int s_horizontal(char *palabra, char **array, int tamano){
    int length = strlen(palabra);
    //printf("length= %d, palabra = %s, tamano = %d\n", length, palabra, tamano);
    int alto= tamano;
    int ancho = alto*2 +1;
    int j =0;
    int i = 0;
    int k= 0;
    while (k<alto){
        while (j<ancho) {
            if (array[k][j]== palabra[i]){
                i++;
                if (i == length) {
                    //printf ("encontrado horizontal\n");
                    return 1;
                }
            }
            else { i = 0;}
            j+=2;
        }
        i=0;
        j = 0;
        k++;
    }
    //printf("no encontrado  \n");
    return 0;
};

int directory_initialization(){
    if ( (mkdir("./clasificacion", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
        //puts("error creando el directorio");
        return 0;
    }else{ 
        if ( (mkdir("./clasificacion/Vertical", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1 ){
            return 0;
        }else{
            if ( (mkdir("./clasificacion/Vertical/50x50", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1 ){
                return 0;                
            }
            if ((mkdir("./clasificacion/Vertical/100x100", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
                return 0;
            }
            if ((mkdir("./clasificacion/Vertical/200x200", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
                return 0;
            }
        }
        if ( (mkdir("./clasificacion/Horizontal", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
            return 0;
        }else{
            if ( (mkdir("./clasificacion/Horizontal/50x50", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1 ){
                return 0;                
            }
            if ((mkdir("./clasificacion/Horizontal/100x100", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
                return 0;
            }
            if ((mkdir("./clasificacion/Horizontal/200x200", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) == -1){
                return 0;
            }
        }
    }
    return 1;
}

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

int moveFile(const char* nombre_archivo, char* orientacion, int matrixSize){
    char* base_old_path = "./testCases/";
   
    int old_path_len = (int)strlen(base_old_path) + (int)strlen(nombre_archivo);
    char* old_path = (char*)malloc(sizeof(char)*old_path_len);

    concat(old_path, old_path_len, base_old_path, (char*)nombre_archivo);
    //printf("final size: %d\n", (int)strlen(old_path));

    int new_path_len;
    char* new_path;

    if ( (strncmp(orientacion, "vertical",2) == 0) || ((strncmp(orientacion, "Vertical",2)) == 0) ){
        //printf("mSiz: %d\n", matrixSize);
        switch (matrixSize){
            case 50:
                //puts("in 50");
                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Vertical/50x50/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Vertical/50x50/", (char*)nombre_archivo);
                break;
            case 100:
                //puts("in 100");
                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Vertical/100x100/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Vertical/100x100/", (char*)nombre_archivo);
                break;
            case 200:
                //puts("in 200");
                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Vertical/200x200/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Vertical/200x200/", (char*)nombre_archivo);
                break;
        }
    }else{
        switch (matrixSize){
            case 50:

                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Horizontal/50x50/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Horizontal/50x50/", (char*)nombre_archivo);
                break;
            case 100:
                
                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Horizontal/100x100/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Horizontal/100x100/", (char*)nombre_archivo);
                break;
            case 200:

                new_path_len = (int)strlen(nombre_archivo) + (int)strlen("./clasificacion/Horizontal/200x200/");
                new_path = (char*)malloc(sizeof(char)*new_path_len);
                concat(new_path, new_path_len, "./clasificacion/Horizontal/200x200/", (char*)nombre_archivo);
                break;
        }
    }

    const char* src = old_path;
    const char* dest = new_path;
    if (rename(src,dest) == -1){
        return 0;
    }
    free(old_path); free(new_path);
    return 1;
}

void procesarTxt(const char* nombre_archivo){
    char path[] = "testCases/";
    strcat(path,nombre_archivo);
    //puts(path);
    FILE* archivo;
    archivo = fopen(path, "r");
    if (archivo == NULL){
        printf("error abriendo archivo: %s\n", nombre_archivo);
        return;
    }
    char* orientacion = NULL;
    size_t largoOr = 0;
    //ssize_t leidosOr = 
    getline(&orientacion,&largoOr,archivo);
    /*
    if(leidosOr != -1){
        orientacion[leidosOr-1] = '\0';
        puts(orientacion);
    };*/
    //free(linea);
    char* fstLine = NULL;
    size_t largoFst = 0;
    ssize_t leidosFst = getline(&fstLine,&largoFst,archivo);
    /*
    if(leidosFst != -1){
        fstLine[leidosFst-1] = '\0';
        //puts(fstLine);
        //printf("%ld", leidosFst);
    };*/
    int matrixSize = (leidosFst - 1 )/2;


    char** matrix = (char**)malloc( (matrixSize*sizeof(char*) ));

    matrix[0] = (char*)malloc( (leidosFst*sizeof(char)) );

    strcpy(matrix[0],fstLine);
    //puts(matrix[0]);

    size_t largoLin = 0;
    //ssize_t leidosLin;
    
    for(int i = 1; i<matrixSize;i++){
        //leidosLin = 
        getline(&matrix[i],&largoLin,archivo);
        largoLin=0;
        //printf("%ld %s",leidosLin,matrix[i]);
        /*
        if (leidosLin == leidosFst){
            matrix[i][leidosLin-1] = '\0';
        }*/
        
        //matrix[i][leidosLin-1] = '\0';
        //printf("%ld", leidosLin);
        //puts(matrix[i]);
        //matrix[i] = (char*)malloc( ( matrixSize*sizeof(char) ) );
    }
    //printf("%s %d\n", nombre_archivo, (int)strlen(nombre_archivo));

    fclose(archivo);


    int dir_palabra = 0;
    if ((strncmp(orientacion, "horizontal",2)==0) || (strncmp( orientacion, "Horizontal",2)==0)){
        dir_palabra=1;
    }
    int largo_palabra= strlen(nombre_archivo)-4;
    char palabra[largo_palabra];
    int contador =0;
    while (contador <=largo_palabra){
        if(nombre_archivo[contador]== '.'){
            palabra[contador] = '\0';
            break;
        }
        palabra[contador] = toupper(nombre_archivo[contador]);
        contador++;
    }

    clock_t init_t, end_t;
    double exec_t;
    if (dir_palabra == 1){
        init_t = clock();
        printf("resultado horizontal = %d\n", s_horizontal(palabra,matrix,matrixSize));
        end_t = clock();
        exec_t = (double)(end_t - init_t) / CLOCKS_PER_SEC;
        printf("tiempo de ejecucion: %f\n", exec_t);
    }
    else{  
        init_t = clock();
        printf("resultado vertical= %d\n", s_vertical(palabra,matrix,matrixSize));
        end_t = clock();
        exec_t = (double)(end_t - init_t) / CLOCKS_PER_SEC;
        printf("tiempo de ejecucion: %f\n", exec_t);
    }

    //for(int i = 0; i<matrixSize;i++){
    //    puts(matrix[i]);
    //}

    if (moveFile(nombre_archivo,orientacion,matrixSize) == 0){
        puts("error clasificando archivo");
    }

    //segmento de liberacion de memoria
    for(int i = 0; i<matrixSize;i++){
        free(matrix[i]);
    }
    free(matrix);
    free(orientacion);
    free(fstLine);

}