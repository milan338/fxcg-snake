#include <fxcg/display.h>
#include <string.h>
#include "draw.h"

void setup_view()
{
    // Fill VRAM with white pixels
    Bdisp_AllClr_VRAM();
    // Redraw status header
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
