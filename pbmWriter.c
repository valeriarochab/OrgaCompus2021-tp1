#include "pbmWriter.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_NUMBER "P1\n"

int pbmWriter_create(pbmwriter_t* self, char *filename, int N){
    self->file = fopen(filename, "w");
    if (self->file == NULL) {
        fprintf(stderr, "File %s not found\n", filename);
        return EXIT_FAILURE;
    }
    char firstRow[3] = MAGIC_NUMBER;

    fwrite(&firstRow, sizeof(char), 3, self->file);

    fprintf(self->file, "%d %d\n", N, N);

    return EXIT_SUCCESS;
}

int pbmWriter_write(pbmwriter_t* self, unsigned char *row, int N){
    return fwrite(&row, sizeof(char), N, self->file);
}

void pbmwriter_destroy(pbmwriter_t* self){
    if (self->file != NULL) {
        fclose(self->file);
    }
}
