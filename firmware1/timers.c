#include "defs.h"

static BYTE 	tmr1count;
static WORD	tmr1reload;

void tmr1isr(void) __interrupt TMR1_VECT
{
	TR1 = 0;
	TH1 = MSB(tmr1reload);
	TL1 = LSB(tmr1reload);
	tmr1count++;
	TR1 = 1;
}
