#include <MK64F12.h>
unsigned int counter = 0;

int main (void) {
	while (1) {
		counter++;
		if (counter > 0xFF) {
			counter = 0;
		}
	}
}
