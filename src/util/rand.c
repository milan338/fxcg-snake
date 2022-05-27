// Based on https://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf, section 7.20.2.1
#include "rand.h"

static unsigned long int next = 1;

unsigned int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}
