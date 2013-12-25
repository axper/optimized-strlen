#include <stdint.h> // uint32_t
#include <stdio.h> // printf

// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
		}
	}
}

int main()
{
	int i;
	uint32_t a = 0;
	uint32_t d = 0;
	const uint32_t magic = 0x7EFEFEFF;
	const uint32_t magicRev = magic ^ 0xFFFFFFFF;

	const uint32_t numbers[] = {
		0x00000000, 0x00000001, 0x34003231,
		0x34323331, 0x01010101
	};


	for (i = 0; i != sizeof(numbers) / sizeof(numbers[ 0 ]); i++) {
		a = numbers[ i ];
		d = magic;

		printf("a:            ");
		printBits(sizeof(a), &a);
		printf("\n");

		d = a + d;

		printf("a+magic:      ");
		printBits(sizeof(d), &d);
		printf("\n");

		a = a ^ 0xFFFFFFFF;

		printf("!a:           ");
		printBits(sizeof(a), &a);
		printf("\n");

		a = a ^ d;

		printf("result:       ");
		printBits(sizeof(a), &a);
		printf("\n");

		a = a & magicRev;

		printf("              ");
		printBits(sizeof(a), &a);

		if (a == 0) {
			printf(" (zero)\n");
		} else {
			printf(" (at least one)\n");
		}

		printf("\n");
	}

	return 0;
}
