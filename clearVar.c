#include <string.h>
#include <stdio.h>
#include "node.h"
#include "defines.h"
#include <stdlib.h>


int clearVar(struct node *head, char *varName){
	// create nodes to track the place
	struct node *place;
	struct node *previous;
	place = head;
	previous = place;
	
	// check if no nodes in the list
	if (head == NULL) {
		return onlyOneNode;
	}
	// if head needs to be deleted its the only node in the list
	else if (strcmp(head->name, varName)==0 && head->next == NULL) {
		return onlyOneNode;
	}
	// if head needs to be deleted and its NOT the only node in the list
	else if (strcmp(head->name, varName)==0){
		return popHead;
	}
	// for all other nodes that would need to be deleted
	else {
		while(place != NULL){
			if (strcmp(place->name,varName) == 0 && place->next == NULL) {
				previous->next = NULL;
				return success;
			}
			else if (strcmp(place->name,varName)==0) {
				previous->next = place->next;
				return success;
			}
			else {
				previous = place;
				place = place->next;
			}
		}
	}
	return success;
}

