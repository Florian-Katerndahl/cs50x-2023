#include <cs50.h>
#include <stdio.h>

int to_digits(long cn, int dest[256]);
int is_valid(int src[256], int digits);
int is_amex(long cn);
int is_master(long cn);
int is_visa(long cn);

int main(void)
{
    int card_arr[256] = { 0 };
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    int nDigits = to_digits(card_number, card_arr);

    if (!is_valid(card_arr, nDigits)) printf("INVALID\n");
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

int is_valid(int src[256], int digits)
{
    int chksm = 0;
    for (int i = 0; i < digits; i++)
    {
        int tmp = src[i] * ( 1 + (i % 2));
        chksm += tmp % 10 + (tmp / 10) % 10;
    }
    return !chksm % 10;
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
