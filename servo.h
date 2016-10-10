#include <avr/io.h>
#include <util/delay.h>

#define SERVO_DDR  DDRB
#define SERVO_PORT PORTB
#define SERVO_PIN1 1
#define SERVO_PIN2 2

void dualservo(uint8_t x, uint8_t y, uint8_t steps);
