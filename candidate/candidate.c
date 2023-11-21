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
    candidate candidate = get_candidate();

    printf("Candidate entered: \n");
    printf("Name: %s with %d votes\n", candidate.name, candidate.votes);

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
