/*
oakpark_hash_str() demo

by: Iman S. H. Suyoto

Copyright (C) 2005 Iman S. H. Suyoto
 
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons
to whom the Software is furnished to do so, subject to the
following conditions:
 
The above copyright notice and this permission notice shall
be included in all copies or substantial portions of the
Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "oakpark.h"

#define HT_NUM_OF_SLOTS 30
#define DELIMITERS " \t\n"

/* a hashtable with separate chaining is to be implemented here.
   node_t is the data type for a node and hashtable_t is the
   data type for the hashtable */

typedef struct node
        { char * key;
          struct node * next;
          }
        node_t;

typedef struct hashtable
        { node_t ** heads;
          size_t num_of_slots;
          unsigned long seed;
          }
        hashtable_t;

/* setup a hashtable of size num_of_slots */
int hashtable_create(hashtable_t * pht, size_t num_of_slots)
{ size_t s;
  node_t ** h;

  assert(num_of_slots > 0);
  assert(pht != NULL);
  /* allocate memory for the head of each slot */
  pht->heads = malloc(num_of_slots * sizeof pht->heads); 
  if(!pht->heads)
  { pht->num_of_slots = 0;
    return 0;
    }
  /* set all heads to NULL */
  h = pht->heads;
  for(s = 0; s < num_of_slots; ++s)
  { *h++ = NULL;
    }
  pht->num_of_slots = num_of_slots;
  /* set the seed to be used by oakpark_hash_str() */
  pht->seed = (unsigned long)time(NULL);
  return 1;
  }

/* destroy a node */
void node_destroy(node_t * node)
{ assert(node != NULL); 
  free(node->key);
  free(node);
  }

/* destroy the linked list in a slot */
void hashtable_clear_slot(node_t * slot)
{ node_t * next = NULL;
  node_t * curr = slot;

  while(curr)
  { next = curr->next;
    node_destroy(curr);
    curr = next;
    }
  }

/* clean up a hashtable */
void hashtable_destroy(hashtable_t * pht)
{ size_t s;
  size_t num_of_slots;
  node_t ** curr;

  assert(pht != NULL);
  num_of_slots = pht->num_of_slots;
  curr = pht->heads;
  for(s = 0; s < num_of_slots; ++s)
  { hashtable_clear_slot(*curr++);
    }
  free(pht->heads);
  }

/* insert a node into the hashtable */
void hashtable_insert_node(hashtable_t * pht, node_t * node)
{ size_t u_bound;
  size_t hash_val;
  node_t * curr;
  node_t * prev = NULL;

  assert(pht != NULL);
  /* calculate hash value */
  u_bound = pht->num_of_slots - 1;
  hash_val = oakpark_hash_str(node->key, u_bound, pht->seed);
  /* try to put the node as the head of the slot */
  curr = pht->heads[hash_val];
  /* but if there's already a node there, the inserted node
     is an overflow and put at the end of the list */
  while(curr)
  { prev = curr; 
    curr = curr->next;
    }
  /* if there's already a node */
  if(prev)
  /* set it's next pointer to the inserted node */
  { prev->next = node; 
    }
  else
  /* otherwise, the inserted node becomes the head */
  { pht->heads[hash_val] = node;
    }
  }

/* create a node */
node_t * node_create(char * key)
{ node_t * new_node;

  assert(key != NULL);
  new_node = malloc(sizeof *new_node);
  if(new_node)
  { size_t key_len = strlen(key);

    new_node->key = malloc(key_len + 1);
    if(new_node->key)
    { strcpy(new_node->key, key);
      }
    else
    { free(new_node);
      new_node = NULL;
      }
    new_node->next = NULL;
    }
  return new_node;
  }

/* display hashtable */
void hashtable_display(hashtable_t * pht)
{ size_t num_of_slots;
  size_t s;
  node_t * curr;

  assert(pht != NULL);
  num_of_slots = pht->num_of_slots;
  /* iterate through the whole hashtable */
  for(s = 0; s < num_of_slots; ++s)
  { curr = pht->heads[s];
    printf("%lu: ", (unsigned long)s);
    while(curr)
    { printf("\"%s\"", curr->key);
      curr = curr->next;
      if(curr)
      { printf(" --> ");
        }
      }
    printf("\n");
    }
  }

/* main function */
int main(void)
{ hashtable_t ht;
  int status = EXIT_SUCCESS;

  /* create an empty hashtable */
  if(hashtable_create(&ht, HT_NUM_OF_SLOTS))
  { char * line;

    /* grab lines one-by-one from stdin */
    while((line = oakpark_get_line(stdin, NULL)) != NULL)
    { char * key;

      key = strtok(line, DELIMITERS);
      while(key)
      { node_t * node = node_create(key);

        if(node)
        { hashtable_insert_node(&ht, node);
          }
        else
        { free(line);
          goto BAIL_OUT;
          }
        key = strtok(NULL, DELIMITERS);
        }
      free(line);
      }
    hashtable_display(&ht);
BAIL_OUT:
    hashtable_destroy(&ht);
    }
  else
  { fprintf(stderr, "Can't create hashtable.\n");
    status = EXIT_FAILURE;
    }
  return status; 
  }
