#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

node* create_node(int idn, const char* nm)
{
  node* tmp = (node*)malloc(sizeof(node));
  tmp->id = idn;
  tmp->name = (char*)malloc(sizeof(char)*(strlen(nm)+1));
  strcpy(tmp->name, nm);

  return tmp;
}


int main()
{
	int n;
	node * head;
	node* tmpn1 = create_node(0, "Sally");
	node* tmpn2 = create_node(1, "Ryze");
	printf("\n\n");
	
	create_list(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	
	
	//Add front, remove front
	printf("Add front, remove front\n");
	add_front(&head, tmpn1);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	add_front(&head, tmpn2);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_front(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	rem_front(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	free_list(&head);
	printf("\n\n");
	
	create_list(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	
	//Add End, Remove front
	printf("Add end, remove front\n");
	add_end(&head, tmpn1);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	add_end(&head, tmpn2);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_front(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_front(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	free_list(&head);
	
	printf("\n\n");
	
	//Add Front, Remove End
	printf("Add front, remove end\n");
	add_front(&head, tmpn1);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	add_front(&head, tmpn2);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_end(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_end(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	free_list(&head);
	printf("\n\n");
	
	
	//Add End, Remove End
	printf("Add end, remove end\n");
	add_end(&head, tmpn1);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	add_end(&head, tmpn2);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_end(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	
	rem_end(&head);
	n = list_len(head);
	printf("list length is %d\n", n);
	print_list(head);
	
	free_list(&head);
	printf("\n\n");
	
	
	return 0;
}
