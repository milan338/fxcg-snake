#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>
#include <stdbool.h>
#include "../types.h"
#include "../util/draw.h"
#include "../util/keyboard.h"
#include "../util/rand.h"
#include "view_game.h"

static uiVec2 snake[N_BLOCKS];
static uiVec2 apple;
static uiVec2 last_tail;
static iVec2 dir;
static unsigned int snake_size;

// TODO first time losing doesn't show game over screen

bool is_intersecting(void)
{
    // Check for playfield bounds intersections
    if (__builtin_expect(
            snake[0].x >= GRID_W || snake[0].x < 0 || snake[0].y >= GRID_H || snake[0].y < 0,
            false))
        return true;
    // Check for snake body intersection
    for (int i = 1; i < snake_size; i++)
    {
        if (__builtin_expect(snake[i].x == snake[0].x && snake[i].y == snake[0].y, false))
            return true;
    }
    return false;
}

bool change_dir(int8_t x, int8_t y)
{
    // Ignore when new dir same as current
    if (dir.x == x && dir.y == y)
        return false;
    // Don't move back into body
    if (__builtin_expect_with_probability(
            snake[0].x + x == snake[snake_size - 1].x && snake[0].y + y == snake[snake_size - 1].y,
            false, 0.75))
        return false;
    dir.x = x;
    dir.y = y;
    return true;
}

static inline void spawn_apple(void)
{
    bool invalid;
    do
    {
        invalid = false;
        apple.x = rand() % GRID_W;
        apple.y = rand() % GRID_H;
        for (int i = 0; i < snake_size; i++)
            if (apple.x == snake[i].x && apple.y == snake[i].y)
                invalid = true;
    } while (invalid);
}

void grow_snake(void)
{
    // Win condition checked prior - won't cause out-of-bounds write
    snake[snake_size].x = last_tail.x;
    snake[snake_size].y = last_tail.y;
    snake_size++;
    // Respawn apple
    spawn_apple();
}

void move_snake(void)
{
    // Store current position of tail to use as the new tail when growing
    last_tail.x = snake[snake_size - 1].x;
    last_tail.y = snake[snake_size - 1].y;
    // Move each ith body part to the position of the i-1th
    for (int i = snake_size - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    // Move head
    snake[0].x += dir.x;
    snake[0].y += dir.y;
}

void draw_game(void)
{
    // Draw background
    draw_rect(0, SCREEN_W, OFFSET_TOP, SCREEN_H, COLOR_BLACK);
    // Draw snake body and head
    int i;
    for (i = snake_size - 1; i > 0; i--)
        draw_block(snake[i].x, snake[i].y, COLOR_GREEN);
    draw_block(snake[i].x, snake[i].y, COLOR_WHITE);
    // Draw apple
    draw_block(apple.x, apple.y, COLOR_RED);
    // Update status display
    DisplayStatusArea();
    // Push modified VRAM to screen
    update_view();
}

void view_game(void)
{
    // Clear frame
    setup_view();
    // Init variables
    int last_ticks = RTC_GetTicks();
    int delay_ms = 1000;
    dir.x = 1;
    dir.y = 0;
    apple.x = apple.y = EMPTY_COORD;
    last_tail.x = last_tail.y = EMPTY_COORD;
    for (int i = 2; i < N_BLOCKS; i++)
        snake[i].x = snake[i].y = EMPTY_COORD;
    snake[0] = (uiVec2){6, 5};
    snake[1] = (uiVec2){5, 5};
    snake_size = 2;
    srand(last_ticks);
    // Draw initial frame
    spawn_apple();
    draw_game();
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
        game_loop_update:
            last_ticks = RTC_GetTicks();
            move_snake();
            // Game over
            if (__builtin_expect(is_intersecting(), false))
            {
                draw_msg_box(5, "  Game Over", STR_UNUSED, STR_UNUSED, STR_UNUSED, "  Press: [EXIT]");
                return;
            }
            // Snake eats apple
            if (__builtin_expect(snake[0].x == apple.x && snake[0].y == apple.y, false))
            {
                // Win condition
                if (__builtin_expect(snake_size == N_BLOCKS, false))
                {
                    draw_msg_box(5, "  You Win", STR_UNUSED, STR_UNUSED, STR_UNUSED, "  Press: [EXIT]");
                    return;
                }
                // Didn't win, keep playing
                grow_snake();
            }
            draw_game();
        }
        // ! Temporary for work on emulator
        int key = PRGM_GetKey();
        switch (key)
        {
        case 47: // EXIT
            key = draw_msg_box(5, "  Game Paused", STR_UNUSED, STR_UNUSED, "  Resume: [F1]", "  Quit: [F2]");
            if (key == KEY_CTRL_F2)
                return;
            break;
        case 38: // LEFT
            CHANGE_DIR(-1, 0)
            break;
        case 37: // DOWN
            CHANGE_DIR(0, 1)
            break;
        case 28: // UP
            CHANGE_DIR(0, -1)
            break;
        case 27: // RIGHT
            CHANGE_DIR(1, 0)
            break;
        case 48:
            GetKey(&key);
            break;
        }
    }
}
