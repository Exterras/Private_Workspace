#include <stdio.h>

int main(int argc, char** argv) {
	char buf[256];
	int len;
	
	len = sprintf_s(buf, 256, "Hello\n");

	for (int i = 0; i < 5; i++) {
		len += sprintf_s(buf + len, 256, "%d ", i);
	}

	puts(buf);
}