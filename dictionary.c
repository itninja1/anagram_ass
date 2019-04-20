#include <string.h>
#include "dictionary.h"

//forms hash value for string s
//this produces a starting value in the dictionary array
unsigned hash(const char *s) {
	unsigned hashval;
	//TODO - implement polynomial hashing of string s
	hashval = 1;
	for(int i = 0; i < strlen(s); i++){
		hashval = (hashval<<5) - hashval + s[i];
	}
	return hashval ;
}

//Performs search for a key in the hashtable.
//if the entry key is in the dictionary, it is in the list of blocks
//beginning in array entry hash(key).
//if lookup finds entry for s, it returns a pointer to the node with this key
//if not - it returns NULL
DNode * get (DNode ** dictionary, int hash_size, const char *key) {
	DNode * np;
	unsigned int hashval = hash(key);
	for (np = dictionary [hashval % hash_size]; np !=NULL; np = np->next)
		if (strcmp (key, np->key) == 0)
			return np; //found
	return NULL; //not found
}

//insert uses lookup to detemine whether key is already in the dictionary
//if not, a new entry is created
//next it adds the value to the list of values for this node
DNode * set (DNode ** dictionary, int hash_size,  const char * key, const char * value) {
	unsigned int hashval;
	DNode *np = get (dictionary, hash_size, key);

	if (np == NULL) { //this is a new key
		np = (DNode *) malloc (sizeof (*np));
		if (np == NULL)
			return NULL;
		np->key = copystr (key);
		VNode *new_val = (VNode *) malloc (sizeof (VNode));
		new_val->value = copystr (value);
		new_val->next = NULL;

		np->values = new_val;

		hashval = hash (key) % hash_size;
		//now links itself on top of array entry
		np->next = dictionary [hashval];
		dictionary [hashval] = np;
	}
	else { //the key is already in the dictionary, add value to the list of values
		VNode *new_val = (VNode *) malloc (sizeof (VNode));
		new_val->value = copystr (value);
		new_val->next = np->values;
		np->values = new_val;
	}
	return np;
}

void free_value_list(VNode ** head){
	VNode *current = *head;
	while (current != NULL) {
		VNode * temp = current;
		current = current->next;

		if (temp->value !=NULL){
			free (temp->value);
			temp->value = NULL;
		}
		free (temp);
		temp = NULL;
	}
	*head = NULL;
}

void free_dictionary (DNode ** dictionary, int hash_size) {
	int i;
	for (i=0; i<hash_size; i++) { //iterate over hash array
		if (dictionary [i]!=NULL) { //if there is an entry at position i
			DNode *head = dictionary[i]; //find the head of the linked list of DNodes
			DNode *current = head;
			while (current != NULL) {
				DNode * temp = current;
				current = current->next;
                if (temp->key !=NULL){
                    free (temp->key);
					temp->key = NULL;
				}

				free_value_list(&(temp->values));

				free (temp);
				temp = NULL;
			}
			dictionary[i] = NULL;
		}
	}
}

char *copystr(const char *s) { /* make a duplicate of s */
	char *p;
	int len = strlen(s);

	p = (char *) malloc(len+1); /* +1 for �\0� */
	if (p != NULL)
		strncpy(p, s, len);
	p[len] = '\0';

	return p;
}
