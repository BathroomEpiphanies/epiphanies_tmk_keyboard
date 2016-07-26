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
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "debug.h"
#include "keymap.h"

/*
  Matrix col/row mapping

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  |06/6|    |07/4|08/4|08/2|08/6| |15/5|11/6|12/2|12/4| |14/4|14/5|14/6|14/0| |13/5|13/7|15/7|
  `----'    `-------------------' `-------------------' `-------------------' `--------------'
  ,-------------------------------------------------------------------------. ,--------------. ,-------------------.
  |06/4|06/5|07/5|08/5|09/5|09/4|10/4|10/5|11/5|12/5|05/5|05/4|11/4|    14/2| |17/4|02/4|04/4| |16/1|17/1|04/1|04/0|
  |-------------------------------------------------------------------------| |--------------| |-------------------|
  |06/2  |06/7|07/7|08/7|09/7|09/2|10/2|10/7|11/7|12/7|05/7|05/2|11/2|  14/3| |16/4|02/5|04/5| |16/7|17/7|04/7|    |
  |-------------------------------------------------------------------------| '--------------' |-------------- 02/7|
  |02/7   |06/3|07/3|08/3|09/3|09/6|10/6|10/3|11/3|12/3|05/3|05/6|      14/1|                  |16/2|17/2|04/2|    |
  |-------------------------------------------------------------------------|      ,----.      |-------------------|
  |01/2     |06/1|07/1|08/1|09/1|09/0|10/0|10/1|11/1|12/1|05/0|         01/3|      |02/6|      |16/3|17/3|04/3|    |
  |-------------------------------------------------------------------------| ,--------------. |-------------- 02/3|
  |15/4|03/2|13/6|                 16/6                  |13/0|0/3|12/0|15/1| |02/0|16/0|17/0| | 17/6    |04/6|    |
  `-------------------------------------------------------------------------' `--------------' `-------------------'
*/

#define KEYMAP(                                                                               \
  KA0,    KC0,KD0,KE0,KF0,  KG0,KH0,KI0,KJ0,  KL0,KM0,KN0,KO0,  KP0,KQ0,KR0,                  \
                                                                                              \
  KA1,KB1,KC1,KD1,KE1,KF1,KG1,KH1,KI1,KJ1,KK1,KL1,KM1,KN1,KO1,  KP1,KQ1,KR1,  KS1,KT1,KU1,KV1,\
  KA2,  KB2,KC2,KD2,KE2,KF2,KG2,KH2,KI2,KJ2,KK2,KL2,KM2,  KN2,  KP2,KQ2,KR2,  KS2,KT2,KU2,KV2,\
  KA2, KB3,KC3,KD3,KE3,KF3,KG3,  KH3,KI3,KJ3,KK3,KL3,KM3, KN3,                KS3,KT3,KU3,    \
    KA4,  KC4,KD4,KE4,KF4,KG4,KH4,KI4,KJ4,KK4,KL4,KM4,  KO4,        KQ4,      KS4,KT4,KU4,KV4,\
   KB5, KC5,KD5, KE5,   KF5,  KH5,  KI5,   KJ5, KK5,KL5, KO5,   KP5,KQ5,KR5,  KS5,    KU5    )\
  {                                                                                           \
/*          0         1         2         3         4         5       */ \
/* A  0 */ {KC_ESC,   KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_NO   }, \
/* B  1 */ {KC_NO,    KC_##KB1, KC_##KB2, KC_##KB3, KC_NO,    KC_##KB5}, \
/* C  2 */ {KC_##KC0, KC_##KC1, KC_##KC2, KC_##KC3, KC_##KC4, KC_##KC5}, \
/* D  3 */ {KC_##KD0, KC_##KD1, KC_##KD2, KC_##KD3, KC_##KD4, KC_##KD5}, \
/* E  4 */ {KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5}, \
/* F  5 */ {KC_##KF0, KC_##KF1, KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5}, \
/* G  6 */ {KC_##KG0, KC_##KG1, KC_##KG2, KC_##KG3, KC_##KG4, KC_NO   }, \
/* H  7 */ {KC_##KH0, KC_##KH1, KC_##KH2, KC_##KH3, KC_##KH4, KC_##KH5}, \
/* I  8 */ {KC_##KI0, KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_##KI5}, \
/* J  9 */ {KC_##KJ0, KC_##KJ1, KC_##KJ2, KC_##KJ3, KC_##KJ4, KC_##KJ5}, \
/* K 10 */ {KC_NO,    KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5}, \
/* L 11 */ {KC_##KL0, KC_##KL1, KC_##KL2, KC_##KL3, KC_##KL4, KC_##KL5}, \
/* M 12 */ {KC_##KM0, KC_##KM1, KC_##KM2, KC_##KM3, KC_##KM4, KC_NO   }, \
/* N 13 */ {KC_##KN0, KC_##KN1, KC_##KN2, KC_##KN3, KC_NO,    KC_NO   }, \
/* O 14 */ {KC_##KO0, KC_##KO1, KC_NO,    KC_NO,    KC_##KO4, KC_##KO5}, \
/* P 15 */ {KC_##KP0, KC_##KP1, KC_##KP2, KC_NO,    KC_NO,    KC_##KP5}, \
/* Q 16 */ {KC_##KQ0, KC_##KQ1, KC_##KQ2, KC_NO,    KC_##KQ4, KC_##KQ5}, \
/* R 17 */ {KC_##KR0, KC_##KR1, KC_##KR2, KC_NO,    KC_NO,    KC_##KR5}, \
/* S 18 */ {KC_NO,    KC_##KS1, KC_##KS2, KC_##KS3, KC_##KS4, KC_##KS5}, \
/* T 19 */ {KC_NO,    KC_##KT1, KC_##KT2, KC_##KT3, KC_##KT4, KC_NO   }, \
/* U 20 */ {KC_NO,    KC_##KU1, KC_##KU2, KC_##KU3, KC_##KU4, KC_##KU5}, \
/* V 21 */ {KC_NO,    KC_##KV1, KC_##KV2, KC_NO,    KC_##KV4, KC_NO   }  \
  }

#include "keymap_ansi.h"

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
  if (layer < KEYMAPS_SIZE) {
    return pgm_read_byte(&keymaps[(layer)][(key.col)][(key.row)]);
  } else {
    return pgm_read_byte(&keymaps[0][(key.col)][(key.row)]);
  }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
  action_t action;
  if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
    action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
  } else {
    action.code = ACTION_NO;
  }
  return action;
}
