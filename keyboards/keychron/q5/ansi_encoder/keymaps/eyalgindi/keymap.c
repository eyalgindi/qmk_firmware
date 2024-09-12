/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#include "keycodes.h"
#include "features/select_word.h"
#include QMK_KEYBOARD_H

enum layers{
  MAC_BASE,
  MAC_FN,
  MACROS
};

enum custom_keycodes {
  SS_EML = SAFE_RANGE,
  SELWORD //https://getreuer.info/posts/keyboards/select-word/index.html
};



typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

//Tap dance enums
enum {
  CTL_OSL = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_98(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_DEL,   KC_HOME,  KC_END,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,
        TD(CTL_OSL),  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT),

    [MAC_FN] = LAYOUT_ansi_98(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  QK_BOOT,  _______,  _______,  _______,  _______,  _______),

    [MACROS] = LAYOUT_ansi_98(
        _______,             _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,     _______,   _______,             _______,   _______,  _______,   _______,
        _______,   _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,    _______,   _______,            _______,   _______,  _______,  _______,
        _______,   _______,     _______,     SS_EML,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,    _______,  _______,            _______,    _______,    _______,
        _______,  _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,  _______,              _______,             _______,    _______,    _______,    _______,
        _______,            _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,              _______,  _______,    _______,    _______,    _______,
        _______,  SELWORD,  _______,                                _______,                                 _______,  _______, _______,  _______,  _______,  _______,  _______,    _______,  _______),

};

const uint16_t PROGMEM lock_scr_combo[] = {KC_1, KC_2, COMBO_END};

combo_t key_combos[] = {
    COMBO(lock_scr_combo, LCTL(LCMD(KC_Q)))
};


int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap ctltap_state = {
    .is_press_action = true,
    .state = 0
};


void ctl_finished (tap_dance_state_t *state, void *user_data) {
  ctltap_state.state = cur_dance(state);
  switch (ctltap_state.state) {
  case SINGLE_TAP: set_oneshot_layer(MACROS, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
  case SINGLE_HOLD: register_code(KC_LCTL); break;
  case DOUBLE_TAP: set_oneshot_layer(MACROS, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
  case DOUBLE_HOLD: register_code(KC_LCTL); layer_on(1); break;
  }
}

void ctl_reset (tap_dance_state_t *state, void *user_data) {
  switch (ctltap_state.state) {
  case SINGLE_TAP: break;
  case SINGLE_HOLD: unregister_code(KC_LCTL); break;
  case DOUBLE_TAP: break;
  case DOUBLE_HOLD: layer_off(MACROS); unregister_code(KC_LCTL); break;
  }
  ctltap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
         [CTL_OSL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctl_finished, ctl_reset)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
      case KC_TRNS:
      case KC_LCTL:
      case KC_NO:
        if (record->event.pressed && is_oneshot_layer_active()){
          clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        return true;
      default:
        return true;
      }
      return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {
  case SS_EML:
    if (record->event.pressed) {
      SEND_STRING("eyalgindi@gmail.com");

    }
    return false;
  case KC_PDOT:  // Types [], {}, or <> and puts cursor between braces.
    if (record->event.pressed) {
      clear_oneshot_mods();  // Temporarily disable mods.
      unregister_mods(MOD_MASK_CSAG);
      if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
        SEND_STRING("()");
      } else if ((mods | oneshot_mods) & MOD_MASK_ALT) {
        SEND_STRING("[]");
      } else if ((mods | oneshot_mods) & MOD_MASK_GUI) {
        SEND_STRING("{}");
      } else if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        SEND_STRING("<>");
      } else {SEND_STRING("."); return false;}
      tap_code(KC_LEFT);  // Move cursor between braces.
      register_mods(mods);  // Restore mods.
    }
    return false;
  }
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  return true;
}



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MACROS] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif
