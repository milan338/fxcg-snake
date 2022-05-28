#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>
#include <stdbool.h>
#include "../types.h"
#include "../util/draw.h"
#include "../util/keyboard.h"
#include "../util/rand.h"
#include "view_game.h"

bool is_intersecting(uiVec2 *snake, unsigned int snake_size)
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

static inline void change_dir(const iVec2 *new_dir, iVec2 *dir, uiVec2 *snake, unsigned int snake_size)
{
    // Don't move back into body
    if (__builtin_expect_with_probability(
            snake[0].x + new_dir->x == snake[1].x && snake[0].y + new_dir->y == snake[1].y,
            false, 0.75))
        return;
    dir->x = new_dir->x;
    dir->y = new_dir->y;
}

static inline void spawn_apple(uiVec2 *snake, uiVec2 *apple, unsigned int snake_size)
{
    bool invalid;
    do
    {
        invalid = false;
        apple->x = rand() % GRID_W;
        apple->y = rand() % GRID_H;
        for (int i = 0; i < snake_size; i++)
            if (apple->x == snake[i].x && apple->y == snake[i].y)
                invalid = true;
    } while (invalid);
}

static inline void grow_snake(uiVec2 *snake, uiVec2 *apple, const uiVec2 *last_tail, unsigned int *snake_size)
{
    // Win condition checked prior - won't cause out-of-bounds write
    snake[*snake_size].x = last_tail->x;
    snake[*snake_size].y = last_tail->y;
    (*snake_size)++;
    // Respawn apple
    spawn_apple(snake, apple, *snake_size);
}

void move_snake(uiVec2 *snake, uiVec2 *last_tail, const iVec2 *dir, unsigned int snake_size)
{
    // Store current position of tail to use as the new tail when growing
    last_tail->x = snake[snake_size - 1].x;
    last_tail->y = snake[snake_size - 1].y;
    // Move each ith body part to the position of the i-1th
    for (int i = snake_size - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    // Move head
    snake[0].x += dir->x;
    snake[0].y += dir->y;
}

void draw_game(const uiVec2 *snake, const uiVec2 *apple, unsigned int snake_size)
{
    // Draw background
    draw_rect(0, SCREEN_W, OFFSET_TOP, SCREEN_H, BG_COLOR);
    // Draw snake body and head
    int i;
    for (i = snake_size - 1; i > 0; i--)
        draw_block(snake[i].x, snake[i].y, SNAKE_BODY_COLOR);
    draw_block(snake[i].x, snake[i].y, SNAKE_HEAD_COLOR);
    // Draw apple
    draw_block(apple->x, apple->y, APPLE_COLOR);
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
    static unsigned short last_key[8];
    static unsigned short hold_key[8];
    static const iVec2 dir_left = {-1, 0};
    static const iVec2 dir_right = {1, 0};
    static const iVec2 dir_up = {0, -1};
    static const iVec2 dir_down = {0, 1};
    static const int pause_keys[] = {KEY_CTRL_F1, KEY_CTRL_F2, KEY_CTRL_EXIT};
    static const int game_end_keys[] = {KEY_CTRL_EXIT};
    unsigned int snake_size = 2;
    int last_ticks = RTC_GetTicks();
    int delay_ms = _delay_ms;
    int key;
    uiVec2 snake[N_BLOCKS] = {[0 ... N_BLOCKS - 1] = {EMPTY_COORD, EMPTY_COORD}};
    uiVec2 apple = {EMPTY_COORD, EMPTY_COORD};
    uiVec2 last_tail = {EMPTY_COORD, EMPTY_COORD};
    iVec2 dir = {1, 0};
    snake[0] = (uiVec2){9, 5};
    snake[1] = (uiVec2){8, 5};
    srand(last_ticks);
    // Draw initial frame
    spawn_apple(snake, &apple, snake_size);
    draw_game(snake, &apple, snake_size);
    // Game loop
    while (1)
    {
        // Update key arrays
        key_update(last_key, hold_key);
        // Handle input
        if (__builtin_expect(is_key_down(KEY_PRGM_EXIT, last_key, hold_key), false))
        {
            key = draw_msg_box(5, pause_keys, 3, "  Game Paused", STR_UNUSED, STR_UNUSED, "  Resume: [F1]", "  Quit: [F2]");
            if (key == KEY_CTRL_F2)
                return;
        }
        else if (__builtin_expect(is_key_down(KEY_PRGM_MENU, last_key, hold_key), false))
        {
            // Let os handle menu key
            GetKey(&key);
            return;
        }
        if (is_key_down(KEY_PRGM_LEFT, last_key, hold_key))
            change_dir(&dir_left, &dir, snake, snake_size);
        if (is_key_down(KEY_PRGM_RIGHT, last_key, hold_key))
            change_dir(&dir_right, &dir, snake, snake_size);
        if (is_key_down(KEY_PRGM_UP, last_key, hold_key))
            change_dir(&dir_up, &dir, snake, snake_size);
        if (is_key_down(KEY_PRGM_DOWN, last_key, hold_key))
            change_dir(&dir_down, &dir, snake, snake_size);
        // Game loop - under non-blocking delay
        if (RTC_Elapsed_ms(last_ticks, delay_ms))
        {
            last_ticks = RTC_GetTicks();
            // Progress snake
            move_snake(snake, &last_tail, &dir, snake_size);
            // Game over
            if (__builtin_expect(is_intersecting(snake, snake_size), false))
            {
                draw_msg_box(5, game_end_keys, 1, "  Game Over", STR_UNUSED, STR_UNUSED, STR_UNUSED, "  Press: [EXIT]");
                return;
            }
            // Snake eats apple
            if (__builtin_expect(snake[0].x == apple.x && snake[0].y == apple.y, false))
            {
                // Win condition
                if (__builtin_expect(snake_size == N_BLOCKS, false))
                {
                    draw_msg_box(5, game_end_keys, 1, "  You Win", STR_UNUSED, STR_UNUSED, STR_UNUSED, "  Press: [EXIT]");
                    return;
                }
                // Didn't win, keep playing
                grow_snake(snake, &apple, &last_tail, &snake_size);
            }
            draw_game(snake, &apple, snake_size);
        }
    }
}
