#include "ants_list.h"

ants_list_t* ants_new_list()
{
    ants_list_t* new_list = NULL;
  
    new_list = malloc(sizeof(ants_list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->pcomapre = NULL;
    new_list->cnt_nodes = 0;

    return new_list;
}


int ants_list_add_head(ants_list_t* list, void* data)
{
    int ret = 0;
    ants_node_t* node_new = NULL;

    if (!list)
    {
	return -1;
    }

    node_new = malloc(sizeof(ants_node_t));
    node_new->data = data;
    node_new->next = NULL;
    node_new->prev = NULL;


    if (list->head)
    {
	list->head->prev= node_new;
	node_new->next = list->head;
	list->head = node_new;
    }
    else
    {
	list->head = node_new;
	list->tail = node_new;
    }

    list->cnt_nodes++;

    return ret;
}


int ants_list_add_tail(ants_list_t* list, void* data)
{
    int ret = 0;
    ants_node_t* node_new = NULL;

    if (!list)
    {
	return -1;
    }

    node_new = malloc(sizeof(ants_node_t));

    node_new->data = data;
    node_new->next = NULL;
    node_new->prev = NULL;

    if (list->tail)
    {
	list->tail->next = node_new;
	node_new->prev = list->tail;
	list->tail = node_new;
    }
    else
    {
	list->tail = node_new;
	list->head = node_new;
    }

    return ret;
}
