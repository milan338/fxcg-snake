#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <string.h>

#define KEYBOARD_REGISTER 0xA44B0000

bool key_down_last(int keycode, unsigned short buff[8]);

// Update keypress buffers before polling
static inline void key_update(unsigned short last_key[8], unsigned short hold_key[8])
{
    memcpy(hold_key, last_key, sizeof(unsigned short) * 8);
    memcpy(last_key, (unsigned short *)KEYBOARD_REGISTER, sizeof(unsigned short) * 8);
}

// Non-blocking debounced key polling
static inline bool is_key_down(int keycode, unsigned short last_key[8], unsigned short hold_key[8])
{
    return key_down_last(keycode, last_key) && key_down_last(keycode, hold_key);
}

static inline bool is_key_up(int keycode, unsigned short last_key[8], unsigned short hold_key[8])
{
    return !key_down_last(keycode, last_key) && !key_down_last(keycode, hold_key);
}

#endif // KEYBOARD_H
