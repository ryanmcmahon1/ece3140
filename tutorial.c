#include <MK64F12.h>
unsigned int counter = 0;
unsigned int toggle = 0;

void LEDRed_Setup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable clock to port B
	PORTB->PCR[22] = PORT_PCR_MUX(001); // Set up PTB22 as GPIO
	PTB->PDDR = (1 << 22); // Enable PTB22 as GPIO output
}

void LEDRed_On() {
	PTB->PSOR = (0 << 22);
	PTB->PCOR = (1 << 22);
}

void LEDRed_Off() {
	PTB->PSOR = (1 << 22);
	PTB->PCOR = (0 << 22);
}

// This function sets up the blue LED for use
void LEDBlue_Setup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable clock to port B
	PORTB->PCR[21] = PORT_PCR_MUX(001); // Set up PTB22 as GPIO
	PTB->PDDR = (1 << 21); // Enable PTB21 as GPIO output
}

// This function turns on the blue LED using PSOR/PCOR registers
void LEDBlue_On() {
	PTB->PSOR = (0 << 21);
	PTB->PCOR = (1 << 21);
}

// This function turns off the blue LED using PSOR/PCOR registers
void LEDBlue_Off() {
	PTB->PSOR = (1 << 21);
	PTB->PCOR = (0 << 21);
}

void LEDGreen_Setup() {
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; // Enable clock to port E
	PORTE->PCR[26] = PORT_PCR_MUX(001); // Set up PTE26 as GPIO
	PTE->PDDR = (1 << 26); // Enable PTE26 as GPIO output
}

void LEDGreen_On() {
	PTE->PSOR = (0 << 26);
	PTE->PCOR = (1 << 26);
}

void LEDGreen_Off() {
	PTE->PSOR = (1 << 26);
	PTE->PCOR = (0 << 26);
}

int main (void) {
	LEDGreen_Setup();
	LEDGreen_Off();

	while (1) {
		counter++;
		if (counter > 0xFFFFF) {
			if (toggle == 0) {
				LEDGreen_On();
				toggle = 1;
			}
			
			else {
				LEDGreen_Off();
				toggle = 0;
			}
			
			counter = 0;
		}
	}
}
