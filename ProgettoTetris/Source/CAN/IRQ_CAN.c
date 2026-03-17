/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.h>                  /* LPC17xx definitions */
#include "CAN.h"                      /* LPC17xx CAN adaption layer */
#include "../GLCD/GLCD.h"
#include <stdio.h>
/*
extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    // CAN message for sending 
extern CAN_msg       CAN_RxMsg;    // CAN message for receiving                           

int readtime, readlives, readscore;
extern int victory, gameover;
*/
/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
 /*
void CAN_IRQHandler (void)  {

  // check CAN controller 1 
	icr = 0;
  icr = (LPC_CAN1->ICR | icr) & 0xFF;             // clear interrupts on CAN1
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             // clear interrupts on CAN2
	
  if (icr & (1 << 0)) {                          		// CAN Controller #1 meassage is received 
		CAN_rdMsg (1, &CAN_RxMsg);	                		// Read the message 
    LPC_CAN1->CMR = (1 << 2);                    		// Release receive buffer 
		
		readlives = CAN_RxMsg.data[0];	// the number of lives is the first part of the message
		readtime = CAN_RxMsg.data[1];		// the remaining time is the second part of the message
		
		readscore = (CAN_RxMsg.data[2] << 8);				// the score is on 16 bits, so the first part gets shifted
		readscore = readscore | CAN_RxMsg.data[3];	// and the total is obtained by combining the first and the second part
		
		if (!victory && !gameover) {	// render the received data only when it needs to be shown
			renderScore(readscore);
			renderTimer(readtime);
			renderLives(readlives);
		}
  }
}
*/
