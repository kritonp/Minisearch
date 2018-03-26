#ifndef UTILS_H
#define UTILS_H
#define LMAX 255

#include "trie.h"
#include "postingList.h"


int get_input(struct Trie*,int,char **,int,int);
int consecutivity(char **,int );
int parsing(char **, int , struct Trie*,int);
int print_array(char **,int );
int cmd_arguments(int argc,char* argv[]);
int get_numWords(int id,char** array,int);




#endif