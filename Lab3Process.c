#include "3140_concur.h"
#include <stdlib.h>
#include <MK64F12.h>

// globals
process_t* process_queue= NULL;
process_t* current_process= NULL;

struct process_state {
				// vars needed for process state
				unsigned int* sp; // stack pointer
				unsigned int* osp; // original stack pointer
				unsigned int size; // size of process
				unsigned int process_status; // status
				struct process_state* next; // next process ( for queue)
			};

void enqueue(process_t* proc) {
	// if queue empty, given process is the head
	if (process_queue == NULL) { process_queue = proc; }
	else { // if not empty
		process_t* temp = process_queue;
		// find end of queue
		while ( temp->next != NULL ) {
			temp = temp->next;
		}
		// put process at the end
		temp->next = proc;
	}
}

process_t* dequeue(void) {
	// set head process to process after the head and return it
	process_queue = process_queue->next;
	return process_queue;
}
			
			
int process_create (void (*f)(void), int n) {
	// allocate memory for new process
	process_t* p = (process_t*) malloc( sizeof(process_t));
	
	//init process state
	p->sp = process_stack_init( (*f), n);
	p->osp = process_queue->sp;
	p->size = n;
	p->process_status = 0;
	p->next = NULL;
	
	// checks for error (couldn't allocate memory
	if ( p->sp == NULL) { return -1; }
	
	// adds process to the queue
	enqueue( p );
	
	// if no error, return 0
	return 0;
}

void process_start (void) {
	//enable inturupts
	NVIC_EnableIRQ(PIT0_IRQn);
	
	//set up PIT
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK; // Enable clock to PIT module
	PIT->MCR =0x00; // Allows me to turn timer on
	PIT->CHANNEL[0].LDVAL = SystemCoreClock /10000; // ~1 second
	PIT->CHANNEL[0].TCTRL |= (1 << 1); // Enable Interrupts
	//PIT->CHANNEL[0].TCTRL |= (1 << 0); // Start timer
	// begin
	process_begin();
}

unsigned int* process_select(unsigned int* cursp) {
	// no currently running process or process terminated
	if ( current_process == NULL ) {
		current_process = process_queue;
	}
	else if (cursp == NULL) {
		process_stack_free( current_process->osp, current_process->size);
		current_process = dequeue();
	}
	else { // stopped a process
			//add back to queue
			enqueue(current_process);
			
		  // make temp
			process_t* temp = current_process;
		
			// get next process
			current_process = dequeue();
		
		  // fix the stack pointer and next
			temp->sp = cursp;
			temp->next = NULL;
	}
	
		// if no next process. return NULL
		if ( current_process == NULL ) { return NULL; }
		
		// otherwise return next stack pointer
		return current_process->sp;
}


