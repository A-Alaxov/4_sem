.686
.MODEL FLAT, C
.STACK
.CODE
copy_str PROC C old_str:dword, new_str:dword, len:dword
	push ebp
	mov ebp, esp

	mov ecx, [len + 4]

	mov eax, [old_str + 4]
	mov edx, [new_str + 4]

	xor ebx, ebx
	copy:
		mov bl, [eax]
		mov [edx], bl
		inc eax
		inc edx

		loop copy

	mov al, 0
	mov [edx], al

	pop ebp
	ret
copy_str ENDP
END
