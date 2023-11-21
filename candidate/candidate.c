#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

// typdef a anonymous struct
typedef struct
{
    string name;
    int votes;
}
candidate;

candidate get_candidate(void);

int main(void)
{
    candidate c_arr[3];

    for (int i = 0; i < 3; i ++)
    {
        c_arr[i] = get_candidate();
    }

    printf("Candidates entered: \n");
    for (int i = 0; i < 3; i ++)
    {
        printf("%s with %d vote(s)\n", c_arr[i].name, c_arr[i].votes);
    }

    return 0;
}

candidate get_candidate(void)
{
    candidate c = {0};
    do
    {
        c.name = get_string("Enter candidate's name: ");
    }
    while (c.name == NULL);

    do
    {
        c.votes = get_int("Enter candidate's number of votes: ");
    }
    while (c.votes == INT_MAX);

    return c;
}
