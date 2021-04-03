extern next_row: near
extrn input: near
extrn to_binary: near
extrn to_hex: near

STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	MENU dw 4 dup(?)
	MENU_MSG db 13, 10, 'Choose one of listed options:'
	db 13, 10, '1 - input number'
	db 13, 10, '2 - change to binary system'
	db 13, 10, '3 - change to hex system'
	db 13, 10, '4 - to quit'
	db 13, 10, 'Your choice: $'
	NUMBER dw 0
	MAX_TEN_LEN db 8
	TEN_LEN db 0
	TEN_NUM db 8 dup(?)
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
main:
	mov ax, DSEG
	mov ds, ax
	
	mov MENU[0], input
	mov MENU[2], to_binary
	mov MENU[4], to_hex
	mov MENU[6], exit
	
	menu_choice:
		mov dx, offset MENU_MSG
		mov ah, 9
		int 21h
		
		mov ah, 1
		int 21h
		
		mov ah, 0
		sub ax, '0'
		dec ax
		mov bx, 2
		mul bx
		mov bx, ax
		
		call next_row
		
		call MENU[bx]
		jmp menu_choice
	
exit proc near
	mov ax, 4c00h
	int 21h
exit endp
CSEG ENDS

public NUMBER
public MAX_TEN_LEN
public TEN_LEN
public TEN_NUM

END main