#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdbool.h>
#include "../util/draw.h"
#include "../util/text.h"
#include "view_game.h"
#include "view_help.h"
#include "view_home.h"
#include "view_opt.h"

void draw_home(void)
{
    setup_view();
    const Fkey fkeys[] = {
        {F1, 0x0404},
        {F5, 0x0319},
        {F6, 0x0509}};
    const size_t size = sizeof(fkeys) / sizeof(fkeys[0]);
    draw_fkey_labels(size, fkeys);
    print_xy(1, 1, "fx-CG Snake", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLUE);
    print_xy(1, 3, "By milan338", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    print_xy(1, 4, "github.com/milan338", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    // 0372 or 0x040A - black arrow
    // 00FD - menu
    // 02B1 - back
    // 0319 - opt
    // 0404 - play
    // 0509 - help
}

void view_home(void)
{
    int key;
    bool redraw;
    // Initial draw
    draw_home();
    // Main window loop
    while (1)
    {
        // Redraw menu on return from sub-menu
        redraw = true;
        // Wait for user input
        GetKey(&key);
        switch (key)
        {
        case KEY_CTRL_F1:
            view_game();
            break;
        case KEY_CTRL_F5:
            view_opt();
            break;
        case KEY_CTRL_F6:
            view_help();
            break;
        default:
            redraw = false;
            break;
        }
        if (redraw)
            draw_home();
    }
}
