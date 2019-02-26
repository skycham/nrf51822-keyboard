/**
 * @brief 基础键盘配列
 * 
 * @file keymap_plain.c
 * @author Jim Jiang
 * @date 2018-05-13
 */
#include "keymap_common.h"
#include "keyboard_fn.h"

/** ??Keymap?? */
#ifdef KEYBOARD_4100
const uint8_t keymaps[2][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP( \
           ESC, F1, F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  NLCK, PSCR, SLCK, PAUS, \
                1,   2,   3,   4,   5,   6,   7,   8,   9,    0,  MINS,  EQL, BSPC, HOME, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,    P,  LBRC, RBRC, BSLS, PGUP, \
           CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L, SCLN,  QUOT,    ENT,   PGDOWN, \
           LSFT,  Z,   X,   C,   V,   B,   N,   M,   COMM,  DOT,  SLSH, RSFT,   UP,  END, \
           LCTL,FN0,LALT, GRV,         SPC,          RALT,  INS,   DEL, LEFT, DOWN, RIGHT ),
    /* 1: Fn */       
    KEYMAP( \
         TRNS, F11, F12,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS,  TRNS, TRNS, TRNS, FN1, \
              TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  P7,  P8,  P9, PAST,  TRNS, TRNS, TRNS, TRNS, \
         FN2,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  P4,  P5,  P6, PMNS,  TRNS, TRNS, TRNS, TRNS, \
         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  P1,  P2,  P3, PPLS,  TRNS,     PENT,   TRNS, \
         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  P0,   TRNS, PDOT,  PSLS,  TRNS, TRNS, TRNS, \
         RCTL,FN0, LGUI,TRNS,       TRNS,           TRNS, TRNS,  TRNS,  TRNS, TRNS, TRNS ),       
};

const action_t PROGMEM fn_actions[] = {
    ACTION_LAYER_MOMENTARY(1), 
    ACTION_FUNCTION(POWER_SLEEP),
    ACTION_FUNCTION(SWITCH_DEVICE)
};

#endif

#ifdef KEYBOARD_60

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP_ANSI(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
        LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     FN4,  \
        LCTL,LGUI,LALT,          SPC,                     FN0, FN1, FN2, FN3),
    /* 1: Poker Fn */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PGUP,PGDN,INS,  \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,END,      TRNS, \
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,VOLD,VOLU,MUTE,     UP,   \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,LEFT,DOWN,RGHT),
	  /* 1: system key */
	    KEYMAP_ANSI(
        FN5 ,MYCM,MAIL,CALC,EJCT,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BOOTLOADER, \
        FN6 ,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS),
};
const action_t PROGMEM fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_TAP_KEY(1, KC_DELETE),
    [1] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_LEFT),
    [2] = ACTION_LAYER_TAP_KEY(2, KC_DOWN),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RIGHT),
    [4] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [5] = ACTION_FUNCTION(POWER_SLEEP),
    [6] = ACTION_FUNCTION(SWITCH_DEVICE),
};

#endif

