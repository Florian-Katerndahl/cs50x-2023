#include <cs50.h>
#include <stdio.h>

int is_valid(long cn);
int is_amex(long cn);
int is_master(long cn);
int is_visa(long cn);

int main(void)
{
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    printf("%zu", sizeof(long));
    if (!is_valid(card_number)) printf("INVALID\n");
    else if (is_amex(card_number)) printf("AMEX\n");
    else if (is_master(card_number)) printf("MASTERCARD\n");
    else if (is_visa(card_number)) printf("VISA\n");
    else printf("INVALID\n");

    return 0;
}

char[256] to_string(long cn)
{
    char num_as_string[256];
    for (int i = 0; cn > 0; i++)
    {
        num_as_string[i] = cn % 10;
        cn /= 10;
    }
    return num_as_string;
}

int is_valid(long cn)
{
    int nb = sizeof(long);
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
