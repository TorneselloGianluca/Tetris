/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons and manage the bouncing effect
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect. 	
  * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include <stdlib.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "timer/timer.h"
#include "GLCD/GLCD.h" 
#include "joystick/joystick.h"
#include "../shared.h"
#include "TETRIS/field.h"
#include "TETRIS/tetromino.h"
#include "TETRIS/tetris_render.h"
#include "adc/adc.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
	SystemInit();
  LED_init();	
  LCD_Initialization();
  initField();
	LCD_Init_Tetris();
	BUTTON_init();
	joystick_init();
	ADC_init();              
  ADC_start_conversion();  
 

  pauseFlag = 1;       // start in pausa
	gameOver = 0;
  currentSpawned = 0;  // forza spawn al primo KEY1
 
	

  uint32_t prescaler = 2499; 
  uint32_t match = 499;     
  init_timer(0, prescaler, 0, 3, match); 
  enable_timer(0);
	
	init_random_seed();
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
		
  }

}

