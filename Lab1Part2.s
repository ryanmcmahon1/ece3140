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
		BL    LEDSETUP
		MOV   R0, #0
		BL    morse
		BL    pause
		MOV   R0, #1
		BL    morse
		BL    pause
		MOV   R0, #2
		BL    morse
		BL    pause
		MOV   R0, #3
		BL    morse
		BL    pause
		MOV   R0, #4
		BL    morse
		BL    pause
		MOV   R0, #5
		BL    morse
		BL    pause
		MOV   R0, #6
		BL    morse
		BL    pause
		MOV   R0, #7
		BL    morse
		BL    pause
		MOV   R0, #8
		BL    morse
		BL    pause
		MOV   R0, #9
		BL    morse
		B     forever
		
morse
		PUSH  {LR}
	    CMP   R0, #0
		BLEQ   zero
		CMP   R0, #1
		BLEQ  one
		CMP   R0, #2
		BLEQ  two
		CMP   R0, #3
		BLEQ  three
		CMP   R0, #4
		BLEQ  four
		CMP   R0, #5
		BLEQ  five
		CMP   R0, #6
		BLEQ  six
		CMP   R0, #7
		BLEQ  seven
		CMP   R0, #8
		BLEQ  eightt
		CMP   R0, #9
		BLEQ  nine
		POP   {LR}
		BX    LR
		
zero
		PUSH  {LR}
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		POP   {LR}
		BX    LR
		
one
		PUSH  {LR}
		BL    dot
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		POP   {LR}
		BX    LR
		
two
		PUSH  {LR}
		BL    dot
		BL    dot
		BL    dash
		BL    dash
		BL    dash
		POP   {LR}
		BX    LR
		
three
		PUSH  {LR}
		BL    dot
		BL    dot
		BL    dot
		BL    dash
		BL    dash
		POP   {LR}
		BX    LR

four
		PUSH  {LR}
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		BL    dash
		POP   {LR}
		BX    LR
		
five
		PUSH  {LR}
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		POP   {LR}
		BX    LR
		
six
		PUSH  {LR}
		BL    dash
		BL    dot
		BL    dot
		BL    dot
		BL    dot
		POP   {LR}
		BX    LR
		
seven
		PUSH  {LR}
		BL    dash
		BL    dash
		BL    dot
		BL    dot
		BL    dot
		POP   {LR}
		BX    LR
		
eightt
		PUSH  {LR}
		BL    dash
		BL    dash
		BL    dash
		BL    dot
		BL    dot
		POP   {LR}
		BX    LR
		
nine
		PUSH  {LR}
		BL    dash
		BL    dash
		BL    dash
		BL    dash
		BL    dot
		POP   {LR}
		BX    LR
		
dot
		PUSH  {LR, R7}
		BL    LEDON
		MOV   R7, #0x000F0000
		BL    delay
		BL    LEDOFF
		MOV   R7, #0x000F0000
		BL    delay
		POP   {LR, R7}
		BX    LR

dash
		PUSH  {LR, R7}
		BL    LEDON
		MOV   R7, #0x000F0000
		BL    delay
		MOV   R7, #0x000F0000
		BL    delay
		MOV   R7, #0x000F0000
		BL    delay
		BL    LEDOFF
		MOV   R7, #0x000F0000
		BL    delay
		POP   {LR, R7}
		BX    LR
		
pause
		PUSH  {LR, R7}
		MOV   R7, #0x000F0000
		BL    delay
		MOV   R7, #0x000F0000
		BL    delay
		MOV   R7, #0x000F0000
		BL    delay
		POP   {LR, R7}
		BX    LR
		
delay
	; function that allows us to delay lighting the LED
		SUBS   R7, #1
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
 				
