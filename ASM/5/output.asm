public output
extrn MATR_REZ: byte
extrn NEXT_ROW: byte
extrn ROW_SIZE: byte
extrn COL_SIZE: byte
extrn MATR: byte

CS1 SEGMENT PARA PUBLIC 'CODE'
	assume CS:CS1
output proc far
	mov dx, offset MATR_REZ
	mov ah, 9
	int 21h
		
	mov cl, ROW_SIZE
	mov bx, 0
	Matr_output:
		mov dh, cl
		mov cl, COL_SIZE
		
		Row_output:
			mov ah, 2
			mov dl, MATR[bx]
			int 21h
			inc bx
			
			mov ah, 2
			mov dl, ' '
			int 21h
			
			loop Row_output
		mov cl, dh
		
		mov dx, offset NEXT_ROW
		mov ah, 9
		int 21h
		
		loop Matr_output

	ret
output endp
CS1 ENDS
END