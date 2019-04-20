#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

void print_list(VNode *head){
	VNode *cur = head;
	while(cur){
		printf("%s ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

int compare_char(const void* p1, const void* p2){
	return (*(char*)p1 - *(char*)p2);
}

int main (int argc, char ** argv) {

	DNode* result;

	//either static or use calloc - to set all bytes initially to 0
	static DNode* dictionary [DEFAULT_HASH_SIZE];
	//Scan through text file and put words in the dictionary with their sorted
	//as key and the string itself as value
	FILE *fp;
	char key[1000];
	char value[1000];
  char str[1000];
  char* filename = "words.txt";
 	fp = fopen(filename, "r");
  if (fp == NULL){
        printf("File %s not found",filename);
        return 0;
  }
  while (fgets(str, 1000, fp) != NULL){
		if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = 0;
		strcpy(value,str);
		//printf("%s\n", value);
		qsort(str, strlen(str), sizeof(char), compare_char);
		strcpy(key,str);
		//printf("%s\n", key);
		set(dictionary, DEFAULT_HASH_SIZE, key, value);
	}
  fclose(fp);

	//Now loop through dictionary to find anagrams
	int num_anagrams = 0;
	for (int i=0;i<DEFAULT_HASH_SIZE;i++){
		if (dictionary[i]!= NULL){
				result = get(dictionary, DEFAULT_HASH_SIZE, dictionary[i]->key);
				VNode * anagrams = (result->values);
				if (anagrams->next != NULL){
						while (anagrams != NULL){
								printf("%s ",anagrams->value);
								anagrams=anagrams->next;
						}
						printf("\n");
						num_anagrams++;
				}
		}
	}

	printf("There are %d sets of anagrams", num_anagrams);
	/*result = get (dictionary, DEFAULT_HASH_SIZE, "how");
	if (result != NULL) {
		printf("Anagrams for 'how':\n");
		print_list (result->values);
	}
	else{
		printf("notfound\n");
	}*/
	/*
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "repo");
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "rope");
	result = get (dictionary, DEFAULT_HASH_SIZE, "pore");
	if (result != NULL) {
		printf("Anagrams for 'pore':\n");
		print_list (result->values);
	}
	else
		printf ("'pore' not found\n");
	set(dictionary, DEFAULT_HASH_SIZE, "bore", "robe");
	result = get (dictionary, DEFAULT_HASH_SIZE, "bore");
	if (result != NULL) {
		printf("Anagrams for 'bore':\n");
		print_list (result->values);
	}
	else
		printf ("'bore' not found\n");
		*/
	free_dictionary(dictionary, DEFAULT_HASH_SIZE);


	return 0;
}
