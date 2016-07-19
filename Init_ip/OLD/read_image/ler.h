#ifndef _LER_H
#define _LER_H

#define IMAGE_FILE "/home/image.dat"
#define TRUE   0
#define FALSE -1

#define BUFFER 10

typedef char imagem[256];

int read_image(const char* filename, char linha[257], int n_linha);

#endif


