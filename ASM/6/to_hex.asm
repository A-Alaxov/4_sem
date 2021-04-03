public to_hex
extern next_row: near
extrn NUMBER: word
extrn TEN_NUM: byte

DSEG SEGMENT PARA PUBLIC 'DATA'
	HEX_MSG db 'Number in hex n/s: $'
	HEX_LEN db 0
	HEX_NUM db 5 dup(?)
	db '$'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG
to_hex proc near
	mov ax, word ptr [NUMBER]
	mov bx, 16
	mov si, 4
	xor dx, dx
	mov HEX_LEN, 0
	change:
		div bx
		mov HEX_NUM[si], dl
		cmp HEX_NUM[si], 9
		jg to_symb
		add HEX_NUM[si], '0'
		
		back:
		inc HEX_LEN
		xor dx, dx
		
		dec si
		cmp ax, 0
		jnz change
	mov al, TEN_NUM[0]
	mov HEX_NUM[si], al
	
	call next_row
	
	mov dx, offset HEX_MSG
	mov ah, 9
	int 21h
	
	mov dx, offset HEX_NUM
	add dx, 4
	sub dl, HEX_LEN
	sbb dh, 0
	int 21h
	
	call next_row
	
	ret
	
	to_symb:
		sub HEX_NUM[si], 10
		add HEX_NUM[si], 'A'
		jmp back
to_hex endp
CSEG ENDS
END