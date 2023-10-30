#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    printf("%s\n", score1 > score2 ? "Player 1 wins!" : score1 == score2 ? "Tie!" : "Player 2 wins!");
    return 0;
}

int compute_score(string word)
{
    int score = 0;
    size_t ssize = strlen(word);
    int c;
    for (size_t i = 0; i < ssize; i++)
    {
        c = tolower(word[i]);
        if (c < 97 || c > 122)
            continue;
        sum += POINTS[c - 97];
    }
    return score;
}
