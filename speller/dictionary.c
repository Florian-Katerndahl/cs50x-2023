// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 8192;

// Hash table
node *table[N];

void force_lower(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
        word[i] = tolower(word[i]);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    force_lower(word);
    node *head = table[hash(word)];
    while (head)
    {
        if (strcasecmp(head->word, word) == 0)
            return true;
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    unsigned int len = strlen(word);
    unsigned int hash = len;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += word[i];
    }
    return (hash ^ len) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "rt");
    if (f == NULL)
        return false;

    char word[LENGTH + 2];
    while (fgets(word, LENGTH + 2, f))
    {
        if (word[0] == '\n')
            break;
        word[strlen(word) - 1] = '\0';

        node *head = table[hash(word)];
        node *new = malloc(sizeof(node));
        strcpy(new->word, word);
        new->next = head;
        head = new;
        table[hash(word)] = head;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        while (head)
        {
            count++;
            head = head->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *lp;
        while (head)
        {
            lp = head->next;
            free(head);
            head = lp;
        }
    }

    return true;
}
