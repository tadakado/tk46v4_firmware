/* Copyright 2021 tadakado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// #define DISABLE_MSC 1

#define MASTER_LEFT

#define PERMISSIVE_HOLD
#undef IGNORE_MOD_TAP_INTERRUPT

#define GUI_COMBO_TAPPING_TERM 50

// define macro for using recent pointing device code (devices/sensors/cirque & quantum/pointing_device)
#define GET_TAPPING_TERM(keycode, record) get_tapping_term(keycode, record)
#define KC_LEFT_CTRL KC_LCTL
#define KC_RIGHT_GUI KC_RGUI
#define QK_TO_GET_LAYER(kc) ((kc)&0x1F)
#define QK_TOGGLE_LAYER_GET_LAYER(kc) ((kc)&0x1F)
#define QK_MOMENTARY_GET_LAYER(kc) ((kc)&0x1F)
#define QK_LAYER_MOD_GET_LAYER(kc) (((kc) >> 5) & 0xF)
#define QK_LAYER_TAP_TOGGLE_GET_LAYER(kc) ((kc)&0x1F)
#define QK_LAYER_TAP_GET_LAYER(kc) (((kc) >> 8) & 0xF)
