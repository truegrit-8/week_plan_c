#include "stdlib.h"
#include "stdio.h"
#include "swap.h"

int main(int argc, char *argv[])
{
    printf(">> ------------%s------------", __TIME__);

    int a = 100;
    int b = 200;
    printf("\nBefore Swap: a = %d, b = %d", a, b);
    Swap(&a, &b);
    printf("\nAfter  Swap: a = %d, b = %d", a, b);
    // getchar();
    return 0;
}
