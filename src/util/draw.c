#include <fxcg/display.h>
#include <string.h>
#include "draw.h"

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

void draw_point(int x, int y, color_t color)
{
    *pixel_at(x, y) = color;
}

void draw_rect(int x1, int x2, int y1, int y2, color_t color)
{
    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            *pixel_at(x, y) = color;
        }
    }
}
