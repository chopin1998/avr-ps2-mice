/*
 * Author: chopin1998@gmail.com
 */


#include "common.h"
#include "ps2_mice.h"

void init_uart(void);
void init_io(void);
void killdog(void);

uint8_t mcusr_mirror __attribute__((section (".noinit")));
void get_mcusr(void) __attribute__((naked)) __attribute__((section(".init3")));



ISR(TIMER0_COMPA_vect)
{
    static unsigned char i = 0;

    i++;

    if (i<254)
    {
        PORTD |= 0x08;
    }
    else
    {
        PORTD &= ~0x08;
    }
}

void timer_init(void)
{

    /* use timer0 as task timer */

    /* set timer 0 as CTC mode
       1024 pre_clock
       100 Hz
    */
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS02) | _BV(CS00);
    
    OCR0A = 100;

    TIMSK0 = _BV(OCIE0A);
}


int main()
{
    unsigned int i=0;
    
    killdog();

    init_io();
    uart_init();
    timer_init();
    mice_init();
    
    sei();

    uart_print("hello ps2 mouse\n");
    for(;;)
    {
        cmdrecv_uart_tick();
    }
    
    cli();
    wdt_enable(WDTO_500MS);     /* should not run here */
    for(;;);
}

void init_io()
{
    /*
     * PORTA
     */
    DDRA = 0x00;
    PORTA = 0x00;

    /*
     *  PORTB
     */
    DDRB = 0x00;
    PORTB = 0x00;

    /*
     * PORTC
     */
    DDRC = 0x00;
    PORTC = 0x00;

    /*
     * PORTD
     */    
    DDRD = 0x0c;
    PORTD = 0x0c;
}

void killdog(void)
{
    mcusr_mirror = MCUSR;
    MCUSR = 0;
    wdt_disable();
}
