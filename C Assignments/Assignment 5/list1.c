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
//how do I compare the numeric values of strings?

void add_inorder(node** head, node* new_node)
{
	//what am i missing? A segmentation fault means there is a pointer that's being left empty
	if(*head == NULL)
	{
	new_node->next == NULL;
	*head = new_node;
	}
	else if(strcmp((*head)->name, new_node->name) > 0)
	{
	 new_node->next = *head;
	 *head = new_node;
	}
	else{
	 node* prev = *head;
	 node* cur = (*head)->next;;
	 
	while(cur && strcmp(cur->name, new_node->name) < 0)
	{
	  prev = cur;
	  cur = cur->next;
	}
	  
	prev->next = new_node;
	new_node->next = cur;
	}
}

node* rem_inorder(node** head, char* key_name)
{
	if((*head == NULL))
	{
	  return *head;
	}
	else if(strcmp((*head)->name, key_name) == 0)
	{
	 node * test1 = *head;
	 *head = (*head)->next;
	 test1->next = NULL;
	 return test1;
	}	
	else{
	  node * test_node = (*head)->next;
	  node* store = *head;
	  while(test_node)
	  {
	    if(strcmp(test_node->name, key_name) == 0)
		{
		store->next = test_node->next;
		test_node->next = NULL;
		return test_node;
		}
		else{
		store = test_node;
		test_node = test_node->next;
		}
	  }
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
int list_len(const node* head)
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
    free_list(&((*head)->next));
    free_node1( *head );
    *head = NULL;
  }
}

void print_list(const node* head) {
    const node* iteration = head;
	while (iteration != NULL) {
        printf("{%d, %s}\n", iteration->id, iteration->name);
        iteration = iteration->next;
    }
}

