#ifndef PBMWRITER_H
#define PBMWRITER_H

#include <stdio.h>

typedef struct {
    FILE* file;
}pbmwriter_t;

int pbmWriter_create(pbmwriter_t* self, char *filename, int N);

int pbmWriter_write(pbmwriter_t* self, unsigned char *row, int N);

void pbmwriter_destroy(pbmwriter_t* self);

#endif //PBMWRITER_H