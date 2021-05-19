#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.0.1"

void show_version() {
    printf("TP1 Version: %s\n", VERSION);
}

void show_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void show_help() {
    printf("Usage:\n");
    printf("\tautocel -h\n");
    printf("\tautocel -V\n");
    printf("\tautocel R N inputfile [-o outputprefix]\n");
    printf("Options\n");
    printf("\t-h --help\tImprime este mensaje.\n");
    printf("\t-V --version\tDa la versión del programa.\n");
    printf("\t-o \tPrefijo de los archivos de salida.\n");
    printf("Examples\n");
    printf("\n");
    printf("\tautcel 30 80 inicial -o evolucion\n");
    printf("\tCalcula la evolución del autómata \"Regla 30\",\n");
    printf("\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n");
    printf("\tEl archivo de salida se llamará evolucion.pbm.\n");
    printf("\tSi no se da un prefijo para los archivos de salida,\n");
    printf("\tel prefijo será el nombre del archivo de entrada.\n");
}


int read_file(unsigned char* matriz, char * fileName, unsigned int N) {
    int ret = EXIT_FAILURE;
    FILE *fp = fopen(fileName, "rb");
    if (is_valid_file(fp)) {
        unsigned char buffer;
        int counter = 0;
        while (fread(&buffer, sizeof(char), 1, fp) && counter < N) {
            if (buffer != '1' & buffer != '0') {
                show_error("El archivo no cumple con el formato");
                return ret;
            } 
            matriz[counter] = buffer - '0';
            counter++;      
        }
        if (feof(fp) && counter == N) {
            ret = EXIT_SUCCESS;
        } else {
            fprintf(stderr, "El archivo no contiene %d celdas\n", N);
        }
        fclose(fp);
    } else {
        fprintf(stderr, "No se pudo abrir el archivo %s o el mismo esta vacio\n", fileName);
    }
    return ret;
}

int is_valid_file(FILE *fp) {
    int size = 0;
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        rewind(fp);
    }
    return size;
}