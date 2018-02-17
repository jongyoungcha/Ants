#ifndef _ANTS_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct ants_node
{
	void* data;
	int len_data;
	struct ants_node* next;
	struct ants_node* prev;
  
} ants_node_t;


typedef struct ants_list
{
	int cnt_nodes;
	ants_node_t* head;
	ants_node_t* tail;
	int (*fpcompare)(void*, void*);
  
} ants_list_t;

int ants_list_comapre_default(void* data_prev, void* data_next);
ants_list_t* ants_list_new(int (*fpcompare)(void* data_prev, void* data_next));

int ants_list_add_head(ants_list_t* list, void* data, int len_data);
int ants_list_add_tail(ants_list_t* list, void* data, int len_data);

ants_node_t* ants_list_pop_head(ants_list_t* list);
ants_node_t* ants_list_pop_tail(ants_list_t* list);

ants_node_t* ants_list_read_head(ants_list_t* list);
ants_node_t* ants_list_read_tail(ants_list_t* list);

int ants_list_find(ants_list_t* list, void* data, int len_data);

ants_list_t* ants_list_remove(void* data);  


#endif

