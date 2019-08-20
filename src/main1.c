#include "pow_of_2.h"

int main()
{
	unsigned int i;
	for (i=3; i<=16; i++) {
		if (is_pow_of_2(i)) {
			printf("%d is power of 2.\n", i);
		}
	}
	printf("exit...\n");
}
