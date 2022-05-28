#ifndef UTIL_DRAW_H
#define UTIL_DRAW_H

#include <stddef.h>
#include "../types.h"
#include "../views/view_game.h"

#define OFFSET_TOP 24
#define SCREEN_W 384
#define SCREEN_H 215

typedef enum f_key_e
{
    F1,
    F2,
    F3,
    F4,
    F5,
    F6
} f_key_e;

typedef struct Fkey
{
    f_key_e fkey;
    int bitmap;
} Fkey;

void update_vram_addr(void);

static inline unsigned short *pixel_at(int x, int y, unsigned short *ptr)
{
    return ptr + x + SCREEN_W * y;
}

void setup_view(void);
void update_view(void); // GetKey already calls this

void draw_fkey_label(int fkey, int bitmap);
void draw_fkey_labels(size_t size, const Fkey *fkeys);

void update_status_area(void);

int draw_msg_box(int n_lines, ...);

void draw_rect(int x1, int x2, int y1, int y2, color_t color);
// Draw point in playfield to screen
static inline void draw_block(uint8_t x, uint8_t y, color_t color)
{
    int x1 = GRID_X1 + x * BLOCK_SIZE;
    int x2 = x1 + BLOCK_SIZE - 1;
    int y1 = GRID_Y1 + y * BLOCK_SIZE;
    int y2 = y1 + BLOCK_SIZE - 1;
    draw_rect(x1, x2, y1, y2, color);
}

#endif // UTIL_DRAW_H
