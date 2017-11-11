#ifndef _ANTS_LIST_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct ants_node
{
	void* data;
	struct ants_node* next;
	struct ants_node* prev;
  
} ants_node_t;


typedef struct ants_list
{
	int cnt_nodes;
	ants_node_t* head;
	ants_node_t* tail;
	int (*pcomapre)(void*, void*);
  
} ants_list_t;


ants_list_t* ants_new_list();

int ants_list_add_head(ants_list_t* list, void* data);
int ants_list_add_tail(ants_list_t* list, void* data);

ants_node_t* ants_list_pop_head(ants_list_t* list);
ants_node_t* ants_list_pop_tail(ants_list_t* list);

ants_node_t* ants_list_read_head(ants_list_t* list);
ants_node_t* ants_list_read_tail(ants_list_t* list);

ants_list_t* ants_list_find(void* data);

ants_list_t* ants_list_remove(void* data);  


#endif

