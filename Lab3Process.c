#include "3140_concur.h"
#include <stdlib.h>
#include <MK64F12.h>

unsigned int timer_value = 0xFFF;

process_t* process_queue = NULL;
process_t* current_process = NULL;

// process_state struct, with typedef process_t
struct process_state {
	int n;                        // Size of stack frame
	unsigned int* original_sp;    // Original stack pointer
	unsigned int* sp;             // Current Stack pointer
	struct process_state* next_p; // Next process
};

// This function sets up the PIT timer and enables interrupts
void pit_setup() {
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK; // Enable clock to PIT module
	PIT_MCR = 1;
	PIT_TCTRL(0) = 3; // interrupts are enabled
	PIT_TCTRL(1) = 3;
	PIT->CHANNEL[0].LDVAL = timer_value; // Set load value of zeroth PIT
}

// helper method that appends a process to the end of a queue
void enqueue(process_t* proc) {
	
	// Case 1: queue is empty, so add this process to the head
	if (process_queue == NULL) {
		process_queue = proc;
		proc->next_p = NULL;
	}
	
	// Case 2: queue is nonempty, so add this process to the end
	else {
		process_t* temp_p = process_queue;
		
		while (temp_p->next_p != NULL) {
			// Continue iterating until we get to the last element
			temp_p = temp_p->next_p;
		}
		
		// Set next pointer of this final element
		temp_p->next_p = proc;
		proc->next_p = NULL;
	}
}

// helper method that removes and returns process at head of queue
process_t* dequeue() {
	
	// Case 1: if queue is empty, we have nothing to return
	if (process_queue == NULL) {
		return NULL;
	}
	
	// Case 2: queue is nonempty, return first element and adjust pointers
	else {
		// temporary pointer to keep track of first element
		process_t* temp_p = process_queue;
		process_queue = temp_p->next_p;
		return temp_p;
	}
}

// Creates a process that starts at function f with stack size n
int process_create (void (*f)(void), int n) {
	
	// Creating new process_t struct and allocating memory
	process_t* proc = malloc(sizeof(process_t));
	// Returning -1 if malloc fails
	if (proc == NULL) return -1;
	
	// Allocating memory for the process state on the stack
	unsigned int* sp = process_stack_init(f, n);
	// Returning -1 if stack can't be allocated
	if (sp == NULL) return -1;
	
	// Assigning fields to the struct
	proc->n = n;
	proc->original_sp = sp;
	proc->sp = sp;
	proc->next_p = NULL;
	
	// Enqueueing this process to the process queue
	enqueue(proc);
	
	// If everything else succeeded, return 0
	return 0;
}

// Sets up processes and calls process begin
void process_start (void) {
	
	// Calling helper functions to setup PIT
	pit_setup();
	NVIC_EnableIRQ(PIT0_IRQn);
	
	// Moving the first element from the process queue
	if (process_queue != NULL) {
		current_process = dequeue();
	}
	// If there is nothing in the queue, then current process
	// is NULL
	
	// Initiate first process
	process_begin();
}

// Selects next ready process when PIT0 interrupt handler is called
unsigned int* process_select (unsigned int* cursp) {
	
	// Checking if there is a currently running process
	if (cursp != NULL) {
		// Add current process to the process queue
		enqueue(current_process);
		
		// Check if queue is empty
		if (process_queue != NULL) {
			// Add head of queue to current process
			current_process = dequeue();
			// Return stack pointer for next process
			return current_process->sp;
		}
	}
	
	// If there is no process ready, return NULL
	return NULL;
}
