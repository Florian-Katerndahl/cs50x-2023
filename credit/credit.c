#include <cs50.h>
#include <stdio.h>

void to_digits(long cn, char dest[]);
int is_valid(long cn);
int is_amex(long cn);
int is_master(long cn);
int is_visa(long cn);

int main(void)
{
    int nDigits[256] = { 0 };
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    to_digits(card_number, nDigits);
    printf("%s\n", num_as_string);

    if (!is_valid(card_number)) printf("INVALID\n");
    else if (is_amex(card_number)) printf("AMEX\n");
    else if (is_master(card_number)) printf("MASTERCARD\n");
    else if (is_visa(card_number)) printf("VISA\n");
    else printf("INVALID\n");

    return 0;
}

int to_digits(long cn, int dest[256])
{
    int i = 0;
    while (i > 0)
    {
        dest[i] = cn % 10;
        cn /= 10;
        i++;
    }
    return i;
}

int is_valid(int src, int digits)
{
    int chksm = 0;
    for (int i = 0; i < digits; i++)
    {
        chksm += src[i] * 2 * (i % 2);
    }
    return 1;
}

int is_amex(long cn)
{
    return 1;
}

int is_master(long cn)
{
    return 1;
}

int is_visa(long cn)
{
    return 1;
}
