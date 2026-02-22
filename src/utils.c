#include "utils.h"
#include <stdlib.h>

uint16_t power(int base, int exponent) {
    if (exponent < 0) return 0x00;

    int temp = 1;
    for (int i = 0; i < exponent; i++) {
        temp *= base;
    }
    return (uint16_t)temp;
}

struct coord randomnumber(void) {
    struct coord food;
    food.x = (rand() % CUBE_SIZE) + 1;
    food.y = (rand() % CUBE_SIZE) + 1;
    food.z = (rand() % CUBE_SIZE) + 1;
    return food;
}

int isEqual(int array1[3], int array2[3]) {
    return (array1[0]==array2[0] &&
            array1[1]==array2[1] &&
            array1[2]==array2[2]);
}