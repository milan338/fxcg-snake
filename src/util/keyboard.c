// Adapted from https://prizm.cemetech.net/index.php?title=Debouncing_Multiple-Keypress_PRGM_GetKey
#include <stdbool.h>
#include <string.h>
#include "keyboard.h"

bool key_down_last(int keycode, unsigned short buff[8])
{
    int row = keycode % 10;
    int col = keycode / 10 - 1;
    int word = row >> 1;
    int bit = col + 8 * (row & 1);
    return (0 != (buff[word] & 1 << bit));
}
