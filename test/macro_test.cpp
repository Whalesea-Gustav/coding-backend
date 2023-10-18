#include <stdio.h>
#define F_MACRO(x) (x << 2)
inline int F_INLINE(int x)
{
    return x << 2;
}

int main(int argc, char* argv[]) {
    int number = 33;
    number = F_MACRO(number += 10);
    //number = (number += 10 << 2);
    printf("%d\n", number);

    number = 33;
    number = F_INLINE(number += 10);

    printf("%d\n", number);
    return 0;
}