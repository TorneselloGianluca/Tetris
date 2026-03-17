#include "LPC17xx.h"
#include "timer.h"
#include "shared.h"
#include "../TETRIS/tetromino.h"
#include "../TETRIS/field.h"
#include "../TETRIS/tetris_render.h"

#define DEBOUNCE_TICKS   2      // 2 * 50ms = 100ms
#define DROP_TICKS       10     // caduta normale ogni 500ms
#define SOFT_DROP_TICKS  2      // caduta soft ogni 100ms

static uint8_t key1_cnt = 0;
static uint8_t key2_cnt = 0;
static uint8_t drop_cnt = 0;
static uint8_t softDropCounter = 0;
static uint8_t needRender = 0;

static uint8_t key2_wait_release = 0;
static uint8_t key1_wait_release = 0;

volatile uint8_t nextInput = 0;

volatile int down_0;
volatile int down_1;
volatile int down_2;

void TIMER0_IRQHandler(void) {

    if (!(LPC_TIM0->IR & 1)) return;
    LPC_TIM0->IR = 1;   // clear subito
	
		// KEY1: attesa rilascio (GPIO P2.11) 
    if (key1_wait_release) {
        if ((LPC_GPIO2->FIOPIN & (1 << 11)) != 0) {   // rilasciato

            key1_wait_release = 0;

            // rimetti EINT1
            LPC_PINCON->PINSEL4 |= (1 << 22);

            // clear + enable IRQ
            LPC_SC->EXTINT = (1 << 1);
            NVIC_ClearPendingIRQ(EINT1_IRQn);
            NVIC_EnableIRQ(EINT1_IRQn);
        }
    }

      if (down_1 && !key1_wait_release) {
          if (++key1_cnt >= DEBOUNCE_TICKS) {

              key1_wait_release = 1;   // ora aspetta rilascio
              down_1 = 0;
              key1_cnt = 0;

              // AZIONE KEY1 
              if (gameOver) {
                  initField();
                  spawnTetromino();
                  pauseFlag = 0;
                  gameOver = 0;
								  
              }
              else if (pauseFlag) {
                       if (!currentSpawned)
                           spawnTetromino();
                           pauseFlag = 0;
              }
              else {
                    pauseFlag = 1;
              }
              LCD_Display_State(gameOver, pauseFlag);
              return;
         }
     }
      // KEY2: aspetta rilascio (GPIO P2.12) 
    if (key2_wait_release) {
        if ((LPC_GPIO2->FIOPIN & (1 << 12)) != 0) {   // rilasciato
            key2_wait_release = 0;

            // rimetti P2.12 come EINT2
            LPC_PINCON->PINSEL4 |= (1 << 24);

            // clear pending + enable
            LPC_SC->EXTINT = (1 << 2);
            NVIC_ClearPendingIRQ(EINT2_IRQn);
            NVIC_EnableIRQ(EINT2_IRQn);
        }
    }
     // KEY2 : HARD DROP (debounce + one-shot) 
    if (down_2 && !key2_wait_release) {
        if (++key2_cnt >= DEBOUNCE_TICKS) {

            // consuma il press
            down_2 = 0;
            key2_cnt = 0;

            // ora aspetta rilascio prima di riabilitare EINT2
            key2_wait_release = 1;

            // se in pausa/gameover non fare drop
            if (pauseFlag || gameOver || !currentSpawned) return;

            // HARD DROP: eseguilo UNA SOLA VOLTA
            while (!checkCollision(current.x, current.y + 1, current.rotation))
                current.y++;

            lockTetromino();
            spawnTetromino();

            // reset contatori per evitare “secondo step” nello stesso tick
            drop_cnt = 0;
            softDropCounter = 0;
            nextInput = 0;

            tetris_render();
            return;
        }
    }

    // STOP SE IN PAUSA 
    if (pauseFlag || gameOver || !currentSpawned)
        return;

    // JOYSTICK 
    int softDropPressed = 0;
    if ((LPC_GPIO1->FIOPIN & (1<<26)) == 0) { // down
        nextInput = 1;
        softDropPressed = 1;
    }
    else if ((LPC_GPIO1->FIOPIN & (1<<27)) == 0) nextInput = 2; // left
    else if ((LPC_GPIO1->FIOPIN & (1<<28)) == 0) nextInput = 4; // right
    else if ((LPC_GPIO1->FIOPIN & (1<<29)) == 0) nextInput = 3; // rotate
    else nextInput = 0;

    // CADUTA 
    if (softDropPressed) {
        if (++softDropCounter >= SOFT_DROP_TICKS) {
            moveDown();
            softDropCounter = 0;
            needRender = 1;
        }
    } else {
        softDropCounter = 0;
        if (++drop_cnt >= DROP_TICKS) {
            moveDown();
            drop_cnt = 0;
            needRender = 1;
        }
    }

    // INPUT LATERALE / ROTATE 
    if (nextInput) {
        processInput();
        needRender = 1;
    }

    // RENDER 
    if (needRender) {
        tetris_render();
        needRender = 0;
    }
}