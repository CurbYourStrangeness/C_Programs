#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"


node* create_node(int idn, const char* nm);
void free_node(node* nd);


int main(void)
{
  node* list;
  node* tmpn;

  printf("node size : %lu\n", sizeof(node));
  create_list(&list);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);

  printf("\nAdd Inorder / Remove Inorder ... \n");

  tmpn = create_node(0, "Zatch");
  printf("Adding node : {%d, %s}\n", tmpn->id, tmpn->name);
  add_inorder(&list, tmpn);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("\n");

  tmpn = create_node(40, "Bri");
  printf("Adding node : {%d, %s}\n", tmpn->id, tmpn->name);
  add_inorder(&list, tmpn);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("\n");

  tmpn = create_node(38, "Jonathon");
  printf("Adding node : {%d, %s}\n", tmpn->id, tmpn->name);
  add_inorder(&list, tmpn);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("\n");

  tmpn = create_node(3, "Fizz");
  printf("Adding node : {%d, %s}\n", tmpn->id, tmpn->name);
  add_inorder(&list, tmpn);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("\n");

  tmpn = rem_inorder(&list,"Jonathon");
  printf("Node removed : {%d, %s}\n", tmpn->id, tmpn->name);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("Freeing removed node ...\n");
  free_node(tmpn);

  tmpn = rem_inorder(&list, "Fizz");
  printf("Node removed : {%d, %s}\n", tmpn->id, tmpn->name);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("Freeing removed node ...\n");
  free_node(tmpn);

  tmpn = rem_inorder(&list, "Bri");
  printf("Node removed : {%d, %s}\n", tmpn->id, tmpn->name);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("Freeing removed node ...\n");
  free_node(tmpn);

  tmpn = rem_inorder(&list, "Bill");

  tmpn = rem_inorder(&list, "Zatch");
  printf("Node removed : {%d, %s}\n", tmpn->id, tmpn->name);
  printf("List length now is : %d\n", list_len(list));
  printf("Print List : \n");
  print_list(list);
  printf("Freeing removed node ...\n");
  free_node(tmpn);

  tmpn = rem_inorder(&list, "Zatch");

  return 0;
}


node* create_node(int idn, const char* nm)
{
  node* tmp = (node*)malloc(sizeof(node));
  tmp->id = idn;
  tmp->name = (char*)malloc(sizeof(char)*(strlen(nm)+1));
  strcpy(tmp->name, nm);
  
  return tmp;
}

void free_node(node* nd)
{
  free(nd->name);
  free(nd);
}
