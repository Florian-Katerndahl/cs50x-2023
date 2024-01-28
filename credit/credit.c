#include <cs50.h>
#include <stdio.h>

int to_digits(long cn, int dest[256]);
int is_valid(int src[256], int digits);
int is_amex(int src[256], int digits);
int is_master(int src[256], int digits);
int is_visa(int src[256], int digits);

int main(void)
{
    int card_arr[256] = {0};
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    int nDigits = to_digits(card_number, card_arr);

    if (!is_valid(card_arr, nDigits))
        printf("INVALID\n");
    else if (is_amex(card_arr, nDigits))
        printf("AMEX\n");
    else if (is_master(card_arr, nDigits))
        printf("MASTERCARD\n");
    else if (is_visa(card_arr, nDigits))
        printf("VISA\n");
    else
        printf("INVALID\n");

    return 0;
}

int to_digits(long cn, int dest[256])
{
    int i = 0;
    while (cn > 0)
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
        int tmp = src[i] * (1 + (i % 2));
        // tmp % 10 -> 0-9
        // ((tmp / 10) % 10) -> 10s digit, if applicable
        chksm += tmp % 10 + ((tmp / 10) % 10);
    }
    return !(chksm % 10);
}

int is_amex(int src[256], int digits)
{
    return digits == 15 && src[digits - 1] == 3 && (src[digits - 2] == 5 || src[digits - 2] == 7);
}

int is_master(int src[256], int digits)
{
    return digits == 16 && src[digits - 1] == 5 && src[digits - 2] > 0 && src[digits - 2] < 6;
}

int is_visa(int src[256], int digits)
{
    return (digits == 13 || digits == 16) && src[digits - 1] == 4;
}
