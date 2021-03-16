extrn input: near
extrn output: far

STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	ROW_MSG db 13, 10, 'Enter number of rows: $'
	COL_MSG db 13, 10, 'Enter number of columns: $'
	MATR_INP db 13, 10, 'Enter matrix:'
	NEXT_ROW db 13, 10, '$'
	MATR_REZ db 13, 10, 'Result matrix:', 13, 10, '$'
	ROW_SIZE db 0
	COL_SIZE db 0
	MATR db 9 * 9 dup (0)
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
change:
	mov cl, ROW_SIZE
	mov ax, cx
	mov cl, 2
	div cl
	mov cl, al
	
	inc cx
	loop Matr_change
	loop Failed_check
	
	Matr_change:
		mov dh, cl
		mov cl, COL_SIZE
		
		Row_change:
			mov dl, cl
			
			mov bx, 0
			mov bl, dh
			dec bl
			
			mov ax, bx
			mul COL_SIZE
			mov bl, al
			
			add bl, dl
			dec bl
			
			mov cx, 0
			mov cl, ROW_SIZE
			sub cl, dh
			
			mov ax, cx
			mul COL_SIZE
			mov cl, al
			
			add cl, dl
			dec cl
			
			mov al, MATR[bx]
			xchg bx, cx
			mov ah, MATR[bx]
			mov MATR[bx], al
			xchg bx, cx
			mov MATR[bx], ah
			
			mov cl, dl
			loop Row_change
		mov cl, dh
		loop Matr_change
	
	Failed_check:
	
	ret
main:
	mov ax, DSEG
	mov ds, ax
	
	call input
	
	call change

	call output

	mov ax, 4c00h
	int 21h
CSEG ENDS

public ROW_MSG
public COL_MSG
public MATR_INP
public NEXT_ROW
public MATR_REZ
public ROW_SIZE
public COL_SIZE
public MATR

END main