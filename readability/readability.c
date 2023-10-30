#include <stdio.h>

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
        printf("Before grade 1\n");
    else
        printf("Grade %d\n", grade);

    return 0;
}

float coleman_liau(const char * text)
{
    int word_count = 0;
    int sentence_count = 0;
    
    return 0.0588 * ((float) L) - 0.296 * ((float) S) - 15.8;
}
