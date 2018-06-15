#ifndef AUTOMAT_H 
#define AUTOMAT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#define HASH_MUL 31
#define HASH_SIZE 26


void dir (char * dir_name, int substr_size, int al_size, char *substring);

void list_dir (char * dir_name, int substr_size, int al_size, char *substring);

void search(char *string, int substr_size, int al_size, char *substring);

void open_file(char *file, int substr_size, int al_size, char *substring);

//void dir(char * dir_name, int substr_size, int al_size, char *substring);

unsigned int hash(char s);




#endif
