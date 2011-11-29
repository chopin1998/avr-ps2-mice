#include "common.h"
#include "ps2_mice.h"



ISR (MICE_CLK_INT_vect)
{
    PORTD ^= 0x04;

    
}



void mice_init(void)
{
    MICE_DAT_DDR &= ~_BV(MICE_DAT_bm); // input
    MICE_DAT_PORT |= _BV(MICE_DAT_bm); // pull up

    MICE_CLK_DDR &= ~_BV(MICE_CLK_bm); // input
    MICE_CLK_PORT |= _BV(MICE_CLK_bm); // pull up
    
    EICRA = _BV(ISC21); // INT2 as falling edge
    EIMSK = _BV(INT2);          // enable int2

    memset(&ps2_mice, 0x00, sizeof(ps2_mice));
}
