#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int directory_initalization(){
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

void procesarTxt(const char* nombre_archivo){
    char path[] = "testCases/";
    strcat(path,nombre_archivo);
    puts(path);
    FILE* archivo;
    archivo = fopen(path, "r");
    if (archivo == NULL){
        printf("error abriendo archivo: %s\n", nombre_archivo);
        return;
    }else{
        puts("archivo abierto");
    }
    char* orientacion = NULL;
    size_t largoOr = 0;
    ssize_t leidosOr = getline(&orientacion,&largoOr,archivo);
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
    ssize_t leidosLin;
    
    for(int i = 1; i<matrixSize;i++){
        leidosLin = getline(&matrix[i],&largoLin,archivo);
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
    printf("%d\n", matrixSize);
    //for(int i = 0; i<matrixSize;i++){
    //    puts(matrix[i]);
    //}

    for(int i = 0; i<matrixSize;i++){
        free(matrix[i]);
    }

    free(matrix);

    fclose(archivo);
}

int main(){
    //realizar validacion de directorios
    //if (directory_initalization() == 0){
    //    puts("error creando directorios");
    //    return 0;
    //}
    
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
            puts("archivo procesado");
        
        }
    }

    closedir(directory);
    return 0;
}