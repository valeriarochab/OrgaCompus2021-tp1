#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include "pbmWriter.h"
#include "proximo.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int option = 0;
    int must_return = 0;
    char prefix[50] = {0};

    static struct option long_options[] = {
        {"version", no_argument, 0, 'V'},
        {"help", no_argument, 0, 'h'},
    };

    int long_index = 0;
    while ((option = getopt_long(argc, argv, "Vho:", long_options, &long_index)) != -1) {
        if (must_return) {
            show_error("Parametros invalidos");
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
    unsigned char rule;
    unsigned long N;
    char *input_filename = NULL;
    if (optind + 3 == argc) {
        int rule_aux = atoi(argv[optind++]);
        N = atoi(argv[optind++]);
        input_filename = argv[optind++];
        if ((rule_aux > 255 || rule_aux < 0) || (N > UINT_MAX || N < 3)) {
            show_error("Parametros invalidos");
            return EXIT_FAILURE;
        }    
        rule = (unsigned char) rule_aux;
    } else {
        return EXIT_FAILURE;
    }

    pbmwriter_t pbm_writer;
    pbmWriter_create(&pbm_writer, strlen(prefix) > 0 ? prefix : input_filename, N);

    unsigned char *matriz = calloc( N * N, sizeof(unsigned char));
    if (read_file(matriz, input_filename, N) == 0) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                printf("%u", matriz[(i * N) + j]);
                if (i != N-1) {
                    matriz[((i + 1) * N) + j] = proximo(matriz, i, j, rule, N);
                }   
            }
            pbmWriter_write(&pbm_writer, &matriz[i * N], N);
            printf("\n");
        }
    }
    free(matriz);
    pbmwriter_destroy(&pbm_writer);
    return EXIT_SUCCESS;
}