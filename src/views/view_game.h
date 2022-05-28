#ifndef VIEW_GAME_H
#define VIEW_GAME_H

#define BORDER_SIDE_W 2
#define BORDER_BOTTOM_H 1

#define BLOCK_SIZE 19

#define GRID_X1 BORDER_SIDE_W
#define GRID_X2 SCREEN_W - BORDER_SIDE_W
#define GRID_Y1 OFFSET_TOP
#define GRID_Y2 SCREEN_H - BORDER_BOTTOM_H

#define GRID_W (GRID_X2 - GRID_X1) / BLOCK_SIZE
#define GRID_H (GRID_Y2 - GRID_Y1) / BLOCK_SIZE

#define N_BLOCKS (GRID_W) * (GRID_H)

#define BG_COLOR COLOR_BLACK
#define SNAKE_HEAD_COLOR COLOR_WHITE
#define SNAKE_BODY_COLOR COLOR_GREEN
#define APPLE_COLOR COLOR_RED

#define EMPTY_COORD 255

#define STR_UNUSED "  "

extern int _delay_ms;

void view_game(void);

#endif // VIEW_GAME_H
