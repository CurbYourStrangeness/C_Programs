#include <stdlib.h>
#include <stdio.h>
#include "list.h"
// create an empty list - set *node = NULL
void create_list(node** head)
{
*head = NULL;
}

// add a new node to the front of the list, you must externally add something so that
void add_front(node** head, node* new_node)
{
	new_node->next = *head;
	*head = new_node;
}

//add a new node to the end of the list
void add_end(node** head, node* new_node)
{
	if(*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		node * current = *head;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}
// remove / return the node at the head of the list (if there is one)
node* rem_front(node** head)
{
	if(*head)
	{
	node * test1 = *head;
	*head = (*head)->next;
	test1->next = NULL;
	return test1;
	}
	else
	{
	return *head;
	}
}

//remove / return the node at the end of the list (if there is one)
node* rem_end(node** head)
{
	node* current = *head;
	node* previous = NULL;
	if(*head == NULL)
	{
	  return *head;
	}
	else
	{
	  while(current->next != NULL)
	  {
	    previous = current;
	    current = current->next;
	  }
	  node * test2 = current;
	  if(previous != NULL)
	  {
	    previous->next = NULL;
	  }
	  else
	  {
            *head = NULL;
          }
	  return test2;
	}
}

// return the number of nodes in the list
int list_len(node* head)
{
int ct = 0;
const node* tmp = head;
while(tmp != NULL)
{
++ct;
tmp = tmp->next;
}
return ct;
}

void free_node1(node* this_node)
{
  free(this_node->name);
  free(this_node);
}

void free_list(node** head) 
{
  if ( *head )
  {
    free_list( &((*head)->next) );
    free_node1( *head );
    *head = NULL;
  }
}

void print_list(node* head) {
    while (head != NULL) {
        printf("{%d, %s}\n", head->id, head->name);
        head = head->next;
    }
}

