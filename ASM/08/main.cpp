#include <iostream>


extern "C"
{
	void copy_str(char *old_str, char *new_str, int len);
}

int main()
{
	char old_str[25] = "Hello, World!", new_str[25] = "aaaaaaaaaaaaaaaaa", *copy;
	int len = 0, size;

	std::cout << "Initial string: " << old_str << "\n";
	size = sizeof(copy);

	copy = old_str;
	__asm {
		mov edi, copy;
		mov ecx, 0FFFFFFFFh;
		mov al, 0;
		cld;

		repne scasb;
		not ecx;
		dec ecx;

		mov len, ecx;
	}
	std::cout << "Length: " << len << "\n";

	copy_str(old_str, new_str, len);
	std::cout << "Copied string: " << new_str << "\n";

	copy = old_str;
	copy_str(old_str, copy, len);
	std::cout << "Copied string (with equal pointers): " << copy << "\n";

	copy = old_str + 5;
	copy_str(old_str, copy, len);
	std::cout << "Copied string (with overlap): " << copy << "\n";

	return 0;
}
