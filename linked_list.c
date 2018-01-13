
/* 
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list
 
 */


// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id, 
        char *firstName, char *familyName)
{
	// Create Person
	PersonalInfo *newPerson, *currentPerson;
	newPerson = (PersonalInfo *)malloc(sizeof(PersonalInfo));

	newPerson->id = id; // == (*newPerson).id = id;
	strcpy(newPerson->firstName, firstName);
	strcpy(newPerson->familyName, familyName);
	
	newPerson->next = *head;
	*head = newPerson;
	
	return newPerson;
}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName)
{
	if (node == NULL) 
		return NULL;
	else {
		// Create Person
		PersonalInfo *newPerson = (PersonalInfo *) malloc(sizeof(PersonalInfo));
		(*newPerson).id = id; // == newPerson -> id = id;
		strcpy(newPerson->firstName, firstName);
		strcpy(newPerson->familyName, familyName);
		newPerson->next = node->next;
		
		// Print Out
		printNode(newPerson);
		
		node->next = newPerson;
		
		return newPerson;
	}		
	return NULL;
}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{
	
	if (*head == NULL) // check if head exists 
		return insertToList(head, id, firstName, familyName);
	else {
		//if((*head)->firstName == NULL)
		//	return NULL;
		PersonalInfo *currentPerson = NULL;		
		currentPerson = *head;
		
		int lastOfList = 0;
		while (lastOfList == 0){
			if (currentPerson->next == NULL) {
				lastOfList = 1;
				return insertAfter(currentPerson, id, firstName, familyName);
			}
			else 
				currentPerson = currentPerson->next; // try p ->= next ???
		}
	}
	return NULL; // should not reach here
}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName)
{
	if (head == NULL)
		return NULL;
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = head;
		
		int personFound = 0;
		while (personFound == 0){
			if(strcmp(currentPerson->firstName, firstName) == 0) { // if person is found by firstName
				personFound = 1;
				return currentPerson;
			}
			else if(currentPerson->next == NULL) // if the person is not found thru the whole list
				return NULL;
			else
				currentPerson = currentPerson->next; // if person is not found yet move to next
		}
	}
	return NULL; // should not reach here
}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.  

NULL - if no node was found or list empty 

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id)
{
	if (head == NULL)
		return NULL;
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = head;
			
		int personFound = 0;
		while (personFound == 0) {
			if(currentPerson->id == id) { // if person is found by id
				personFound = 1;
				return currentPerson;
			}
			else if (currentPerson->next == NULL) // if the person is not found thru the whole list
				return NULL;
			else 					
				currentPerson = currentPerson->next; // if person is not found yet move to next
		}
	}
	return NULL; // should not reach here
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id,
	char *firstName, char *familyName)
{
	if (*head == NULL)
		return 1; // return 1 if list is empty
	else {
		PersonalInfo *currentPerson = *head;
		
		*id = currentPerson->id;		
  		strcpy(firstName, currentPerson->firstName);
     		strcpy(familyName, currentPerson->familyName);

		*head = (*head)->next;
		free(currentPerson);  // delete first node

		return 0; // return 0 if node was deleted
	}
	return 1; // should not reach here
}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted  
1 if node was not deleted or list is empty 

*/


int deleteLast(PersonalInfo **head, unsigned int *id,
                char *firstName, char *familyName)
{
	if (*head == NULL)
		return 1; // return 1 if list is empty
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = *head;

		if(currentPerson->next == NULL) { // if last element of list delete
			*id = currentPerson->id;		
  			strcpy(firstName, currentPerson->firstName);
     			strcpy(familyName, currentPerson->familyName);

			free(currentPerson);
			*head = NULL;
			return 0; // return 0 if node was deleted  
		}
		else {
			while(currentPerson->next->next != NULL) { // while there is more in the list loop thru
				currentPerson = currentPerson->next; 
			}
			PersonalInfo *nextPerson = currentPerson->next;

			*id = nextPerson->id;		
  			strcpy(firstName, nextPerson->firstName);
     			strcpy(familyName, nextPerson->familyName);

			currentPerson->next = NULL;
			nextPerson = NULL;
			free(nextPerson); // delete last element of list 

			return 0; // return 0 if node was deleted  
		}
	}
	return 1; // should not reach here 
}



/************************************************************************/

/*
Purpose: delete the record after the given node 
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted 
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/



int deleteAfter(PersonalInfo *node, unsigned int *id,
                char *firstName, char *familyName)

{
	if (node == NULL || node->next == NULL) 
		return 1; // return 1 if input or next node is NULL
	else {
		PersonalInfo *currentPerson = node;
		PersonalInfo *nextPerson = node->next;

		*id = nextPerson->id;		
  		strcpy(firstName, nextPerson->firstName);
     		strcpy(familyName, nextPerson->familyName);

		node->next = node->next->next;
		free(nextPerson); 
		return 0; // return 0 if node was deleted 
	}

}


/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName,
	char *familyName, unsigned int *id)
{
	if (*head == NULL || (*head)->next == NULL)
		return 1; // return 1 if no such node exists
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = *head;
		
		while (currentPerson->next != NULL) {
			if(strcmp(currentPerson->next->firstName, firstName) == 0) { // if person is found by firstName
				PersonalInfo *tempPerson = currentPerson->next;

				currentPerson->next = currentPerson->next->next;

				*id = currentPerson->id;		
  				strcpy(firstName, currentPerson->firstName);
     				strcpy(familyName, currentPerson->familyName);

				tempPerson = NULL;
				free(tempPerson);
				return 0; // return 0 if node was deleted
			}
			else 		
				currentPerson = currentPerson->next; // if person is not found yet move to next
		}
		if (currentPerson->next == NULL) { // if the person is not found thru the whole list->next
			if(strcmp(currentPerson->firstName, firstName) == 0) {

				*id = currentPerson->id;		
  				strcpy(firstName, currentPerson->firstName);
     				strcpy(familyName, currentPerson->familyName);

				currentPerson = NULL;
				free(currentPerson);
				
				return 0;
			}
 			else
				return 1; // return 1 if node was not deleted
 		}
	}
	return 1; // should not reach here
}
/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head)
{
	if (head == NULL)
		return;
	else {
		PersonalInfo *currentPerson = NULL;
		PersonalInfo *tempPerson = NULL;
		currentPerson = *head;
		
		int lastPerson = 0;
		while (lastPerson == 0) { // while there are nodes remaining
			if (currentPerson->next == NULL) { // if next node is last node
				lastPerson = 1;
				free(currentPerson); // delete node
			}
			else { 
				tempPerson = currentPerson->next;
				free(currentPerson); // delete node
				currentPerson = tempPerson;
			}
		}
	}
	*head = NULL; // list is now nothing
	return;
}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node)
{
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head)
{
	if (head == NULL)
		return;
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = head;
			
		int lastPerson = 0;
		while (lastPerson == 0) {
			printNode(currentPerson); // print node
			
			if(currentPerson->next == NULL) // if last node exit
				lastPerson = 1;
			else 
				currentPerson = currentPerson->next; // move to next node
		}
	}
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return 
the number of nodes in the list

*/


int listSize(PersonalInfo *head)
{
	int numNodes = 0;
	
	if (head == NULL)
		return 0;
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = head;
			
		int lastPerson = 0;
		while (lastPerson == 0) {
			numNodes++;
			
			if(currentPerson->next == NULL) 
				lastPerson = 1;
			else
				currentPerson = currentPerson->next;
		}
	}
	return numNodes;
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return 
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName)
{
	int numNodes = 0;
	
	if (head == NULL || head->firstName == NULL) 
		return 0;
	else {
		PersonalInfo *currentPerson = NULL;
		currentPerson = head;
			
		int lastPerson = 0;
		while (lastPerson == 0) {
			if (strcmp(currentPerson->firstName, firstName) == 0)
				numNodes++;
			if (currentPerson->next == NULL) 
				lastPerson = 1;
			else 
				currentPerson = currentPerson->next;
		}
	}
	return numNodes;
}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name. 
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/


void removeDuplicates(PersonalInfo *head)
{
	if (head == NULL)
		return;
	else {
		PersonalInfo *currentPerson = NULL;
		PersonalInfo *newNextPerson = NULL;
		currentPerson = head;
		if (currentPerson->firstName == NULL) return;
			
		//int personFound = 0;
		while (currentPerson->next != NULL) {
			if (strcmp(currentPerson->firstName, currentPerson->next->firstName) == 0){ // if same first name
				newNextPerson = currentPerson->next->next;
				free(currentPerson->next);
				currentPerson->next = newNextPerson;
			}
			else
				currentPerson = currentPerson->next; // if not the same move along list
		}
	}
}


























