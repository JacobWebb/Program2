#include <string.h>
#include <stdio.h>
#include "node.h"
#include "defines.h"
#include <stdlib.h>


bool matchAlias(struct node *head, char *command, char *varName){
	// create a node to track the place
	struct node *place;
	place = head;
	
	if (place != NULL) {
		if (strcmp(place->name,command) == 0 && strcmp(place->value,varName)==0) {
			return TRUE;
		}
		else {
			while(place != NULL){
				if (strcmp(place->name,command) == 0 && strcmp(place->value,varName)==0) {
					return TRUE;
				}
				else {
					place = place->next;
				}
			}
		}
	}
	return FALSE;
}
