#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "util/draw.h"
#include "views/view_home.h"
#include "views/view_opt.h"

int _delay_ms;

int main(void)
{
    // Use 3-bit color mode
    Bdisp_EnableColor(0);
    update_vram_addr();
    update_status_area();
    update_delay_ms();
    // Begin main window loop
    view_home();
    return 0;
}
