// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO-depending on hash implementation-: Choose number of buckets in hash table
const unsigned int N = 150001;

// need a counter for the size function
int word_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // we need to assign the hashed word to an index (hash_value)
    int hash_value = hash(word);

    // we need a cursor/pointer to travel through the linked list at the hash value (hashed index) being ran
    node *cursor = table[hash_value];

    // we travel the linked list until cursor hits the end of the list (null)
    while (cursor != NULL)
    {
        // we compare the hashed word and return true if the word is found in the dictionary
        // we do this case insensitive way because we lowercase each word in the hash function which is faster than in check
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // we move into the next node of the list
        cursor = cursor->next;
    }
    // else if we reach the end of the linked list withouth finding the hashed word we return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // We need a variable to summ the ASCII values of each character
    int sum = 0;

    // We loop through each char on the word, stopping when '\0' which in C marks the end of a string (word)
    for (int i = 0; word[i] != '\0'; i++)
    {
        // we lowercase each char to make it insensitive to case for the check function later
        // and we add each character ASCII value to a SUM since tolower returns the ASCII value of that letter
        sum += tolower(word[i]);
    }

    // N is the number of buckets in the hash value and with the modulo for example for dog:
    // d is 100 in ASCII
    // o is 111 in ASCII
    // g is 103 in ASCII
    // d+o+g+ = 100+111+103 = 314 -> 314 % N(150001) = 314,
    // dog will end up in bucket 314
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // If load not possible, return false
    if (source == NULL)
    {
        printf("Could not open %s. \n", dictionary);
        return false;
    }

    // Read each word in the file
    // need a variable to act as buffer (where the word to read is stored) to read from
    char word_beingread[LENGTH + 1];

    // Add each word to the hash table
    // As long as fscan is reading words, loop continues, if end of file (no more words) returns EOF (end of file)
    while (fscanf(source, "%s", word_beingread) != EOF)
    {
        // we allocate memory the size of the node for every new node
        node *newNode = malloc(sizeof(node));

        if (newNode == NULL)
        {
            fclose(source);
            return false;
        }

        // we copy the words being read to the nodes created, each node is a word
        strcpy(newNode->word, word_beingread);
        newNode->next = NULL;

        // we add the nodes(words) to the hash table
        int hash_value = hash(word_beingread);

        // We insert the newNode at the beginning of the linked list at the correct index in the hash table
        // we use a hash table where each "bucket" is a pointer to the start of a linked list
        newNode->next = table[hash_value];
        table[hash_value] = newNode;

        // for every word read (every iteration from the loop) we count word+1 for the size function
        word_counter++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate across every bucket in the hash table (N = nº of buckets defined L18)
    for (int i = 0; i < N; i++)
    {
        // we need another cursor for each bucket(node) we will run through (i)
        node *cursor = table[i];

        // while cursor does not point to something null (end of linked list)
        while (cursor != NULL)
        {
            node *temporary = cursor; // save the current node at temporary address
            cursor = cursor-> next;   // move the cursor to the next node
            free(temporary);          // we free the saved node
        }

    }

    // return true if all memory has been freed
    return true;
}
