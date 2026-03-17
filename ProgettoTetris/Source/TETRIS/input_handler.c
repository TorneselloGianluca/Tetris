#include "shared.h"
#include "tetromino.h"
#include "../RIT/RIT.h" 

void processInput(void) {
    switch(nextInput) {
        case 1: moveDown(); break;
        case 2: moveLeft(); break;
        case 3: rotateTetromino(); break;
        case 4: moveRight(); break;
    }
    nextInput = 0;  // resetta il flag
}
