/*
  Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 0
#endif
static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void select_col(uint8_t col);

inline uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

/* Row pin configuration
 *
 * row: 0    1    2    3    4    5    6    7
 * pin: PC2  PD0  PD1  PC7  PD5  PD6  PD2  PD4
 *
 * Column pin configuration 
 *
 * These columns uses two 74HC42 4 to 10 bit demultiplexers (low
 * active) to control the 18 columns. The columns are driven from pins
 * B6,5,4,3,2,1.
 */
void matrix_init(void) {
  DDRC  &= ~0b10000100;  // Row input pins
  DDRD  &= ~0b01110111;
  PORTC |=  0b10000100;
  PORTD |=  0b01110111;
  
  DDRB  |=  0b01111110;  // Column output pins
  
  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);
    uint8_t rows = read_rows();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        debouncing = DEBOUNCE;
      }
    }
  }
  
  if (debouncing) {
    if (--debouncing) {
      _delay_ms(1);
    }
    else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }
  
  return 1;
}

bool matrix_is_modified(void) {
  if (debouncing)
    return false;
  else
    return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop32(matrix[i]);
  }
  return count;
}

static uint8_t read_rows(void) {
  return
    (PINC&(1<<2) ? 0 : (1<<0)) |
    (PIND&(1<<0) ? 0 : (1<<1)) |
    (PIND&(1<<1) ? 0 : (1<<2)) |
    (PINC&(1<<7) ? 0 : (1<<3)) |
    (PIND&(1<<5) ? 0 : (1<<4)) |
    (PIND&(1<<4) ? 0 : (1<<5)) |
    (PIND&(1<<2) ? 0 : (1<<6)) |
    (PIND&(1<<6) ? 0 : (1<<7));
}

static void select_col(uint8_t col) {
  switch (col) {
  case  0: PORTB = (PORTB & ~0b01111110) | 0b00111010; break;
  case  1: PORTB = (PORTB & ~0b01111110) | 0b01011000; break;
  case  2: PORTB = (PORTB & ~0b01111110) | 0b01110000; break;
  case  3: PORTB = (PORTB & ~0b01111110) | 0b01101110; break;
  case  4: PORTB = (PORTB & ~0b01111110) | 0b01101100; break;
  case  5: PORTB = (PORTB & ~0b01111110) | 0b01101010; break;
  case  6: PORTB = (PORTB & ~0b01111110) | 0b01101000; break;
  case  7: PORTB = (PORTB & ~0b01111110) | 0b01100100; break;
  case  8: PORTB = (PORTB & ~0b01111110) | 0b01100000; break;
  case  9: PORTB = (PORTB & ~0b01111110) | 0b01100010; break;
  case 10: PORTB = (PORTB & ~0b01111110) | 0b00011010; break;
  case 11: PORTB = (PORTB & ~0b01111110) | 0b00011000; break;
  case 12: PORTB = (PORTB & ~0b01111110) | 0b00111100; break;
  case 13: PORTB = (PORTB & ~0b01111110) | 0b01100110; break;
  case 14: PORTB = (PORTB & ~0b01111110) | 0b00111000; break;
  case 15: PORTB = (PORTB & ~0b01111110) | 0b01110010; break;
  case 16: PORTB = (PORTB & ~0b01111110) | 0b00011110; break;
  case 17: PORTB = (PORTB & ~0b01111110) | 0b00111110; break;
  }
}
