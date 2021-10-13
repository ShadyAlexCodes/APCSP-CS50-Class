// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Malloc code to allocate new space
         node *new_node = malloc(sizeof(node));

        // Check if the node is not alive.
         if(new_node == NULL)
         {
             // Unload and return false
             unload();
             return false;
         }


        // Copies word based on struct
        strcpy(new_node->word, word);

        // Hash the new word
        int h = hash(word);
        if(hashtable[h] == NULL) {
            hashtable[h] = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
        }
    }
    //printf("The dicitionary size is %i\n", size());
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Create an int to store the size
    unsigned int wordCount = 0;
    // Create node pointer
    node *currentNode = NULL;

    for(int i = 0; i < N; i++) {

        currentNode = hashtable[i];

        while(currentNode != NULL) {
            wordCount++;

            currentNode = currentNode->next;
        }
    }
    return wordCount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{


    int bucket = hash(word);
    node *currentNode = NULL;
    currentNode = hashtable[bucket];
    while(currentNode != NULL)
    {

        if(strcasecmp(word, currentNode->word) == 0)
        {
            return true;
        }
        currentNode = currentNode -> next;
    }
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *currentNode = NULL;

    for(int i = 0; i < N; i++) {
        currentNode = hashtable[i];

        while(currentNode != NULL) {
            hashtable[i] = hashtable[i]->next;

            free(currentNode);

            currentNode = hashtable[i];
        }
    }
    // TODO
    return true;
}
