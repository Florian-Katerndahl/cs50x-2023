#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    /*for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s won over %s with a margin of %d\n",
                candidates[pairs[i].winner],
                candidates[pairs[i].loser],
                preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    }*/
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(candidates[candidate], name) == 0)
        {
            ranks[rank] = candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] == preferences[j][i])
                continue;
            int winner = preferences[i][j] > preferences[j][i] ? i : j;
            int loser = preferences[i][j] < preferences[j][i] ? i : j;
            pairs[pair_count] = (pair){.winner = winner, .loser = loser};
            pair_count++;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] <
                preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner])
            {
                temp = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

int forms_cycle(int original, int next)
{
    int circle = 0;
    if (locked[next][original])
        return 1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[next][i])
        {
            circle += forms_cycle(original, i);
        }
    }
    return circle;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (forms_cycle(pairs[i].winner, pairs[i].loser))
            continue;
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner_idx = 0;
    int min_losses = candidate_count;
    int losses[MAX] = {0};
    for (int j = 0; j < candidate_count; j++)
    {
        int l = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            l += locked[i][j];
            //printf("%d ", locked[i][j]);
        }
        losses[j] = l;
        //printf("Candidate %s has %d losses\n", candidates[j], losses[j]);
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (losses[i] < min_losses)
        {
            min_losses = losses[i];
            winner_idx = i;
        }
    }

    printf("%s\n", candidates[winner_idx]);
    return;
}
