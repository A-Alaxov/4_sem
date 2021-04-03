public input
public next_row
extrn NUMBER: word
extrn MAX_TEN_LEN: byte
extrn TEN_LEN: byte
extrn TEN_NUM: byte

DSEG SEGMENT PARA PUBLIC 'DATA'
	ENTER_MSG db 13, 10, 'Enter number in 10 n/s (from -32768 to +32767): $'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
next_row proc near
	mov dl, 13
	mov ah, 2
	int 21h
	
	mov dl, 10
	mov ah, 2
	int 21h

	ret
next_row endp
str_to_int proc near
	xor cx, cx
	mov cl, TEN_LEN
	dec cx
	mov bx, 1
	mov word ptr [NUMBER], 0
	change:
		mov si, cx
		xor ax, ax
		mov al, TEN_NUM[si]
		sub ax, '0'
		mul bx
		add word ptr [NUMBER], ax
		
		mov ax, bx
		mov bx, 10
		mul bx
		mov bx, ax
		
		loop change
	
	ret
str_to_int endp
input proc near
	mov dx, offset ENTER_MSG
	mov ah, 9
	int 21h
	
	mov dx, offset MAX_TEN_LEN
	mov ah, 10
	int 21h
	
	call str_to_int
	
	call next_row

	ret
input endp
CSEG ENDS
END