public input
extrn ROW_MSG: byte
extrn COL_MSG: byte
extrn MATR_INP: byte
extrn NEXT_ROW: byte
extrn ROW_SIZE: byte
extrn COL_SIZE: byte
extrn MATR: byte

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
input proc near
	mov dx, offset ROW_MSG
	mov ah, 9
	int 21h
	
	mov ah, 1
	int 21h
	mov ROW_SIZE, al
	sub ROW_SIZE, '0'
	
	mov dx, offset COL_MSG
	mov ah, 9
	int 21h
	
	mov ah, 1
	int 21h
	mov COL_SIZE, al
	sub COL_SIZE, '0'
	
	mov dx, offset MATR_INP
	mov ah, 9
	int 21h
	
	mov cx, 0
	mov cl, ROW_SIZE
	mov bx, 0
	Matr_input:
		mov dh, cl
		mov cl, COL_SIZE
		
		Row_input:
			mov ah, 1
			int 21h
			mov MATR[bx], al
			inc bx
			
			mov ah, 2
			mov dl, ' '
			int 21h
			
			loop Row_input
		mov cl, dh
		
		mov dx, offset NEXT_ROW
		mov ah, 9
		int 21h
		
		loop Matr_input

	ret
input endp
CSEG ENDS
END