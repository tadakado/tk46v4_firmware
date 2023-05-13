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
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include "i2c.h"
#include "pointing_device.h"
#include "drivers/sensors/cirque_pinnacle.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LOWER = BMP_SAFE_RANGE,
    RAISE,
    ADJUST,
    CLR,
    STAT,
    DUMMY
};

const key_string_map_t custom_keys_user =
{
    .start_kc = LOWER,
    .end_kc = DUMMY,
    .key_strings = "LOWER\0RAISE\0ADJUST\0CLR\0STAT\0DUMMY\0"
};

// layers, keymaps, keymaps_len will be over-written.

enum layers {
    _BASE, _LOWER, _RAISE, _ADJUST, _NUM, _BLE, _MOUSE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
        // Dummy 
        KC_A, KC_1, KC_H, KC_TAB, KC_SPC,
    }}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}

// clear flags for debugging

void clear_modifiers(void) {
    unregister_code(KC_LSFT);
    unregister_code(KC_RSFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_RCTL);
    unregister_code(KC_LGUI);
    unregister_code(KC_RGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_RALT);
}

// pointing device (Cirque Trackpad)

void pointing_device_init_user(void) {
    cirque_pinnacle_init();
}

// LED settings (I2C LED controller https://github.com/tadakado/i2c_ws2812)

#define I2C_LED_ADDR 0x08
#define N_LED 7
#define STATUS_LED 6

#define LED_LEFT 1
#define LED_RIGHT 2
#define LED_BOTH (LED_LEFT | LED_RIGHT)

static bool led_init_done = false;
static uint16_t ble_stat;
static uint32_t led_off_time;
static uint8_t I2C_LED_START[2] = {0xff, 0x07};

struct {
    uint8_t addr;
    RGB data[N_LED];
} static i2c_led = { 0x00 };

void i2c_set_led() {
    i2c_init();
    i2c_transmit(I2C_7BIT_ADDR(I2C_LED_ADDR), (uint8_t *)&i2c_led, sizeof(i2c_led), 0);
    i2c_transmit(I2C_7BIT_ADDR(I2C_LED_ADDR), I2C_LED_START, sizeof(I2C_LED_START), 0);
    i2c_uninit();
}

void set_led(uint8_t side, uint8_t r, uint8_t g, uint8_t b, uint8_t index) {
    if (side & LED_LEFT) {
        rgblight_setrgb_at(r, g, b, index);
    }
    if (side & LED_RIGHT) {
        setrgb(r, g, b, (LED_TYPE *)&i2c_led.data[index]);
        i2c_set_led();
    }
}

void set_rgb_all(uint8_t side, uint8_t r, uint8_t g, uint8_t b) {
    if (side & LED_LEFT) {
        for (int i=0; i<N_LED; i++) {
            setrgb(r, g, b, (LED_TYPE *)&led[i]);
	}
    }
    if (side & LED_RIGHT) {
        for (int i=0; i<N_LED; i++) {
            setrgb(r, g, b, (LED_TYPE *)&i2c_led.data[i]);
        }
    }
}

void set_led_all(uint8_t side, uint8_t r, uint8_t g, uint8_t b) {
    set_rgb_all(side, r, g, b);
    if (side & LED_LEFT) {
        rgblight_set();
    }
    if (side & LED_RIGHT) {
        i2c_set_led();
    }
}

void init_led() {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    set_led_all(LED_BOTH, RGB_RED);
    led_off_time = timer_read32();
}

#define COLOR0 RGB_RED
#define COLOR1 RGB_GREEN
#define COLOR2 RGB_BLUE
#define COLOR3 RGB_YELLOW
#define COLOR4 RGB_MAGENTA
#define COLOR5 RGB_CYAN
#define COLOR6 RGB_WHITE
#define COLOR7 RGB_ORANGE
#define COLOR8 RGB_PINK
#define COLOR9 RGB_PURPLE

void set_layer_led(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BASE:
        set_rgb_all(LED_BOTH, COLOR0); break;
    case _LOWER:
        set_rgb_all(LED_BOTH, COLOR1); break;
    case _RAISE:
        set_rgb_all(LED_BOTH, COLOR2); break;
    case _ADJUST:
        set_rgb_all(LED_BOTH, COLOR3); break;
    case _NUM:
        set_rgb_all(LED_BOTH, COLOR4); break;
    case _BLE:
        set_rgb_all(LED_BOTH, COLOR5); break;
    case _MOUSE:
        set_rgb_all(LED_BOTH, COLOR6); break;
    default:
        set_rgb_all(LED_BOTH, COLOR7); break;
    }
}

void set_connection_led() {
    // stat >> 8 : number of BLE connections (0 or 1)
    // stat & 0xff : BLE connection id (0 to 7) or nobonding (0xff)
    uint16_t stat = BMPAPI->ble.get_connection_status();
    if (get_usb_enabled()) {
        set_led(LED_BOTH, COLOR0, STATUS_LED);
    } else {
        switch (stat & 0xff) {
        case 0:
            set_led(LED_BOTH, COLOR1, STATUS_LED); break;
        case 1:
            set_led(LED_BOTH, COLOR2, STATUS_LED); break;
        case 2:
            set_led(LED_BOTH, COLOR3, STATUS_LED); break;
        case 3:
            set_led(LED_BOTH, COLOR4, STATUS_LED); break;
        case 4:
            set_led(LED_BOTH, COLOR5, STATUS_LED); break;
        case 5:
            set_led(LED_BOTH, COLOR6, STATUS_LED); break;
        case 6:
            set_led(LED_BOTH, COLOR7, STATUS_LED); break;
        case 7:
            set_led(LED_BOTH, COLOR8, STATUS_LED); break;
        default:
            set_led(LED_BOTH, COLOR9, STATUS_LED); break;
        }
    }
}

void keyboard_post_init_user(void) {
    init_led();
    ble_stat = BMPAPI->ble.get_connection_status() | (get_ble_enabled()<<15);
}

void matrix_scan_user(void) {
    // somehow init_led requires additional code here.
    if (! led_init_done) {
        rgblight_set();
        led_init_done = true;
    }
    uint16_t stat = BMPAPI->ble.get_connection_status() | (get_ble_enabled()<<15);;
    if (stat != ble_stat) {
        set_connection_led();
	ble_stat = stat;
	led_off_time = timer_read32();
    }
    if (timer_elapsed32(led_off_time) > 10 * 1000) { // 10 sec
        set_led_all(LED_BOTH, RGB_BLACK);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_layer_led(state);
    set_connection_led();
    led_off_time = timer_read32();
    return state;
}

void bmp_before_sleep() {
    set_led_all(LED_BOTH, RGB_BLACK);
}

// Status

void status() {
    uprintf("USB/BLE status: %d %d 0x%04x\r",
            get_usb_enabled(), get_ble_enabled(),
            BMPAPI->ble.get_connection_status());
}

// Pointing device

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    mouse_report.x = mouse_report.x / 2;
    mouse_report.y = mouse_report.y / 2;
//    mouse_report.h = mouse_report.h / 2;
//    mouse_report.v = mouse_report.v / 2;
    return mouse_report;
}

// Custom behavior

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false) {
        return false;
    }

    switch (keycode) {
        case CLR:
            if (record->event.pressed) {
                uprint("##### clear keyboard #####\r");
                layer_clear();
                clear_modifiers();
                clear_keyboard();
            }
            return false;
        case STAT:
            if (record->event.pressed) {
                status();
            }
            return false;
        default:
            break;
    }
    return true;
}
