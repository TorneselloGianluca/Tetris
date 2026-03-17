#include "tetris_render.h"
#include "shared.h"
#include "tetromino.h"
#include "GLCD.h"
#include <string.h>
#include <stdio.h>

static Tetramino last_piece;
static uint8_t last_field[FIELD_HEIGHT][FIELD_WIDTH];
static uint8_t first_render = 1;
static uint16_t color_map[7] = {Cyan, Yellow, Magenta, Blue, Orange, Green, Red};

void LCD_Init_Tetris(void){
    LCD_Clear(Black);
    LCD_Draw_Grid();
    memset(last_field,0,sizeof(last_field));
    first_render=1;
    last_piece.x=-4;
    last_piece.y=-4;
    last_piece.shape=0;
    last_piece.rotation=0;
    LCD_Refresh_Score(score,highScore,linesCleared);
	  LCD_Display_State(gameOver, pauseFlag);
}

void LCD_Draw_Grid(void){
    LCD_DrawLine(FIELD_X_OFF-1,FIELD_Y_OFF-1,FIELD_X_OFF+COLS*BLOCK_SIZE,FIELD_Y_OFF-1,White);
    LCD_DrawLine(FIELD_X_OFF-1,FIELD_Y_OFF+ROWS*BLOCK_SIZE,FIELD_X_OFF+COLS*BLOCK_SIZE,FIELD_Y_OFF+ROWS*BLOCK_SIZE,White);
    LCD_DrawLine(FIELD_X_OFF-1,FIELD_Y_OFF-1,FIELD_X_OFF-1,FIELD_Y_OFF+ROWS*BLOCK_SIZE,White);
    LCD_DrawLine(FIELD_X_OFF+COLS*BLOCK_SIZE,FIELD_Y_OFF-1,FIELD_X_OFF+COLS*BLOCK_SIZE,FIELD_Y_OFF+ROWS*BLOCK_SIZE,White);
}

void draw_cell(int row,int col){
    uint16_t color=(field[row][col]!=0)?color_map[field[row][col]-1]:Black;
	  int i, j;
    for(i=1;i<BLOCK_SIZE-1;i++)
        for(j=1;j<BLOCK_SIZE-1;j++)
            LCD_SetPoint(FIELD_X_OFF+col*BLOCK_SIZE+i,FIELD_Y_OFF+row*BLOCK_SIZE+j,color);
}

void draw_piece(Tetramino piece,uint16_t color){
	  int i, j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(tetraminos[piece.shape][piece.rotation][i][j]){
                int rr=piece.y+i;
                int cc=piece.x+j;
                if(rr>=0 && rr<ROWS && cc>=0 && cc<COLS)
                    LCD_Draw_Block(rr,cc,color);
            }
}

void tetris_render(void){
    if(first_render){
        LCD_Draw_Grid();
        memset(last_field,0,sizeof(last_field));
        first_render=0;
    }
    // cancella pezzo precedente
		int i, j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(tetraminos[last_piece.shape][last_piece.rotation][i][j]){
                int rr=last_piece.y+i;
                int cc=last_piece.x+j;
                if(rr>=0 && rr<ROWS && cc>=0 && cc<COLS)
                    draw_cell(rr,cc);
            }
    // aggiorna campo
		int r, c;
    for(r=0;r<ROWS;r++)
        for(c=0;c<COLS;c++)
            if(field[r][c]!=last_field[r][c]){
                draw_cell(r,c);
                last_field[r][c]=field[r][c];
            }
    // disegna pezzo corrente
    draw_piece(current,color_map[current.shape]);
    last_piece=current;
    LCD_Refresh_Score(score,highScore,linesCleared);
						
}

void LCD_Draw_Block(int row,int col,uint16_t color){
	  int i, j;
    for(i=1;i<BLOCK_SIZE-1;i++)
        for(j=1;j<BLOCK_SIZE-1;j++)
            LCD_SetPoint(FIELD_X_OFF+col*BLOCK_SIZE+i,FIELD_Y_OFF+row*BLOCK_SIZE+j,color);
}

void LCD_Refresh_Score(int score,int top,int lines){
    char buf[16];
    int x_text=FIELD_X_OFF+COLS*BLOCK_SIZE+20;
    GUI_Text(x_text,20,(uint8_t*)"TOP",White,Black);
    sprintf(buf,"%06d",top);
    GUI_Text(x_text,40,(uint8_t*)buf,White,Black);
    GUI_Text(x_text,80,(uint8_t*)"SCORE",White,Black);
    sprintf(buf,"%06d",score);
    GUI_Text(x_text,100,(uint8_t*)buf,White,Black);
    GUI_Text(x_text,140,(uint8_t*)"LINES",White,Black);
    sprintf(buf,"%03d",lines);
    GUI_Text(x_text,160,(uint8_t*)buf,Red,Black);
    
}

void LCD_Display_State(uint8_t gameOver, uint8_t pauseFlag){
    int x_state = FIELD_X_OFF + COLS*BLOCK_SIZE/2 - 50;
    int y_state = FIELD_Y_OFF + ROWS*BLOCK_SIZE + 5;

    if(gameOver)
        GUI_Text(x_state, y_state, (uint8_t*)"GAME OVER", Red, Black);
    else if(pauseFlag)
        GUI_Text(x_state, y_state, (uint8_t*)"PAUSE", White, Black);
    else
        GUI_Text(x_state, y_state, (uint8_t*)"             ", Black, Black); // cancella solo se non pausa e non gameover
}






