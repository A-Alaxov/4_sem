PUBLIC output_X
EXTRN X: byte

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
output_X proc far
	mov ah, 2
	mov dl, X
	int 21h
	ret
output_X endp
CSEG ENDS
END