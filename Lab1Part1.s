		AREA Myprog, CODE, READONLY
		ENTRY
		EXPORT __main
			
;don't change these addresses!
PCR22 	  EQU 0x4004A058 ;PORTB_PCR22  address
SCGC5 	  EQU 0x40048038 ;SIM_SCGC5    address
PDDR 	  EQU 0x400FF054 ;GPIOB_PDDR   address
PCOR 	  EQU 0x400FF048 ;GPIOB_PCOR   address
PSOR      EQU 0x400FF044 ;GPIOB_PSOR   address

ten		  EQU 0x00000400 ; 1 << 10
eight     EQU 0x00000100 ; 1 << 8
twentytwo EQU 0x00400000 ; 1 << 22

__main
	; Your code goes here!
		MOV   R0, #7
		BL    LEDSETUP
	    CMP   R0, #0
		BEQ   zero
		CMP   R0, #1
		BEQ   one
		CMP   R0, #2
		BEQ   two
		CMP   R0, #3
		BEQ   three
		CMP   R0, #4
		BEQ   four
		CMP   R0, #5
		BEQ   five
		CMP   R0, #6
		BEQ   six
		CMP   R0, #7
		BEQ   seven
		CMP   R0, #8
		BEQ   eightt
		CMP   R0, #9
		BEQ   nine
		
zero
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		B     forever
		
one
		BL    dot
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		B     forever
		
two
		BL    dot
		BL    dot
		BL    dash
		BL    dash
		BL    dash
		B     forever
		
three
		BL    dot
		BL    dot
		BL    dot
		BL    dash
		BL    dash
		B     forever

four
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		BL    dash
		B     forever
		
five
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		B     forever
		
six
		BL    dash
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		B     forever
		
seven
		BL    dash
		BL    dash
		BL    dot
		BL    dot
		BL    dot
		B     forever
		
eightt
		BL    dash
		BL    dash
		BL    dash
		BL    dot
		BL    dot
		B     forever
		
nine
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		BL    dot
		B     forever
		
dot
		PUSH  {LR}
		BL    LEDON
		MOV   R1, #0x000F0000
		BL    delay
		BL    LEDOFF
		MOV   R1, #0x000F0000
		BL    delay
		POP   {LR}
		BX    LR

dash
		PUSH  {LR}
		BL    LEDON
		MOV   R1, #0x000F0000
		BL    delay
		MOV   R1, #0x000F0000
		BL    delay
		MOV   R1, #0x000F0000
		BL    delay
		BL    LEDOFF
		MOV   R1, #0x000F0000
		BL    delay
		POP   {LR}
		BX    LR
		
delay
	; function that allows us to delay lighting the LED
		SUBS  R1, #1
		NOP
		NOP
		NOP
		NOP
		NOP
		BNE   delay
		BX    LR

; Call this function first to set up the LED
LEDSETUP
				PUSH  {R4, R5} ; To preserve R4 and R5
				LDR   R4, =ten ; Load the value 1 << 10
				LDR		R5, =SCGC5
				STR		R4, [R5]
				
				LDR   R4, =eight
				LDR   R5, =PCR22
				STR   R4, [R5]
				
				LDR   R4, =twentytwo
				LDR   R5, =PDDR
				STR   R4, [R5]
				POP   {R4, R5}
				BX    LR

; The functions below are for you to use freely      
LEDON				
				PUSH  {R4, R5}
				LDR   R4, =twentytwo
				LDR   R5, =PCOR
				STR   R4, [R5]
				POP   {R4, R5}
				BX    LR
LEDOFF				
				PUSH  {R4, R5}
				LDR   R4, =twentytwo
				LDR   R5, =PSOR
				STR   R4, [R5]
				POP   {R4, R5}
				BX    LR
				
forever
			B		forever						; wait here forever	
			END
 				
