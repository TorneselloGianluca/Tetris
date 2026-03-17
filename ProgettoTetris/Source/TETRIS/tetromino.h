#ifndef TETRAMINO_H 
#define TETRAMINO_H 

#include <stdint.h> 
#include "shared.h" 


extern volatile uint8_t justSpawned; 
extern uint8_t currentSpawned;
extern uint8_t tetraminos[7][4][4][4]; 

void moveDown(void); 
void moveLeft(void); 
void moveRight(void); 
void rotateTetromino(void); 
void spawnTetromino(void); 
void lockTetromino(void); 

uint8_t checkCollision(int x,int y,int rotation); 


#endif
