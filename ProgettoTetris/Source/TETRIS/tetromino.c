#include "tetromino.h"
#include "field.h"
#include "shared.h"
#include "tetris_render.h"
#include <stdlib.h>

Tetramino current;
uint8_t currentSpawned = 0;
volatile uint8_t justSpawned = 1;

uint8_t tetraminos[7][4][4][4] = {
    // I
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
     {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}},
    // O
    {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
    // T
    {{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},  
     {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},
    // J
    {{{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},  
     {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}}
		},
    // L
    {{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},  
     {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}},
    // S
    {{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}},
    // Z
    {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}}
};


void spawnTetromino(void){
    current.shape = rand()%7;
    current.rotation = 0;
    current.y = 0;
    current.x = rand() % (FIELD_WIDTH - 4 + 1); 

    currentSpawned = 1;
    justSpawned = 1;
	
    if(checkCollision(current.x,current.y,current.rotation)){
        pauseFlag = 1;
        gameOver = 1;
        currentSpawned = 0;
			  LCD_Display_State(gameOver, pauseFlag);
        return;
    }
}

uint8_t checkCollision(int x,int y,int rotation){
	int i, j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(tetraminos[current.shape][rotation][i][j]){
                int fx=x+j;
                int fy=y+i;
                if(fx<0 || fx>=FIELD_WIDTH || fy<0 || fy>=FIELD_HEIGHT) return 1;
                if(field[fy][fx]) return 1;
            }
    return 0;
}

void lockTetromino(void){
	int i, j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(tetraminos[current.shape][current.rotation][i][j])
                field[current.y+i][current.x+j] = current.shape+1;
    score+=10;
    removeFullLines();
}


void moveDown(void){
    if(!checkCollision(current.x,current.y+1,current.rotation)){
        current.y++;
        justSpawned=0;
    } else {
        if(!justSpawned){
            lockTetromino();
            spawnTetromino();
        } else {
            // pezzo appena spawnato non può muoversi ? game over
            pauseFlag = 1;
            gameOver = 1;
            currentSpawned = 0;
					  LCD_Display_State(gameOver, pauseFlag);
        }
    }
}

void moveLeft(void){
    if(!checkCollision(current.x-1,current.y,current.rotation))
        current.x--;
}

void moveRight(void){
    if(!checkCollision(current.x+1,current.y,current.rotation))
        current.x++;
}

void rotateTetromino(void){
    int nextRot=(current.rotation+1)%4;
    if(!checkCollision(current.x,current.y,nextRot))
        current.rotation=nextRot;
}
