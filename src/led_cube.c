#include "led_cube.h"
#include "libopencm3/stm32/usart.h"
#include "utils.h"

void drawer(int ledArray[MAX_SNAKE_LENGTH+1][COORD_LENGTH]) {
    usart_send_blocking(USART1, 0xF2);

    for (int z = 1; z < 9; z++) {
        for (int y = 1; y < 9; y++) {
            uint16_t temp = 0x00;

            for (int count = 0; count < MAX_SNAKE_LENGTH+1; count++) {
                if (ledArray[count][1] == y &&
                    ledArray[count][2] == z) {
                    temp += power(2, ledArray[count][0] - 1);
                }
            }

            usart_send_blocking(USART1, temp);
        }
    }
}