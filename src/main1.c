/*
代码风格要求:
1. 为了与Qt开发环境风格一致, 要求调整eclipse代码对齐方式, 将所有tab展开并替换为4个空格.
2. (待定)
*/
#include "pow_of_2.h"

int main()
{
    unsigned int i;
    for (i = 3; i <= 16; i++) {
        if (is_pow_of_2(i)) {
            printf("%d is power of 2.\n", i);
        }
    }
    printf("exit...\n");
}
