#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "pbmWriter.h"
#include "proximo.h"

#define VERSION "0.0.1"

void show_version() {
    printf("TP1 Version: %s\n", VERSION);
}

void show_error(char *msg) {
    fprintf(stderr, "%s", msg);
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


int readFile(unsigned char* matriz, char * fileName, int N) {
    int ret = 1;
    FILE *fp = fopen(fileName, "rb");
    unsigned char buffer;
    int counter = 0;
    if (fp != NULL) {
        while (fread(&buffer, sizeof(char), 1, fp) && counter < N) {
            if (buffer != '1' & buffer != '0') {
                break;
            } 
            matriz[counter] = buffer - '0';
            counter++;      
        }
        if (feof(fp) && counter == N) {
            ret = 0;
        } else {
            fprintf(stderr, "El archivo no contiene %d celdas\n", N);
        }
        fclose(fp);
    } else {
        fprintf(stderr, "No se pudo abrir el archivo %s celdas\n", fileName);
    }
    return ret;
}

int main(int argc, char *argv[]) {
    int option = 0;
    int must_return = 0;
    char prefix[20];

    static struct option long_options[] = {
        {"version", no_argument, 0, 'V'},
        {"help", no_argument, 0, 'h'},
    };

    int long_index = 0;
    while ((option = getopt_long(argc, argv, "Vho:", long_options, &long_index)) != -1) {
        if (must_return) {
            show_error("Invalid parameters.");
            return 1;
        }

        switch (option) {
            case 'V':
                show_version();
                must_return = 1;
                break;
            case 'h':
                show_help();
                must_return = 1;
                break;
            case 'o':
                strncpy(prefix, optarg, strlen(optarg));
                break;
            case '?':
                must_return = 1;
                break;
            default:
                must_return = 1;
                break;
        }
    }

    if (must_return) {
        return EXIT_FAILURE;
    }
    int rule = (unsigned char) atoi(argv[1]);
    int N = atoi(argv[2]);

    pbmwriter_t pbmWriter;
    pbmWriter_create(&pbmWriter, argv[4], N);

    unsigned char *matriz = calloc( N * N, sizeof(unsigned char));
    if (readFile(matriz, argv[3], N) == 0) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                printf("%u", matriz[(i * N) + j]);
                if (i != N-1) {
                    matriz[((i + 1) * N) + j] = proximo(matriz, i, j, rule, N);
                }   
            }
            pbmWriter_write(&pbmWriter, &matriz[i * N], N);
            printf("\n");
        }
    }
    free(matriz);
    pbmwriter_destroy(&pbmWriter);
    return EXIT_SUCCESS;
}