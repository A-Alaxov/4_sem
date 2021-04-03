public to_binary
extern next_row: near
extrn NUMBER: word
extrn TEN_NUM: byte

DSEG SEGMENT PARA PUBLIC 'DATA'
	BIN_MSG db 'Number in binary n/s: $'
	BIN_LEN db 0
	BIN_NUM db 16 dup(?)
	db '$'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG
to_binary proc near
	mov ax, word ptr [NUMBER]
	cmp TEN_NUM[0], '-'
	jz twos_com
	
	back:
	mov bx, 2
	mov si, 15
	xor dx, dx
	mov BIN_LEN, 0
	change:
		div bx
		mov BIN_NUM[si], dl
		add BIN_NUM[si], '0'
		inc BIN_LEN
		xor dx, dx
		
		dec si
		cmp ax, 0
		jnz change
	
	call next_row
	
	mov dx, offset BIN_MSG
	mov ah, 9
	int 21h
	
	mov dx, offset BIN_NUM
	add dx, 16
	sub dl, BIN_LEN
	sbb dh, 0
	int 21h
	
	call next_row
	
	ret		
	
	twos_com:
		not ax
		inc ax
		jmp back
to_binary endp
CSEG ENDS
END