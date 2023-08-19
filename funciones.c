#include <stdio.h>
#include <string.h>

int s_vertical(char *palabra, char **array, int tamano){
    int length = strlen(palabra)-1;
    printf("length= %d, palabra = %s, tamano = %d\n", length, palabra, tamano);
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
                    printf ("encontrado vertical, i = %d\n", i);
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
    printf("no encontrado  \n");
    return 0;
};
int s_horizontal(char *palabra, char **array, int tamano){
    int length = strlen(palabra);
    printf("length= %d, palabra = %s, tamano = %d\n", length, palabra, tamano);
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
                    printf ("encontrado horizontal\n");
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
    printf("no encontrado  \n");
    return 0;
};