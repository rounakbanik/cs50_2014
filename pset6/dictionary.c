/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#define SIZE 131072

/**
 * Returns true if word is in dictionary else false.
 */
 
 //Define the structure of the linked list
 typedef struct node 
 {
    char word[LENGTH + 1];
    struct node* next;
 }
 node; 
 
 //Define the structure of hashtable
 node* hashtable[SIZE];
 
 //Number of words in dictionary
 int numwords =0;
 
 //This program utilizes the djb2 hash function
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)!=0)
       hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%SIZE;
}

 
bool check(const char* word)
{
    // TODO
    //Converting to lower case
    char* temp= malloc(strlen(word)+1);  
    
    for(int i=0; word[i]!='\0'; i++)
      temp[i] = tolower(word[i]);
  
          
    unsigned long index = hash(temp);
    node* cursor = hashtable[index];
    
    while(cursor!= NULL)
    {      
      
      if(strcmp(temp, cursor->word)==0)
      {
        return true;
      }
      cursor = cursor->next;
    }
    
    return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO    
    
    //Open the dictionary file
    FILE* dict= fopen(dictionary, "r");
    if( dictionary == NULL)
    {
       printf("Loading failed.");
       return false;
    } 
    
    
    
    while(!feof(dict))
    {
       node* new_node = malloc(sizeof(node));
       if(new_node == NULL)
       {
         return 1;
       }
          
       if(fscanf(dict, "%s", new_node->word) != 1)
       {
         free(new_node);       
         break;
       }  
       
       
       //Calculate the hash value of the word
       unsigned long hashval = hash(new_node->word);
       
       //Insert the word into the hash table
       numwords++;
       new_node->next = hashtable[hashval];
       hashtable[hashval] = new_node;
              
    }
    
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return numwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i=0; i<SIZE; i++)
    {
      node* cursor = hashtable[i];
      
      while(cursor != NULL)
      {
         node* temp = cursor;
         cursor = cursor->next;
         free(temp);
      }
    }

    return true;
}


