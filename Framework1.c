#include <MK64F12.h>

unsigned int toggle = 0;
unsigned int tflg, count, time;

void pit_setup() {
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK; // Enable clock to PIT module
	PIT_MCR = 1;
	PIT_TCTRL(0) = 1;
	PIT_TCTRL(1) = 1;
	PIT->CHANNEL[0].LDVAL = 0xFFFFFF; // Set load value of zeroth PIT
	time = PIT_CVAL0;
}

void red_ledsetup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable clock to port B
	PORTB->PCR[22] = PORT_PCR_MUX(001); // Set up PTB22 as GPIO
	PTB->PDDR = (1 << 22); // Enable PTB22 as GPIO output
}

void red_ledon() {
	PTB->PSOR = (0 << 22);
	PTB->PCOR = (1 << 22);
}

void red_ledoff() {
	PTB->PSOR = (1 << 22);
	PTB->PCOR = (0 << 22);
}

int main (void)
{
	pit_setup(); // Setting up the PIT timer
	red_ledsetup(); // Setting up the red LED
	red_ledoff(); // Starting with the LED off
	tflg = PIT->CHANNEL[0].TFLG;
	tflg = PIT_TFLG0;
	
	while (1) {
		tflg = PIT->CHANNEL[0].TFLG;
		time = PIT_CVAL0;
		
		if ( PIT_TFLG0 == 1) {
			//PIT->CHANNEL[0].TFLG = 0;
			
			if (toggle == 0) {
				toggle = 1;
				red_ledon();
				//PIT_TCTRL(0) = 0;
				//PIT_TCTRL(0) = 1;
				PIT_TFLG0 = 1;
			}
			
			else {
				toggle = 0;
				red_ledoff();
				//PIT_TCTRL(0) = 0;
				//PIT_TCTRL(0) = 1;
				PIT_TFLG0 = 1;
			}
		}
	}
}
