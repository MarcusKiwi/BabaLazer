#include "servo.h"

void dualservo(uint8_t x, uint8_t y, uint8_t steps) {
	uint8_t hi;
	uint8_t lo;
	for(uint8_t i=0; i<steps; i++) {
		// servo 1
		hi = x;
		lo = 100-x;
		SERVO_PORT |= (1<<SERVO_PIN1);
		_delay_us(999);
		while(hi) {
			_delay_us(8);
			hi--;
		}
		SERVO_PORT &= ~(1<<SERVO_PIN1);
		while(lo) {
			_delay_us(8);
			lo--;
		}
		_delay_ms(8);
		// servo 2
		hi = y;
		lo = 100-y;
		SERVO_PORT |= (1<<SERVO_PIN2);
		_delay_us(999);
		while(hi) {
			_delay_us(8);
			hi--;
		}
		SERVO_PORT &= ~(1<<SERVO_PIN2);
		while(lo) {
			_delay_us(8);
			lo--;
		}
		_delay_ms(8);
	}
}
