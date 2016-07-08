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
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        node* current = &root;
        if (current->children[hashFunc(word[i])] != NULL)
        {
            current = current->children[hashFunc(word[i])];
        }
        else if (current->is_word == true && i == n - 1)
        {
            return true;
        }
        else return false;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    for (int j = 0, n = strlen(dictionary); j < n; )
    {
        for (int i = j; i < LENGTH; i++)
        {
            node* current = &root;
            char c = dictionary[i];
            int ind = hashFunc(c);
            if (isalpha(c) || (c == '\'' && i > 0))
            {
                if (current->children[ind] == NULL)
                {
                    node* newNode = malloc(sizeof(node));
                    current->children[ind] = newNode;
                    current = newNode;
                    j++;
                    if(dictionary[i + 1] == '\n') 
                    {
                        newNode->is_word = true;
                        words++;
                        j++;
                        break;
                    }
                }
                else
                {
                    current = current->children[ind];
                    j++;
                    if(dictionary[i + 1] == '\n') 
                    {
                        current->is_word = true;
                        words++;
                        j++;
                        break;
                    }
                }
            }
            else 
            {
                printf("WRONG");
            }
        }
        
    }
    return false;
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
