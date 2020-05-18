#include QMK_KEYBOARD_H

#define _NAV 0
#define _MACRO 1
#define _NUMPAD 2
#define _MENU 3

enum custom_keycodes {
  NEWTAB = SAFE_RANGE,
  MURO
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NAV] = LAYOUT_ortho_4x4(
		NEWTAB, MURO, KC_NO, OSL(_MENU),   \
		KC_NO, KC_NO, KC_NO, KC_NO, \
		KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, \
		G(KC_LEFT), G(KC_RIGHT), S(G(KC_LEFT)), S(G(KC_RIGHT)) \
	),
	[_MACRO] = LAYOUT_ortho_4x4(
		RESET,   BL_STEP, _______, OSL(_MENU), \
		BL_TOGG, BL_DEC,  BL_INC,  KC_VOLD, \
		RGB_TOG, RGB_MOD, RGB_HUI, KC_MUTE, \
		RGB_SAI, RGB_SAD, RGB_HUD, _______  \
	),
	[_NUMPAD] = LAYOUT_ortho_4x4(
		KC_KP_7, KC_KP_8, KC_KP_9, OSL(_MENU),   \
		KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, \
		KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, \
		KC_KP_0, KC_PDOT, KC_PCMM, KC_PENT  \
	),
	[_MENU] = LAYOUT_ortho_4x4(
		TO(_NAV), TO(_MACRO), TO(_NUMPAD), KC_TRNS, \
		KC_NO, KC_NO, KC_NO, KC_NO, \
		KC_NO, KC_NO, KC_NO, KC_NO, \
		KC_NO, KC_NO, KC_NO, KC_NO  \
	),

};

uint32_t layer_state_set_user(uint32_t state) {
  rgblight_sethsv_noeeprom(0,0,0);
  switch (biton32(state)) {
  case _NAV:
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    break;
  case _NUMPAD:
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  case _MACRO:
    rgblight_sethsv_noeeprom(HSV_RED);
    break;
  case _MENU:
    rgblight_sethsv_at(HSV_PURPLE, 0);
    rgblight_sethsv_at(HSV_RED, 1);
    rgblight_sethsv_at(HSV_GREEN, 2);
    break;
  default:
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    break;
  }
  return state;
};


void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case NEWTAB:
    if(record->event.pressed) {
      SEND_STRING(SS_LCTRL("c") SS_LCTRL("t"));
      _delay_ms(100);
      SEND_STRING(SS_LCTRL("v"));
      _delay_ms(100);
      SEND_STRING(SS_TAP(X_ENTER));
    } else {
    }
    return false;
  case MURO:
    if(record->event.pressed) {
      SEND_STRING(SS_LCTRL("t"));
      _delay_ms(100);
      SEND_STRING("www.io/tech.fi" SS_TAP(X_ENTER));
    } else {
    }
    return false;
  default:
    return true;
  }
}
