#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>
#include <stdbool.h>
#include "../types.h"
#include "../util/draw.h"
#include "../util/keyboard.h"
#include "view_game.h"

// TODO store direction

static iVec2 snake[N_BLOCKS] = {[0 ... N_BLOCKS - 1] = {EMPTY_COORD, EMPTY_COORD}};
static iVec2 dir = {1, 0};
static iVec2 apple = {EMPTY_COORD, EMPTY_COORD};
static unsigned int snake_size = 0;

// static inline void draw_snake_block(int i, color_t color)
// {
//     x1 = GRID_X1 + snake[i].x * BLOCK_SIZE;
//     x2 = x1 + BLOCK_SIZE - 1;
//     y1 = GRID_Y1 + snake[i].y * BLOCK_SIZE;
//     y2 = y1 + BLOCK_SIZE - 1;
//     draw_rect(x1, x2, y1, y2, color);
// }

bool is_intersecting(void)
{
    const iVec2 head = snake[snake_size - 1];
    // Check for playfield bounds intersections
    if (__builtin_expect(head.x >= GRID_W || head.x <= 0 || head.y >= GRID_H || head.y <= 0, false))
        return true;
    // Check for snake body intersection
    for (int i = 0; i < snake_size - 1; i++)
    {
        if (__builtin_expect(snake[i].x == head.x || snake[i].y == head.y, false))
            return true;
    }
    return false;
}

void draw_game(void)
{
    // Update status display
    DisplayStatusArea();
    // Draw background
    draw_rect(0, SCREEN_W, OFFSET_TOP, SCREEN_H, COLOR_BLACK);
    // Draw snake body and head
    int i = 0;
    for (i = 0; i < snake_size - 1; i++)
        draw_block(snake[i].x, snake[i].y, COLOR_GREEN);
    draw_block(snake[i].x, snake[i].y, COLOR_WHITE);
    // Draw apple
    draw_block(apple.x, apple.y, COLOR_RED);
    // Game over
    if (__builtin_expect(is_intersecting(), false))
    {
    }
    // Push modified VRAM to screen
    update_view();
}

void view_game(void)
{
    // Clear frame
    setup_view();
    int last_ticks = RTC_GetTicks();
    int delay_ms = 1000;

    snake[0] = (iVec2){5, 5};
    snake[1] = (iVec2){6, 5};
    snake_size = 2;
    // snake[1] = {5, 6};

    draw_game();
    int a = 0;
    // Game loop
    while (1)
    {

        // TODO use this for actual hardware
        // Update key arrays
        // key_update();
        // if (is_key_down(KEY_CTRL_F2))
        // {
        //     setup_view();
        //     print_xy(1, 2, "f2 pressed", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLUE);
        //     update_view();
        // }
        // if (is_key_down(KEY_PRGM_MENU))
        // {
        //     int key;
        //     // Let OS handle menu key
        //     GetKey(&key);
        // }

        // Game loop - under non-blocking delay
        if (RTC_Elapsed_ms(last_ticks, delay_ms))
        {
            last_ticks = RTC_GetTicks();

            for (int i = 0; i < snake_size; i++)
            {
                snake[i].x++;
            }

            draw_game();
        }
        // ! Temporary for work on emulator
        int key = PRGM_GetKey();
        switch (key)
        {
        case 79:
            break;
        case 48:
            GetKey(&key);
            break;
        }
    }
}
