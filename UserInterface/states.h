/*
 * states.h
 *
 *  Created on: 5 Feb 2012
 *      Author: Pete Hemery
 */

#ifndef STATES_H_
#define STATES_H_

#include "top.h"
#include "display.h"
#include "threads.h"

/* State Table */
enum ui_states{
	INIT_STATE,
	EMERGENCY,
	WAITING_LOGGED_OUT,
	INPUTTING_PIN,
	WAITING_LOGGED_IN,
	INPUTTING_TRACK_NUMBER,
	MENU_SELECT
} current_state;

extern int state;
extern BYTE playing;

void * state_machine(void);
extern void input_pin(char);
extern void input_track_number(char);
extern void menu_select(void);

#endif /* STATES_H_ */