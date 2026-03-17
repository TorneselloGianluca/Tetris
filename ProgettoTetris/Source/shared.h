#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>

/* FIELD DIMENSIONS */
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define BLOCK_SIZE 10
#define ROWS FIELD_HEIGHT
#define COLS FIELD_WIDTH
#define FIELD_X_OFF 10
#define FIELD_Y_OFF 10

/* GAME VARIABLES */
extern uint8_t field[FIELD_HEIGHT][FIELD_WIDTH];
extern int score;
extern int highScore;
extern int linesCleared;

extern volatile uint8_t pauseFlag;
extern volatile uint8_t gameOver;
extern volatile uint8_t nextInput;



//extern volatile int lastGameOver;
//extern volatile int lastPauseFlag;

/* CURRENT PIECE STRUCT */
typedef struct {
    int x;
    int y;
    int shape;
    int rotation;
} Tetramino;

extern Tetramino current;

#endif
