#include <avr/io.h>
#include <avr/eeprom.h> 
#include <util/delay.h>
#include <pcd8544.h>
#include <stdlib.h>
#include "art.h"
#include "servo.h"

#define BTN_DDR  DDRD
#define BTN_PORT PORTD
#define BTN_PIN  PIND
#define BTN_MINS 0
#define BTN_MODE 1
#define BTN_PLUS 2

#define LEFT	0
#define RIGHT	1
#define TOP 	2
#define BOTTOM	3
#define SPEED	4
#define PLAY	5

#define MAX_MODE 5

#define EEP_INIT 100
#define EEP_RAND 101

#define SVO_MID 49
#define BIGMOVE 25
#define SMLMOVE 10
 
void displayint(uint8_t x) {
	char c[3];
	itoa(x,c,10);
	if(x<10) {
		pcd8544_chr('0');
		pcd8544_chr(c[0]);
	} else {
		pcd8544_chr(c[0]);
		pcd8544_chr(c[1]);
	}
}

void main() {
	
	// all ports output and low by default
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	// button init, pins input with pullup
	BTN_DDR &= ~((1<<BTN_MINS) | (1<<BTN_MODE) | (1<<BTN_PLUS));
	BTN_PORT |= ((1<<BTN_MINS) | (1<<BTN_MODE) | (1<<BTN_PLUS));
	
	// variables
	uint8_t mode = PLAY;
	uint8_t ticks = 0;
	uint8_t conf[5] = {0,99,0,99,50};
	
	// load config
	if(eeprom_read_byte((uint8_t*)EEP_INIT)==0xA5) {
		for(uint16_t i=0; i<5; i++) {
			conf[i] = eeprom_read_byte((uint8_t*)i);
		}
	} else {
		for(uint16_t i=0; i<5; i++) {
			eeprom_write_byte((uint8_t*)i,conf[i]);
		}
		eeprom_write_byte((uint8_t*)EEP_INIT,0xA5);
	}
	
	// set up srand
	srand(eeprom_read_byte((uint8_t*)EEP_RAND));
	eeprom_write_byte((uint8_t*)EEP_RAND, (rand() % 255));
	
	// lcd init
	pcd8544_init();
	pcd8544_pos(0,0);
	for(uint16_t i=0; i<(84*6); i++) {
		pcd8544_raw(pgm_read_byte(&(progmem_play[i])));
	}
	
	// loop
	while(1) {
		/*********************
		* CHANGE & INIT MODE *
		*********************/
		if(!(BTN_PIN & (1<<BTN_MODE))) {
			mode++;
			if(mode>MAX_MODE) mode=0;
			pcd8544_pos(0,0);
			/************
			* PLAY MODE *
			************/
			if(mode==PLAY) {
				// play mode art
				for(uint16_t i=0; i<504; i++) {
					pcd8544_raw(pgm_read_byte(&(progmem_play[i])));
				}
				// make play mode reset
				ticks = 0;
				// save new config to eeprom
				for(uint16_t i=0; i<5; i++) {
					eeprom_write_byte((uint8_t*)i,conf[i]);
				}
				// delay
				_delay_ms(250);		
			/**********************
			* SPEED & CENTER MODE *
			**********************/
			} else if(mode==SPEED) {
				// write text to display
				for(uint8_t i=0; i<(6*14); i++) {
					pcd8544_chr(pgm_read_byte(&(progmem_speed[i])));
				}
				// write speed to display
				pcd8544_pos((6*5)+3,2);
				pcd8544_chr(127);
				displayint(conf[SPEED]);
				// position servos
				dualservo(SVO_MID,SVO_MID,BIGMOVE);
			/****************
			* BOUNDARY MODE *
			****************/
			} else {
				// write text to display
				for(uint8_t i=0; i<(6*14); i++) {
					pcd8544_chr(pgm_read_byte(&(progmem_bound[i])));
				}
				// write arrow for current mode
				pcd8544_pos(2*6,mode+2);
				pcd8544_chr(127);
				// write config to display
				for(uint8_t i=0; i<4; i++) {
					pcd8544_pos(3*6,i+2);
					displayint(conf[i]);
				}
				// position servos
				if(mode<2) {
					dualservo(conf[mode],SVO_MID,BIGMOVE);
				} else {
					dualservo(SVO_MID,conf[mode],BIGMOVE);
				}
			}
		/*********************
		* RUN & EXECUTE MODE *
		*********************/
		} else {
			/************
			* PLAY MODE *
			************/
			if(mode==PLAY) {
				if(ticks==0) {
					// move servo
					dualservo(((rand() % (conf[RIGHT]-conf[LEFT])) + conf[LEFT]),((rand() % 
						(conf[BOTTOM]-conf[TOP])) + conf[TOP]),25);
					// set ticks to next movement
					ticks = 20 + (100-conf[SPEED]) + (rand() % (100-conf[SPEED]));
				}
				ticks--;
				_delay_ms(50);
			/**********************
			* SPEED & CENTER MODE *
			**********************/
			} else if(mode==SPEED) {
				uint8_t change = 0;
				if((!(BTN_PIN&(1<<BTN_PLUS))) && (conf[SPEED]<99)) { // plus
					conf[SPEED]++;
					change = 1;
				} else if((!(BTN_PIN&(1<<BTN_MINS))) && (conf[SPEED]>0)) { // minus
					conf[SPEED]--;
					change = 1;
				}
				if(change==1) {
					pcd8544_pos((6*6)+3,2);
					displayint(conf[SPEED]);
					_delay_ms(100);
				}
			/****************
			* BOUNDARY MODE *
			****************/
			} else {
				// handle input
				uint8_t change = 0;
				if((!(BTN_PIN&(1<<BTN_PLUS))) && (conf[mode]<99)) { // plus
					// ensure left<right and top<bottom
					if((((mode==LEFT)||(mode==TOP)) && (conf[mode]<(conf[mode+1]-1))) || (mode==RIGHT)||(mode==BOTTOM) ) {
						conf[mode]++;
						change = 1;
					}
				} else if((!(BTN_PIN&(1<<BTN_MINS))) && (conf[mode]>0)) { // minus
					// ensure left<right and top<bottom
					if((((mode==RIGHT)||(mode==BOTTOM)) && (conf[mode]>(conf[mode-1]+1))) || (mode==LEFT)||(mode==TOP)) {
						conf[mode]--;
						change = 1;
					}
				}
				if(change==1) {
					// write config to display
					pcd8544_pos(3*6,mode+2);
					displayint(conf[mode]);
					// position servos
					if(mode<2) {
						dualservo(conf[mode],SVO_MID,SMLMOVE);
					} else {
						dualservo(SVO_MID,conf[mode],SMLMOVE);
					}
				}
			}
		}
	}
}
