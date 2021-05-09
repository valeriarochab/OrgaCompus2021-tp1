#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

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

int main(int argc, char *argv[]) {
    int option = 0;
    int version = 0;
    int help = 0;
    int must_return = 0;
    char *prefix = NULL;

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
                prefix = calloc( strlen(optarg), sizeof(char));
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
        free(prefix);
        return EXIT_FAILURE;
    }

    
    free(prefix);
    return EXIT_SUCCESS;
}