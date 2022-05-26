#ifndef UTIL_DRAW_H
#define UTIL_DRAW_H

#include <stddef.h>

typedef enum
{
    F1,
    F2,
    F3,
    F4,
    F5,
    F6
} f_key_e;

typedef struct
{
    int fkey;
    int bitmap;
} Fkey;

void setup_view();
void draw_fkey_label(int fkey, int bitmap);
void draw_fkey_labels(size_t size, const Fkey *fkeys);

#endif // UTIL_DRAW_H
