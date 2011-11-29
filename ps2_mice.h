#ifndef _PS2_MICE_H
#define _PS2_MICE_H 1


#define MICE_CLK_PORT   PORTB
#define MICE_CLK_DDR    DDRB
#define MICE_CLK_bm     PB2

#define MICE_CLK_INT_vect INT2_vect

#define MICE_DAT_PORT   PORTB
#define MICE_DAT_DDR    DDRB
#define MICE_DAT_PIN    PINB
#define MICE_DAT_bm     PB0

#define MICE_DAT()      MICE_DAT_PIN & (~_BV(MICE_DAT_bm))
#define MICE_DAT_OUT()  MICE_DAT_DDR |= _BV(MICE_DAT_bm)
#define MICE_DAT_IN()   MICE_DAT_DDR &= ~_BV(MICE_DAT_bm)

typedef struct 
{
    // internal use only
    unsigned char frames_count;
    unsigned char tmp;

    // external use
    unsigned char flags;
    unsigned char x_mov;
    unsigned char y_mov;
} PS2_MICE_CONTENT_t;
static volatile PS2_MICE_CONTENT_t ps2_mice;


void mice_init(void);



#endif
