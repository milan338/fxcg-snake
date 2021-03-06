#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdarg.h>
#include <string.h>
#include "../views/view_opt.h"
#include "draw.h"

static unsigned short *vram = NULL;

void update_vram_addr(void)
{
    vram = GetVRAMAddress();
}

void setup_view(void)
{
    // Fill VRAM with white pixels
    Bdisp_AllClr_VRAM();
    // Redraw status header
    DisplayStatusArea();
}

void update_view(void)
{
    // Put VRAM on screen
    Bdisp_PutDisp_DD();
}

void update_status_area(void)
{
    int len;
    char speed_text[30] = "   Speed: ";
    const char *speed_name = get_speed_name(&len);
    memcpy(speed_text + 10, speed_name, len);
    DefineStatusMessage(speed_text, 0, TEXT_COLOR_BLACK, 0);
    DefineStatusAreaFlags(3, SAF_BATTERY | SAF_TEXT, 0, 0);
    DisplayStatusArea();
}

void draw_fkey_label(int fkey, int bitmap)
{
    int iresult;
    GetFKeyPtr(bitmap, &iresult);
    FKey_Display(fkey, (int *)iresult);
}

void draw_fkey_labels(size_t size, const Fkey *fkeys)
{
    for (size_t i = 0; i < size; i++)
        draw_fkey_label(fkeys[i].fkey, fkeys[i].bitmap);
}

int draw_msg_box(int n_lines, const int *keys, int n_keys, ...)
{
    va_list args;
    MsgBoxPush(5);
    va_start(args, n_keys);
    char *msg;
    for (int i = 0; i < n_lines; i++)
    {
        msg = va_arg(args, char *);
        PrintXY(3, i + 2, msg, TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_BLACK);
    }
    va_end(args);
    int key;
    while (1)
    {
        GetKey(&key);
        for (int i = 0; i < n_keys; i++)
            if (key == keys[i])
                goto pop_msg_box;
    }
pop_msg_box:
    MsgBoxPop();
    return key;
}

void draw_rect(int x1, int x2, int y1, int y2, color_t color)
{
    __builtin_prefetch(&vram, 0, 3);
    unsigned short *ptr = vram;
    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            *pixel_at(x, y, ptr) = color;
        }
    }
}
