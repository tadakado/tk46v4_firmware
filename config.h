/*
Copyright 2019 sekigon-gonnoc
Copyright 2021 tadakado

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

#pragma once

#ifndef __ASSEMBLER__
#include "config_common.h"
#include "apidef.h"

#define G01 1
#define G02 2
#define G08 8
#define LED_NUM_LOCK_PIN    G01
#define LED_CAPS_LOCK_PIN   G02
#define LED_SCROLL_LOCK_PIN G08
#define LED_PIN_ON_STATE    1

/* USB Device descriptor parameter */

#define VENDOR_ID       0xcafe
#define PRODUCT_ID      0x4403
#define DEVICE_VER      0x0003
#define MANUFACTURER    tadakado
#define PRODUCT         TK46v4
#define DESCRIPTION     A split keyboard

#define BMP_BOOTPIN_AS_RESET

#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
//#define PREVENT_STUCK_MODIFIERS
//#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200
#define COMBO_COUNT 32

/* key matrix size */
#define MATRIX_ROWS_DEFAULT 1
#define MATRIX_COLS_DEFAULT 3
#define THIS_DEVICE_ROWS 1
#define THIS_DEVICE_COLS 3
#define IS_LEFT_HAND  true
#define BMP_DEFAULT_MODE SINGLE

/*
 * Enable mass storage when the switch connected following pins is pushed on boot.
 * No warranty
*/
// #define ALLOW_MSC_ROW_PIN 7
// #define ALLOW_MSC_COL_PIN 20

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { 33 } // Dummy
#define MATRIX_COL_PINS { 1, 2, 3 }
#define MATRIX_LAYOUT { 1, 2, 3, 255 }

/* Below is the actual pins and layout of tk44v3
#define MATRIX_ROW_PINS {8,9,10,19,         7,9,10,11}
#define MATRIX_COL_PINS {11,20,18,17,16,15, 15,16,17,18,19,20}
#define MATRIX_LAYOUT {\
  1,  2,  3,  4,  5,  6,   30, 29, 28, 27, 26, 25, \
  7,  8,  9, 10, 11, 12,   36, 35, 34, 33, 32, 31, \
 13, 14, 15, 16, 17, 18,   42, 41, 40, 39, 38, 37, \
     20, 21, 22, 23, 24,   48, 47, 46, 45, 44,     255}
*/

#define KEYMAP_PRIOR_LOCALE 0
#define KEYMAP_ASCII 0

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGBLIGHT_SPLIT
#define G00 255 // Dummy for bin/qmk config generation
#define RGB_DI_PIN G00
#ifdef RGB_DI_PIN
  #define RGBLED_NUM_DEFAULT 128
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
  #define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_EFFECT_RGB_TEST
  #define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
  #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
  #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 1

#define DEBUG_ACTION

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

#endif /*__ASSEMBLER__*/
