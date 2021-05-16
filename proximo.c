/*Devuelve el valor que va tener la celda[i + 1, j] */
unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N) {
    unsigned char left_neighbour = a[(i * N) + N -1];
    unsigned char right_neighbour = a[(i * N) + 0];
    //obtener vecino izq y derecho;
    if (j > 0) {
        left_neighbour =  a[(i * N) + j - 1];
    }
    if (j < N - 1) {
        right_neighbour = a[(i * N) + j + 1];
    }
    unsigned char binary_position = ((left_neighbour << 2) | a[(i * N) + j] << 1 | right_neighbour);
    return (regla >> (int)binary_position) & 1;
}