/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* current = &root;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (current->children[hashFunc(word[i])] != NULL)
        {
            current = current->children[hashFunc(word[i])];
        }
    }
    if (current->is_word == true) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary for read
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }
    
    // a current letter
    char letter;
    
    
    while (fread(&letter, sizeof(char), 1, fp))
    {
        for (int i = 0; i < LENGTH; i++)
        {
            // go to the beginning of a word
            node* current = &root;
            
            int ind = hashFunc(letter);
            
            // last letter was final of the word
            if (letter == '\n')
            {
                current->is_word = true;
                words++;
                continue;
            }
            // letter is not final of the word
            else
            {
                // next the letter does not exist
                if (current->children[ind] != NULL)
                {
                    // create place for new letter
                    node* newNode = malloc(sizeof(node));
                    if (newNode == NULL)
                    {
                        return false;
                    }
                    current->children[ind] = newNode;
                    current = newNode;
                }    
                else
                {
                    current = current->children[ind];
                }
            }
        }
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    
    deleteBranch(&root);
    return true;
}

void deleteBranch(node* _current)
{
    for (int i = 0; i < 27; i++)
    {
        node* current = _current;
        if (current->children[i] != NULL)
        {
            current = current->children[i];
            deleteBranch(current);
        }
        else if(i == 27) 
        {
            free(current->children);
        }
    }
    
    
}

int hashFunc(char a)
{
    if (isalpha(a))
    {
        return ((int)toupper(a) - 65) % LENGTH;
    }
    else
    {
        return 26;
    }
}
