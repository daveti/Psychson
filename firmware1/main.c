#include "defs.h"

extern void tmr1isr(void) __interrupt TMR1_VECT;

DWORD wait_tick;

void InitHardware()
{
	//Set up RAM mapping just beyond our own code
	BANK0PAL = BANK0_PA>>9;
	BANK0PAH = BANK0_PA>>17;
	BANK1VA  = BANK1_VA>>8;
	BANK1PAL = BANK1_PA>>9;
	BANK1PAH = BANK1_PA>>17;
	BANK2VA  = BANK2_VA>>8;
	BANK2PAL = BANK2_PA>>9;
	BANK2PAH = BANK2_PA>>17;

	XVAL(0xF809) = 7;
	XVAL(0xF80A) = 0x1F;
	XVAL(0xF810) = 0x60;
	XVAL(0xF811) = 0;
	XVAL(0xF08F) = 0;

	XVAL(0xFA6F) = 0x1F;
	XVAL(0xFA60) = 2;
	XVAL(0xFA61) = 0;
	XVAL(0xFA64) = 0;
	XVAL(0xFA65) = 0;
	XVAL(0xFA66) = 0;
	XVAL(0xFA67) = 0;
	XVAL(0xFA62) = 0x0F;
	XVAL(0xFA6F) = 0x1F;

	GPIO0DIR &= 0xFD;
	GPIO0OUT |= 2;

	XVAL(0xFA21) = 7;
	XVAL(0xFA21) &= 0xFB;

	XVAL(0xFA68) &= 0xF7;
	XVAL(0xFA69) &= 0xF7;
	XVAL(0xFA6A) &= 0xF7;
	XVAL(0xFA6B) &= 0xF7;

	XVAL(0xFE00) = 0;
	XVAL(0xFE00) = 0x80;

	XVAL(0xFA50) = 0x20;

	XVAL(0xFE01) = 0;
	XVAL(0xFE02) = 0x45;

	TMOD = 0x11;
	TH0 = 0xF0;
	TL0 = 0x5F;
	TH1 = 0xF0;
	TL1 = 0x5F;
	IP = 1;
	TCON = 0x10;
	SCON = 0;
	IE = 0x80;
}

void DoUSBRelatedInit()
{
	if (WARMSTATUS & 2)
	{
		return;
	}

	REGBANK = 5;
	XVAL(0xF210) = 0xFF;
	XVAL(0xF211) = 2;
	XVAL(0xF212) = 3;
	XVAL(0xF213) = 0x24;
	REGBANK = 0;
	XVAL(0xFA6B) = 0xFF;
	while((XVAL(0xF014) & 3)==0);
}

void main()
{
	InitHardware();
	DoUSBRelatedInit();

	while (1) {
		wait_tick++;
	}
}
