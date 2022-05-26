#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include "views/view_home.h"

int main(void)
{
    // Use 3-bit color mode
    Bdisp_EnableColor(0);
    // Begin main window loop
    view_home();
    return 0;
}
