EXTRN output_X: far

STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	X LABEL BYTE
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
main:
	mov ax, DSEG
	mov ds, ax
	
	mov ah, 8
	int 21h
	mov X, al

	call output_X	

	mov ax, 4c00h
	int 21h
CSEG ENDS

PUBLIC X

END main