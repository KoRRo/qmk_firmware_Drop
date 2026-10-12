RGB_MATRIX_EFFECT(KORRO)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Underglow: indici 67-104 (vedi g_led_config in config_led.c)
#define KORRO_UG_TOP_FIRST    87
#define KORRO_UG_TOP_LAST     99
#define KORRO_UG_SPACE_FIRST  72
#define KORRO_UG_SPACE_LAST   74

// LED che prendono il colore degli alfanumerici anche se non lo sono di default
static bool korro_alpha_color(uint8_t i) {
    // Esc fisico (nel keymap e' il `) e frecce
    if (i == 0 || i == 56 || i == 64 || i == 65 || i == 66) return true;
    // Underglow: parte alta e tratto sotto la barra spaziatrice
    if (i >= KORRO_UG_TOP_FIRST && i <= KORRO_UG_TOP_LAST) return true;
    if (i >= KORRO_UG_SPACE_FIRST && i <= KORRO_UG_SPACE_LAST) return true;
    return false;
}

static bool KORRO(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        uint8_t flags = g_led_config.flags[i];
        HSV hsv = rgb_matrix_config.hsv;

        bool is_underglow = HAS_FLAGS(flags, LED_FLAG_UNDERGLOW);
        bool is_modifier  = HAS_FLAGS(flags, LED_FLAG_MODIFIER);

        if ((is_underglow || is_modifier) && !korro_alpha_color(i)) {
            hsv.h += 128;
        }

        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
