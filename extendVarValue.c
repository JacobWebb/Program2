#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "defines.h"


bool extendVarValue (struct node *head, char *set_resetName, char *getVarValue, char *extendWith, int extendingPosition) 
{
	char finalValue[100], extendTemp[100];

	// create a node to track the place
	struct node *place;
	place = head;
	
	// find the value that is needed to extend with
	while(TRUE){
		if (place == NULL) {
			return FALSE;
		}
		else if (strcmp(place->name,getVarValue) != 0 && place->next == NULL) {
			return FALSE;		 
		}
		else if (strcmp(place->name,getVarValue) == 0) {
			strcpy(finalValue, place->value);
			break;
		}
		else {
			place = place->next;
		}
	}
	
	// create the new variable value
	if (extendingPosition == varValueInFront) {
		strcat(finalValue, extendWith);
	}
	else {//(extendingPosition == varValueInBack)
		strcpy(finalValue, (strcat(extendWith, finalValue)));
	}
	
	// Insert it into the list (insert OR replace)
	extendWith = finalValue;
	insertVariable(head, set_resetName, extendWith, VARIABLE);
	
	return TRUE;
}
