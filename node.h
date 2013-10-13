#ifndef STRUCT_HEADER
#define STRUCT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node 
{
	char name[50]; 
	char value[50];
	struct node *next;
}node;

#endif
