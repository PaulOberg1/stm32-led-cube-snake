#include "game.h"
#include "joystick.h"
#include "led_cube.h"
#include "utils.h"
#include "libopencm3/stm32/usart.h"

static int snakeLength = 2;
static int ledArray[MAX_SNAKE_LENGTH+1][COORD_LENGTH];

static void arrayReplace(int pos, int array[3]) {
    ledArray[pos][0] = array[0];
    ledArray[pos][1] = array[1];
    ledArray[pos][2] = array[2];
}

static void arraySum(int array[3]) {
    ledArray[0][0] = 1 + ((ledArray[0][0] + array[0] + 7) % 8);
    ledArray[0][1] = 1 + ((ledArray[0][1] + array[1] + 7) % 8);
    ledArray[0][2] = 1 + ((ledArray[0][2] + array[2] + 7) % 8);
}

static void addToSnake(void) {
    int temp[3] = {
        ledArray[snakeLength - 1][0] - ledArray[snakeLength - 2][0],
        ledArray[snakeLength - 1][1] - ledArray[snakeLength - 2][1],
        ledArray[snakeLength - 1][2] - ledArray[snakeLength - 2][2]
    };

    ledArray[snakeLength][0] = 1 + ((ledArray[snakeLength - 1][0] + temp[0] + 7) % 8);
    ledArray[snakeLength][1] = 1 + ((ledArray[snakeLength - 1][1] + temp[1] + 7) % 8);
    ledArray[snakeLength][2] = 1 + ((ledArray[snakeLength - 1][2] + temp[2] + 7) % 8);

    snakeLength++;
}

static void generateFood(void) {
    int inLedArray = 1;

    while (inLedArray) {
        inLedArray = 0;
        struct coord food = randomnumber();

        ledArray[MAX_SNAKE_LENGTH][0] = food.x;
        ledArray[MAX_SNAKE_LENGTH][1] = food.y;
        ledArray[MAX_SNAKE_LENGTH][2] = food.z;

        for (int x = 0; x < snakeLength; x++) {
            if (isEqual(ledArray[x], ledArray[MAX_SNAKE_LENGTH])) {
                inLedArray = 1;
            }
        }
    }
}

void game(void) {
    while (1) {
        int temp[3] = {4,4,4};
        arrayReplace(0, temp);

        temp[1] = 3;
        arrayReplace(1, temp);

        generateFood();

        int collision = 0;
        int directions[6][3] = {
            {0,-1,0},{0,1,0},{-1,0,0},
            {1,0,0},{0,0,1},{0,0,-1}
        };

        int direction = 0;

        while (!collision && snakeLength < MAX_SNAKE_LENGTH) {

            for (volatile unsigned int tmr=3e5; tmr > 0; tmr--);

            if (readJoystick(1) > 1.5) direction = 0;
            else if (readJoystick(1) < 0.5) direction = 1;
            else if (readJoystick(2) > 1.5) direction = 2;
            else if (readJoystick(2) < 0.5) direction = 3;
            else if (readJoystick(6) > 1.5) direction = 4;
            else if (readJoystick(6) < 0.5) direction = 5;

            for (int i = snakeLength-1; i > 0; i--) {
                arrayReplace(i, ledArray[i-1]);
            }

            arraySum(directions[direction]);

            if (isEqual(ledArray[0], ledArray[MAX_SNAKE_LENGTH])) {
                generateFood();
                addToSnake();
            }

            for (int i = 1; i < snakeLength; i++) {
                if (isEqual(ledArray[0], ledArray[i])) {
                    collision = 1;
                }
            }

            drawer(ledArray);
        }

        snakeLength = 2;

        for (int i = 0; i < MAX_SNAKE_LENGTH+1; i++) {
            ledArray[i][0] = 0;
            ledArray[i][1] = 0;
            ledArray[i][2] = 0;
        }
    }
}