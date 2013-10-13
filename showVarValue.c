#include <string.h>
#include <stdio.h>
#include "node.h"
#include "defines.h"
#include <stdlib.h>


void showVarValue(node *head, char *varName){
	// create a node to track the place
	node *place;
	place = head;

	
	
	if (place != NULL) {
		if (strcmp(place->name,varName) == 0) {
			printf("%s=%s\n",place->name,place->value);
			return;
		}
		else {
			while(place != NULL){
				if (strcmp(place->name,varName) == 0) {
					printf("%s=%s\n",place->name, place->value);
					return;
				}
				else {
					place = place->next;
				}
			}
		}
	}
}
