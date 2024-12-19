// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int hash_num;
unsigned int hash_check;
int word_count = 0;
char read_dict[LENGTH + 1];

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;
// Use a function to insert,create nodes
void insert(node *, int);
node *create_node(char *);

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Create a hash table to store the contents of dicts
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_check = hash(word);
    node *ch;

    ch = table[hash_check];
    while (ch != NULL)
    {
        if (!(strcasecmp(ch->word, word)))
        {
            return true;
        }
        ch = ch->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Assign index to the word in table
    // Indicate the first alphabet
    unsigned int alpha;
    alpha = (toupper(word[0]) - 'A') * 26;
    // Indiacte the 2nd alphabet
    // Check for the second word first
    if (strlen(word) >= 2)
    {
        alpha = alpha + (toupper(word[1]) - 'A');
    }
    return alpha;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    // Check whether dictionary exist
    if (dict == NULL)
    {
        return false;
    }
    // Read the dictionary line by line
    while (fscanf(dict, "%s", read_dict) != EOF)
    {
        // Use hash function
        // Map the word to the index in the hash table
        hash_num = hash(read_dict);
        // Store words into hash table
        node *NODE = create_node(read_dict);
        if (NODE == NULL)
        {
            return false;
        }
        insert(NODE, hash_num);
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count != 0)
    {
        return word_count;
    }
    return 0;
}

void insert(node *NODE, int pos)
{

    if (NODE == NULL)
    {
        return;
    }
    // Check if hash table has no elements
    if (table[pos] == NULL)
    {
        table[pos] = NODE;
        NODE->next = NULL;
        word_count++;
        return;
    }
    // All other cases
    NODE->next = table[pos];
    table[pos] = NODE;
    word_count++;
    return;
}
node *create_node(char *WORD)
{
    // Keep track of how many NODES are created
    node *member = malloc(sizeof(struct node));
    if (member != NULL)
    {
        strcpy(member->word, WORD);
        member->next = NULL;
        return member;
    }
    return NULL;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *current;
    for (int i = 0; i < N; i++)
    {
        current = table[i];
        node *temp;
        while (current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    return true;
}
