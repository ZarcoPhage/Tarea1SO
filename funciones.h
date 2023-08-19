#ifndef FUNCIONES_H_
#define FUNCIONES_H_

int s_horizontal(char *palabra, char **array, int tamano);

int s_vertical(char *palabra, char **array, int tamano);

int directory_initialization();

void concat(char* buffer, int buf_size, char* s1, char* s2);

int moveFile(const char* nombre_archivo, char* orientacion, int matrixSize);

void procesarTxt(const char* nombre_archivo);



#endif