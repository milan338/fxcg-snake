#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdbool.h>
#include "../util/draw.h"
#include "../util/text.h"
#include "view_home.h"

void draw_home()
{
    setup_view();
    const Fkey fkeys[] = {
        {F1, 0x0006}};
    const size_t size = sizeof(fkeys) / sizeof(fkeys[0]);
    draw_fkey_labels(size, fkeys);
    print_xy(1, 1, "fx-CG Snake", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLUE);
    print_xy(1, 3, "High Score:", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    print_xy(1, 7, "F1: Play", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
}

void view_home()
{
    int key;
    // Initial draw
    draw_home();
    // Main window loop
    while (1)
    {
        // Redraw menu on return from sub-menu
        bool redraw = true;
        // Wait for user input
        GetKey(&key);
        switch (key)
        {
        case KEY_CTRL_F1:
            break;
        default:
            redraw = false;
            break;
        }
        if (redraw)
            draw_home();
    }
}
