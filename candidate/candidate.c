#include <cs50.h>
#include <stdio.h>

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

    return 0;
}

candidate get_candidate(void)
{
    candidate c;
    

}
