#include <iostream>


extern "C"
{
	void copy_str(char *str, char *new_str, int len);
}

int main()
{
	char str[20] = "Hello, World!", new_str[20] = "aaaaaaaaaaaaaaaaa";
	int len = 0;

	std::cout << "Initial string: " << str << "\n";

	__asm {
		xor eax, eax;
		dec eax;

	cycle:
		inc eax;
		cmp[str + eax], '\0';
		jnz cycle;

		mov len, eax;
	}
	std::cout << "Length: " << len << "\n";

	copy_str(str, new_str, len);
	std::cout << "Copied string: " << new_str << "\n";

	return 0;
}
