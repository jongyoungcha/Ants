#include "ants_list.h"

ants_list_t* ants_new_list()
{
  ants_list_t* ret_list = NULL;
  
  ret_list = malloc(sizeof(ants_list_t));
  ret_list->head = NULL;
  ret_list->tail = NULL;
  ret_list->pcomapre = NULL;
  
  return ret_list;
}


int ants_list_add_head(ants_list_t* list, void* data)
{
  int ret = 0;
  ants_node_t* node_alloc = NULL;

  if (!list)
  {
    return -1;
  }

  node_alloc = malloc(sizeof(ants_node_t*));
  node_alloc->data = data;
  node_alloc->next = NULL;
  node_alloc->prev = NULL;

  if (list->head)
  {
    list->head->prev = node_alloc;
    node_alloc->next = list->head;
  }

  list->head = node_alloc;

  return ret;
}

int ants_list_add_tail(ants_list_t* list, void* data)
{
    int ret = 0;

    return ret;
}
