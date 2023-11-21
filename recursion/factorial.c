#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

int factorial(int n)
{
    if (n < 1 || n == INT_MAX) {
        printf("ERROR: n must be larger than or equal to 1 and smaller than INT_MAX\n");
        return -1;
    }

    if (n == 1)
        return 1;

    return n * factorial(n - 1);
}


int main(void)
{
    int n = get_int("The factorial of which number should be calculated? ");
    printf("Factorial of %d is %d\n", n, factorial(n));

    return 0;
}
