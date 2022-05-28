#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <string.h>
#include "../util/draw.h"
#include "../util/text.h"
#include "view_game.h"
#include "view_opt.h"

const int delays[] = {2000, 1000, 750, 500, 250, 100, 50};
const char *speeds[] = {"Really Slow", "Slow", "Leisurely", "Medium", "Fast", "Really Fast", "Too Fast"};
const int speed_lens[] = {12, 5, 10, 7, 5, 12, 9};
const size_t n_delays = sizeof(delays) / sizeof(delays[0]);
int idelay = 3;

const char *get_speed_name(int *len)
{
    *len = speed_lens[idelay] + 1;
    return speeds[idelay];
}

void draw_opt(void)
{
    Bdisp_AllClr_VRAM();
    const Fkey fkeys[] = {
        {F6, 0x02B1}};
    const size_t size = sizeof(fkeys) / sizeof(fkeys[0]);
    char buff[20] = "  ";
    draw_fkey_labels(size, fkeys);
    print_xy(1, 1, "Options", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLUE);
    print_xy(1, 3, "Change speed:", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    print_xy(1, 4, "[D-PAD (UP, DOWN)]", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    memcpy(buff + 2, speeds[idelay], speed_lens[idelay] + 1);
    print_xy(1, 6, "Current speed:", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    PrintXY(1, 7, buff, TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    update_status_area();
}

void view_opt(void)
{
    int key;
    draw_opt();
    while (1)
    {
        draw_opt();
        // Update actual game delay
        set_delay_ms(delays[idelay]);
        GetKey(&key);
        switch (key)
        {
        case KEY_CTRL_F6:
            return;
        case KEY_CTRL_UP:
            if (idelay < n_delays - 1)
                idelay++;
            break;
        case KEY_CTRL_DOWN:
            if (idelay > 0)
                idelay--;
            break;
        }
    }
}
