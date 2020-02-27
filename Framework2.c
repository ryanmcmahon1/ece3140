#include <MK64F12.h>

// This function sets up the PIT timer and enables interrupts
void pit_setup() {
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK; // Enable clock to PIT module
	PIT_MCR = 1;
	PIT_TCTRL(0) = 3; // interrupts are enabled
	PIT_TCTRL(1) = 3;
	PIT->CHANNEL[0].LDVAL = 0xFFFFFF; // Set load value of zeroth PIT
}

// Sets up blue LED by enabling clock and setting PTB21 as GPIO output
void blue_ledsetup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable clock to port B
	PORTB->PCR[21] = PORT_PCR_MUX(001); // Set up PTB21 as GPIO
	PTB->PDDR = (1 << 21); // Enable PTB21 as GPIO output
}

// This function turns on the blue LED using PSOR/PCOR registers
void blue_ledon() {
	PTB->PSOR = (0 << 21);
	PTB->PCOR = (1 << 21);
}

// This function turns off the blue LED using PSOR/PCOR registers
void blue_ledoff() {
	PTB->PSOR = (1 << 21);
	PTB->PCOR = (0 << 21);
}

// Sets up green LED by enabling clock and setting PTE26 as GPIO output
void green_ledsetup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; // Enable clock to port E
	PORTE->PCR[26] = PORT_PCR_MUX(001); // Set up PTE26 as GPIO
	PTE->PDDR = (1 << 26); // Enable PTE26 as GPIO output
}

// Turns on the green LED using the PCOR/PSOR registers
void green_ledon() {
	PTE->PSOR = (0 << 26);
	PTE->PCOR = (1 << 26);
}

// Turns off the green LED using the PCOR/PSOR registers
void green_ledoff() {
	PTE->PSOR = (1 << 26);
	PTE->PCOR = (0 << 26);
}

int main (void)
{
	  NVIC_EnableIRQ(PIT0_IRQn); /* enable PIT0 Interrupts (for part 2) */

	  while (1) {
			
		}
}


/* 
     PIT Interrupt Handler
*/
void PIT0_IRQHandler(void)
{
	PIT_TFLG0 = 1; // writing 1 to TFLG to clear interrupt flag
}
