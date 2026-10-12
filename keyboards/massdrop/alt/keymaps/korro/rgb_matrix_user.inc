RGB_MATRIX_EFFECT(KORRO)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool KORRO(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        uint8_t flags = g_led_config.flags[i];
        HSV hsv = rgb_matrix_config.hsv;

        if (HAS_FLAGS(flags, LED_FLAG_UNDERGLOW)) {
            hsv.h += 85;
        } else if (HAS_FLAGS(flags, LED_FLAG_MODIFIER)) {
            hsv.h += 128;
        }

        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
