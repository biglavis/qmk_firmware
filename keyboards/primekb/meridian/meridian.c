/*
Copyright 2020 Holten Campbell

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

#include "meridian.h"

//Initialize B12 for in-switch caps lock
void keyboard_pre_init_kb(void){
    setPinOutput(B12);
    keyboard_pre_init_user();
}

//Update LED indicator
void update_led(void){
	if (biton32(layer_state)==1){
		rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_at(HSV_WHITE, 0);
		rgblight_sethsv_at(0, 0, 0, 1);
		rgblight_sethsv_at(0, 0, 0, 2);
	} else if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
		rgblight_sethsv_noeeprom(HSV_WHITE);
		rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	} else {
		rgblight_sethsv_noeeprom(HSV_RED);
		rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
	}
}

void led_set_user(uint8_t usb_led){
	// must trigger to
	// - activate capslock indicator
	// - de-activate capslock indicator
	update_led();
}

uint32_t layer_state_set_user(uint32_t state){
	// must trigger to
	// - activate layer indicator
	// - de-activate layer indicator
	update_led();
	return state;
}