#include "defines.h"
#include "node.h"
#include <string.h>
#include <stdio.h>

//NOTE: Define character array in main() and call initialize globals
//Then memset(array, 0, size)

char *array_start; //self-explanatory names
char *array_end;
int current_memory_in_use;
int size_of_memory;
int current_number_of_nodes;

//we need a function that gives values to globals and initializes pointers to end and start

void initialize_globals(char *start, int size_of_array) { 
	array_start = start; //point to start
	array_end = start+size_of_array; //end position is start + size
	current_memory_in_use = 0; //nothing assigned yet
	size_of_memory = size_of_array;
	current_number_of_nodes = 0;
}



void* nshMalloc(int requested_size) {
	node* new_node; //create node pointer
	new_node = (node*)array_start; //new_node points to mem[0]
	int size = sizeof(node); 
	int check = 0;
	if(requested_size + size > (size_of_memory - current_memory_in_use)) {
		printf("No space left in array for nodes.\n");
		return NULL; 
	}
	//We checked if there is space available. If we're here this is at least one spot left, have to iterate to find it.
	while(array_end > ((char*)new_node + requested_size + size)) {
		printf("iterating\n");
		if((int)new_node->name[0] == 0) {//we initialized the array with all values = 0
			check = 1; //let the next statement know you can insert

			break;
		}
		else {//position was used, iterate to next
			new_node = ((char*)new_node+(sizeof(node))); //iterate by moving through mem[current+sizeofnode]
		}
	}
	//at this point we either did not find a position to insert, or we have a position if check =1
	if(check == 1) {
		current_memory_in_use += size + requested_size;
		printf("Allocated memory at position %p\n", new_node); //COMMENT THIS OUT BEFORE TURNING IN
		current_number_of_nodes++;
		return new_node; //returns the address of the empty space in mem[]
	}

	printf("Memory full or too fragmented.\n");
	return NULL;

}

