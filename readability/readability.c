#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float coleman_liau(const char * text);

int main(void)
{
    char * text;
    do
    {
        text = get_string("Text: ");
    }
    while (text == NULL);

    int grade = (int) roundf(coleman_liau(text));

    if (grade > 16)
        printf("Grade 16+\n");
    else if (grade < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade %d\n", grade);

    return 0;
}

float coleman_liau(const char * text)
{
    unsigned int letter_count = 0;
    unsigned int word_count = 0;
    unsigned int sentence_count = 0;
    size_t ssize = strlen(text);

    for (size_t i = 0; i < ssize; i++)
    {
        char c = text[i];
        if ((c > 64 && c < 91) || (c > 96 && c < 123))
            letter_count++;
        if (c == ' ')
            word_count++;
        if (c == '.' || c == '?' || c == '!')
            sentence_count++;
    }

    // since counting white spaces dismisses one word, add one
    word_count++;

    return 0.0588 * (((float) letter_count) / ((float) word_count) * 100.0) - 0.296 *  (((float) sentence_count) / ((float) word_count) * 100.0) - 15.8;
}
