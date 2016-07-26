
static const uint8_t PROGMEM keymaps[][MATRIX_COLS][MATRIX_ROWS] = {
    /* Layer 0: Standard ANSI layer */
    KEYMAP(\
         ESC,     F1,  F2,  F3,  F4,     F5,  F6,  F7,  F8,     F9, F10, F11, F12,    PSCR,SLCK,PAUS,                          \
         GRV, NO,  1,   2,   3,   4,   5,  NO,    6,   7,   8,   9,   0,MINS, EQL,     INS,HOME,PGUP,   NLCK,PSLS,PAST,PMNS,   \
         TAB,    Q,   W,   E,   R,   T,BSLS,RBRC,   Y,   U,   I,   O,   P,   BSPC,     DEL, END,PGDN,     P7,  P8,  P9,  PPLS, \
         CAPS,  A,   S,   D,   F,   G,LBRC,  QUOT,   H,   J,   K,   L,SCLN,   ENT,                        P4,  P5,  P6,        \
         LSFT,       Z,   X,   C,   V,   B,NUBS,SLSH, N,   M,COMM, DOT,      RSFT,           UP,          P1,  P2,  P3,  PENT, \
         LCTL,  FN0,LGUI, LALT,     BSPC,   SPC,   ENT,     RALT, RGUI,MENU, RCTL,    LEFT,DOWN,RGHT,     P0,     PDOT),       \
    /* Layer 1: Function layer */
    KEYMAP(\
         CALC,     MYCM,WSCH,WHOM,MAIL,  VOLD,VOLU,MSEL,MSTP,   MPLY,MPRV,MNXT,TRNS,   WAKE, PWR,SLEP,                         \
         TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS, \
         TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,   TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS, \
         TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                      TRNS,TRNS,TRNS,      \
         TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,         TRNS,TRNS,TRNS,TRNS, \
         TRNS, TRNS,TRNS, TRNS,      TRNS  ,TRNS,  TRNS,      TRNS, TRNS,TRNS, TRNS,   TRNS,TRNS,TRNS,    TRNS,TRNS)
};

static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1)
};
