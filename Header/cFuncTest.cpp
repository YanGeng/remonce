#include "cFunc.h"
#include <iostream>

void vaTest(const char *str, ...) {
	va_list args;
	va_start(args, str);
	std::string printed = cfunc::va_list2String(str, args);
	va_end(args);
	std::cout << printed << std::endl;
}

int main(void) {
	char str[32] = "Hello, %d, world!%s! $$%f end";
	vaTest(str, 5, "Add %s test", 1.25);

	char str2[32] = "Hello world!";
	vaTest(str2);
}
