#include <avr/io.h>

const char progmem_bound[] PROGMEM = "  BOUNDARIES                   -- Left       -- Right      -- Top        -- Bottom  ";
const char progmem_speed[] PROGMEM = "  GAME SPEED                      --                        laser      is cenetered ";
//                                   |             |             |             |             |             |             |

const char progmem_play[] PROGMEM = {
	// row 0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 01-10
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 11-20
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 21-30
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // 31-40
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // 41-50
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51-60
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xE0, 0xC0, // 61-70
	0xC0, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, // 71-80
	0x00, 0x00, 0x00, 0x00,                                     // 81-84 
	// row 1
	0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, // 01-10
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // 11-20
	0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, // 21-30
	0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 31-40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 41-50
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, // 51-60
	0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, // 61-70
	0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF, // 71-80
	0xFE, 0xF8, 0xF0, 0x80,                                     // 81-84
	// row 2
	0x06, 0x0F, 0x1F, 0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, // 01-10
	0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, // 11-20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 21-30
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 31-40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 41-50
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 51-60
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 61-70
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 71-80
	0xFF, 0xFF, 0x0F, 0x00,                                     // 81-84
	// row 3
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xF2, // 01-10
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 11-20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 21-30
	0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, // 31-40
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, // 41-50
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, // 51-60
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 61-70
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0x1F, 0x03, // 71-80
	0x01, 0x01, 0x00, 0x00,                                     // 81-84
	// row 4
	0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, // 01-10
	0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0xF3, 0x83, 0x87, // 11-20
	0x07, 0x07, 0x03, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0xF0, // 21-30
	0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, // 31-40
	0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, // 41-50
	0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, // 51-60
	0x80, 0x00, 0x00, 0x00, 0x80, 0x81, 0x81, 0x01, 0x03, 0x03, // 61-70
	0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, // 71-80
	0x00, 0x00, 0x00, 0x00,                                     // 81-84
	// row 5
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 01-10
	0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x0F, 0x08, 0x08, // 11-20
	0x07, 0x00, 0x00, 0x0E, 0x0A, 0x0A, 0x0F, 0x00, 0x00, 0x0F, // 21-30
	0x08, 0x08, 0x07, 0x00, 0x00, 0x0E, 0x0A, 0x0A, 0x0F, 0x00, // 31-40
	0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0E, 0x0A, 0x0A, 0x0F, // 41-50
	0x00, 0x00, 0x08, 0x0C, 0x0A, 0x09, 0x00, 0x00, 0x07, 0x0A, // 51-60
	0x0A, 0x0B, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x03, // 61-70
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 71-80
	0x03, 0x03, 0x03, 0x03                                      // 81-84
};