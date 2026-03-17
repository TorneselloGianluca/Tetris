#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "shared.h"

void LCD_Init_Tetris(void);
void LCD_Draw_Grid(void);
void LCD_Draw_Block(int row,int col,uint16_t color);
void LCD_Refresh_Score(int score,int top,int lines);
void LCD_Display_State(uint8_t gameOver, uint8_t pauseFlag);
void tetris_render(void);


#endif
