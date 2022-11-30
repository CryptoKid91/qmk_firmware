#include QMK_KEYBOARD_H

#define _NAV 0
#define _MACRO 1
#define _NUMPAD 2
#define _MENU 3

static uint32_t key_timer = 0;
static bool key_trigger = false;

enum custom_keycodes {
  NEWTAB = SAFE_RANGE,
  MURO,
  KEY_TMR
};

// Tap Dance declarations
enum {
    TD_MUTE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_F19, KC_F20),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NAV] = LAYOUT_ortho_4x4(
		NEWTAB, MURO, KC_NO, OSL(_MENU),   \
		KEY_TMR, KC_NO, KC_NO, KC_NO, \
		KC_F18, KC_MPRV, KC_MNXT, KC_MPLY, \
		TD(TD_MUTE),  KC_F21,  KC_F22,  KC_F23 \
	),
	[_MACRO] = LAYOUT_ortho_4x4(
		RESET,   BL_STEP, _______, OSL(_MENU), \
		BL_TOGG, RGB_VAI, RGB_VAD,  KC_VOLD, \
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

layer_state_t layer_state_set_user(layer_state_t state) {
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
  case KEY_TMR:
    if (record->event.pressed) {
        key_trigger ^= true;
        if (key_trigger) {
            tap_code(KC_SPC);
            key_timer = timer_read32();
        }
    }
    return false;
  default:
    return true;
  }
}

void matrix_scan_user(void) {
    if (timer_elapsed32(key_timer) > 1345) { // 1.34 seconds
        key_timer = timer_read32();  // resets timer
        if (key_trigger) tap_code(KC_SPC); // tap if enabled
    }
}
