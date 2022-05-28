#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "../util/draw.h"
#include "../util/text.h"
#include "view_help.h"

void draw_help(void)
{
    setup_view();
    const Fkey fkeys[] = {
        {F6, 0x02B1}};
    const size_t size = sizeof(fkeys) / sizeof(fkeys[0]);
    draw_fkey_labels(size, fkeys);
    print_xy(1, 1, "Controls", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLUE);
    print_xy(1, 3, "Movement: [D-PAD]", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    print_xy(1, 4, "Pause: [EXIT]", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
}

void view_help(void)
{
    int key;
    draw_help();
    while (1)
    {
        GetKey(&key);
        switch (key)
        {
        case KEY_CTRL_F6:
            return;
        }
    }
}
