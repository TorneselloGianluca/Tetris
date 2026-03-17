#include "field.h"
#include "shared.h"

uint8_t field[FIELD_HEIGHT][FIELD_WIDTH];

int score = 0;
int highScore = 0;
int linesCleared = 0;
volatile uint8_t pauseFlag = 1;
//volatile uint8_t hardDropFlag = 0;
volatile uint8_t gameOver = 0;
volatile uint8_t gameRunning = 0;

void initField(void){
	int i, j;
    for(i=0;i<FIELD_HEIGHT;i++)
        for(j=0;j<FIELD_WIDTH;j++)
            field[i][j]=0;
}

void clearField(void){
    initField();
    score=0;
    linesCleared=0;
}

uint8_t checkLineFull(int row){
	int i;
    for(i=0;i<FIELD_WIDTH;i++)
        if(!field[row][i]) return 0;
    return 1;
}

void removeFullLines(void){
    int i, j, k,lines=0;
    for(i=0;i<FIELD_HEIGHT;i++){
        if(checkLineFull(i)){
            lines++;
            for(k=i;k>0;k--)
                for(j=0;j<FIELD_WIDTH;j++)
                    field[k][j]=field[k-1][j];
            for(j=0;j<FIELD_WIDTH;j++) field[0][j]=0;
        }
    }
    linesCleared += lines;
    if(lines==1) score+=100;
    else if(lines==2) score+=200;
    else if(lines==3) score+=300;
    else if(lines>=4) score+=600;
    if(score>highScore) highScore=score;
}
