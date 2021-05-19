#include "pbmWriter.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_NUMBER "P1\n"

int pbmWriter_create(pbmwriter_t* self, char *filename, int N){
    
    self->file = fopen(strcat(filename, ".pbm"), "w");
    if (self->file == NULL) {
        fprintf(stderr, "No se pudo crear el archivo %s\n", filename);
        return EXIT_FAILURE;
    }
    char firstRow[3] = MAGIC_NUMBER;

    fwrite(&firstRow, sizeof(char), 3, self->file);

    fprintf(self->file, "%d %d\n", N, N);

    return EXIT_SUCCESS;
}

int pbmWriter_write(pbmwriter_t* self, unsigned char *row, int N){
    int counter = 0;
    for(int i = 0; i < N; ++i) {
        char pBit = row[i] | '0';
        counter += fwrite(&pBit, sizeof(char), 1, self->file);
    }

    if (counter == N) {
        fprintf(self->file, "\n");
    }
    return counter;
}

void pbmwriter_destroy(pbmwriter_t* self){
    if (self->file != NULL) {
        fclose(self->file);
    }
}
