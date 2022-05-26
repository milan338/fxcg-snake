#ifndef TEXT_H
#define TEXT_H

#include <fxcg/display.h>

// PrintXY with extra two spaces of padding included
#define print_xy(X, Y, MESSAGE, MODE, COLOR) PrintXY(X, Y, "  " MESSAGE, MODE, COLOR)

#endif // TEXT_H
