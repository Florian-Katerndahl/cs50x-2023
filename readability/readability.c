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

    float grade = coleman_liau(text);



    return 0;
}

float coleman_liau(const char * text)
{
    return 0.0588 * ((float) L) - 0.296 * ((float) S) - 15.8;
}
