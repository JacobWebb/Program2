/*
    PROGRAM #2
*/

// define libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "node.h"   

int main() {
    
    // boolean values
    bool needToExecuteProgram, extendVariable, extendAtBack, extendAtFront, didComplete, checkAlias;
    // counters
    int wordCount, loopCount, tempCount, arrayPosition_x, arrayPosition_y;
    // strings
    char commandInput[100],tempWord[20],userCommand[10][30], temp[50], temp2[50], temp3[50];
    // commands & variables
    char *command, *arg1, *arg2, *arg3, *extending;
    
    // declare list heads
	struct node *varHP;
	struct node *aliasHP;
	// init to null
    varHP = NULL;
    aliasHP = NULL;
    char mem[1000];
    initialize_globals(mem, 1000);
    memset(mem, 0, 1000); //all values need to be initialized to 0.    
    // get command input
    needToExecuteProgram = TRUE;
    while (needToExecuteProgram) 
    {
        // print shell prompt
        wordCount = 0;
        prompt;
        fgets(commandInput, 100, stdin);
        // For @var to display 
        if(commandInput[0] == '@') {
        	int temporary = strlen(commandInput) -2; //to ignore "@" and "\n" in input
        	char temporary2[temporary];
        	int x = 1,y = 0;; //skip the @
        	while(y < temporary) {
        		if(commandInput[x] == '\n') //break at the newline, we don't want that included
        			break;
        		temporary2[y] = commandInput[x];
        		x++; //temporary[2] will hold the variable name.
        		y++;
        	}
        	temporary2[y] = '\0';
        	showVarValue(varHP, temporary2);
        	printf("Josh, at this line the program needs to go back to the beginning of loop.\n"); 
        }
        //end of @var display
        // break up input string from user into an array of strings to interpret
        tempCount = arrayPosition_x = arrayPosition_y = 0;
         
        // loop through each character of the string entered from the command line
        for (loopCount=0; loopCount<strlen(commandInput)-1; loopCount++) 
        {
            // if a space is found 
            if (commandInput[loopCount] == space) 
            {
                // end the temp word
                tempWord[tempCount] = EOS;
                // place it in the command array
                arrayPosition_y = 0;
                wordCount++;
                while (TRUE) 
                {
                    if (tempWord[arrayPosition_y] == EOS)
                    {
                        userCommand[arrayPosition_x][arrayPosition_y] = EOS;
                        break;
                    }
                    userCommand[arrayPosition_x][arrayPosition_y] = tempWord[arrayPosition_y];
                    arrayPosition_y++;
                }
                // move to get the next word
                arrayPosition_x++;
                tempCount = 0;
            }
            // while there are no spaces
            else
            {
                // put the characters in a temporary word until one is found
                tempWord[tempCount] = commandInput[loopCount];
                tempCount++;
                 
                // if there is no space, but its the end of the user's input
                if (loopCount == strlen(commandInput)-2) 
                {
                    tempWord[tempCount] = EOS;
                    arrayPosition_y = 0;
                    wordCount++;
                    while (TRUE) 
                    {
                        if (tempWord[arrayPosition_y] == EOS)
                        {
                            userCommand[arrayPosition_x][arrayPosition_y] = EOS;
                            break;
                        }
                        userCommand[arrayPosition_x][arrayPosition_y] = tempWord[arrayPosition_y];
                        arrayPosition_y++;
                         
                    }       
                }
            }
        }
         
         
        // Implement whatever command was given or print the errors
        // if there was input
        if (wordCount > 0) 
        {
            // get the command
            command = &userCommand[0][0];
             
            // if the command is "set"
            if (strcmp(command,"set") == 0 || (matchAlias(aliasHP, "set", command))==TRUE ) 
            {
                // check for the correct amount of arguments
                if (wordCount-1 <= 2) 
                {
                    // display all variables
                    if (wordCount == 1) 
                    {
                        printVarList(varHP);
                    }
                    // display a variable's specific value
                    else if (wordCount == 2)
                    {
                        arg1 = &userCommand[1][0];
                       	showVarValue(varHP,arg1);
                    }
                    // set OR reset a variable  
                    else
                    {   
                        arg1 = &userCommand[1][0];
                        arg2 = &userCommand[2][0];
                         
                        strcpy(temp3,userCommand[2]);
                    	
                        extendVariable = extendAtFront = extendAtBack = FALSE;
                        // if wanting to extend a variable with the new value on the back
                        if (temp3[0] == '@') 
                        {
                            extendAtBack = TRUE;
                            extendVariable = FALSE;
                            // look for the '!' ending variable character
                            for(loopCount=0; loopCount < strlen(temp3); loopCount++)
                            {
                                if (temp3[loopCount] == '!')
                                {
                                    extendVariable = TRUE;
                                    temp[loopCount-1] = EOS;
                                     
                                    // get the rest of the string to use to extend variable with
                                    loopCount++;
                                    int i = 0;
                                    for (loopCount; loopCount < strlen(temp3); loopCount++)
                                    {
                                        temp2[i] = temp3[loopCount];
                                        i++;
                                        if (loopCount == (strlen(temp3) -1))
                                        {
                                            temp2[i] = EOS;
                                            arg2 = temp;
                                            arg3 = temp2;
                                            break;
                                        }
                                    }                                   
                                }
                                else if (extendVariable == TRUE)
                                    break;
                                else
                                {
                                    if (loopCount != 0)
                                        temp[loopCount-1] = temp3[loopCount];
                                }
                            }
                        }
                        // test to see if user wants to extend the variable on the front of it with the new value
                        if (extendAtBack == FALSE)
                        {
                            extendAtFront = FALSE;
                            for(loopCount=0; loopCount < strlen(temp3); loopCount++)
                            {
                                if (temp3[loopCount] == '@' && temp3[loopCount-1] == '!')
                                {
                                    int tempSpot, j;
                                    j = 0;
                                    tempSpot = loopCount + 1;
                                    for (tempSpot; tempSpot < strlen(temp3); tempSpot++)
                                    {
                                        temp[j] = temp3[tempSpot];
                                        j++;
                                    }
                                    temp[j] = EOS;
                                    for (tempSpot = 0; tempSpot < (loopCount-1); tempSpot++)
                                    {
                                        temp2[tempSpot] = temp3[tempSpot];
                                    }
                                    temp2[tempSpot] = EOS;
                                    extendAtFront = TRUE;
                                    extendVariable = TRUE;
                                    arg2 = temp;
                                    arg3 = temp2;
                                    break;
                                }
                            }       
                        }
                         
                         
                        // Set or reset a variable
                        if (extendVariable == FALSE)
                        {
                        	// if the head is null
                           	if (varHP == NULL){
                           		varHP = (node*)nshMalloc(sizeof(node));
								strcpy(varHP->name,&userCommand[1][0]);
								strcpy(varHP->value, arg2);	
								varHP->next = NULL; 	                      		
                           	}
                           	// if need to find its place in the list
                           	else {
                           		insertVariable(varHP, arg1,arg2, VARIABLE);
                           	}
                        }
                        else if (extendAtFront == TRUE)
                        {
                        	// extendVarValue (node *head, char *set_resetValue, char *getVarValue, char *extendWith, int extendingPosition) 
                        	didComplete = extendVarValue(varHP, arg1, arg2, arg3, varValueInBack);
                        	if (didComplete == FALSE)
                        		printf("Couldn't extend variable, it doesn't exist\n");
                           	
                        }
                        else {
                        	// extendVarValue (node *head, char *set_resetValue, char *getVarValue, char *extendWith, int extendingPosition) 
                        	didComplete = extendVarValue(varHP, arg1, arg2, arg3, varValueInFront);
                        	if (didComplete == FALSE)
                        		printf("Couldn't extend variable, it doesn't exist\n");
                        }
                        
                        // reset bool values
                        extendVariable = extendAtFront = extendAtBack = FALSE;
                    }
                }
                else
                {
                    printf("Error - To many arguments for the \"set\" command\n");
                    continue;
                }
            }
            // if the command is "tes"
            else if (strcmp(command,"tes") == 0 || (matchAlias(aliasHP, "tes", command))==TRUE )
            {
                // if there are not to many OR to few arguments for this command
                if (wordCount-1 == 1)
                {
                    arg1 = &userCommand[1][0];
                    int status;
                    status = clearVar(varHP,arg1);
                    if (status == onlyOneNode){
                    	varHP = NULL;
                    }
                    else if (status == popHead){
                    	varHP = varHP->next;
                    }
                    
                }
                else
                {
                    printf("Error - To many or to few arguments for the \"tes\" command\n");
                }
            }
            // if the command is "alias"
            else if (strcmp(command,"alias") == 0 || (matchAlias(aliasHP, "alias", command))==TRUE )
            {
                // if wordCount is 1 - display all aliases (External & Internal)
                if (wordCount == 1)
                {
                	printVarList(aliasHP);
                }
                // wordCount = 2 - display a specific command alias
                else if (wordCount == 2)
                {
                    arg1 = &userCommand[1][0];
                    showVarValue(aliasHP,arg1);
                    
                }
                // wordCout =3 - set/reset a command alias
                else
                {
                    // if the new alias is an internal command
                    arg1 = &userCommand[1][0];
                    arg2 = &userCommand[2][0];
                    // if the head is null
					if (aliasHP == NULL){
						aliasHP = (node*)nshMalloc(sizeof(node));
						strcpy(aliasHP->name,&userCommand[1][0]);
						strcpy(aliasHP->value, arg2);	
						aliasHP->next = NULL;                      		
					}
					// if need to find its place in the list
					else {
						insertVariable(aliasHP, arg1,arg2, ALIAS);
					}
                }
            }
            // if the command is "saila"
            else if (strcmp(command,"saila") == 0 || (matchAlias(aliasHP, "saila", command))==TRUE )
            {
                if (wordCount == 2) 
                {
                    arg1 = &userCommand[1][0];
                    int status;
                    status = clearVar(aliasHP,arg1);
                    if (status == onlyOneNode){
                    	aliasHP = NULL;
                    }
                    else if (status == popHead){
                    	aliasHP = aliasHP->next;
                    }
                }
                else {
                    printf("To many arguments for 'saila' command\n");
                }
            }
            // if the command is "exit"
            else if (strcmp(command,"exit") == 0 || (matchAlias(aliasHP, "exit", command))==TRUE )
            {
                needToExecuteProgram = FALSE;
                continue;
            }
            // if the command is not supported or found
            else
            {   
                printf("-bash: %s: external command not supported\n",command);
            }           
        }
    }
    return END_PROGRAM;
}
