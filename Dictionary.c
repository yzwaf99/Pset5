// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


int counter = 0 ;

// Number of buckets in hash table
const int HASHTABLE_SIZE = 7000;
//create a Hash table
node *table[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    
    int x = hash(word);
    // check if the word exists in the hash table or not
    for (node *tmp =  table[x] ; tmp != NULL; tmp = tmp->next)
    {
        // compare two words regardless of it's uppecase or lowecase
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // initialize index to 0
    int index = 0;

    // sum ascii values
    for (int i = 0; word[i] != '\0'; i++)
    {
        // converting to lower cases words   
        index += tolower(word[i]);
    }

    // mod by size to stay w/in bound of table
    return index % HASHTABLE_SIZE;

}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    
    char oneword[LENGTH + 1];
    
    // open the ditionary and reat it 
    FILE *dict = fopen(dictionary, "r");
   
    // if we couldn't read it or it's NULL return flase and exist the function  
    if (dict == NULL)
    {
        return false;
    }    
    
    // iterate through dictionary words
    while (true)
    {
        fscanf(dict, "%s", oneword);
        if (feof(dict))
        {
            break;
        }
        // create a node for every string is read from dictionary 
        node *h = malloc(sizeof(node));
            
        if (h == NULL)
        {
            return false;
        }

        else 
        {
            // copy word into node
            strcpy(h->word, oneword);
            // set next pointer to NULL
            h->next = NULL;
            int x = hash(h->word);
            
            // insert into list 
            h->next = table[x];
            table[x] = h;
               
            // increment the counter
            counter++;
        }

    }
    // close dictionary
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // the function should return the counter which has been incremented in load function
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate through hashtable
    for (int i = 0; i <= HASHTABLE_SIZE; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];
        // traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);
    }
    return true;
}

