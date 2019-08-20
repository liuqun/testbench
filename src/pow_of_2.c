#include "pow_of_2.h"

int is_pow_of_2(unsigned int num)
{
	return num && !(num & num-1);
}
