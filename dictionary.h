#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#define DEFAULT_HASH_SIZE 500000 //Increasing my HASH SIZE increased the maximum Anagram but 15 was max

typedef struct v_node {
	char* value;
    struct v_node *next;
}VNode;

// Struct to store dictionary nodes
// For each string key there is a list of strings as a value
typedef struct d_node {
	char* key;
	struct v_node *values;
    struct d_node *next;
}DNode;

char * copystr (const char *);
unsigned hash(const char *s);

//Returns a specific entry for a given key
DNode * get (DNode ** dictionary, int hash_size, const char *key);

// Adds a new key-value pair to the dictionary
// If the entry for the key already exists - adds the new value to the list of values
DNode * set (DNode ** dictionary, int hash_size, const char * key, const char * value);

void free_dictionary (DNode ** dictionary, int hash_size);

#endif
