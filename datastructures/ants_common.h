#ifndef _ANTS_COMMON_H_
#define _ANTS_COMMON_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct ants_node
{
	void* data;
	int len_data;
	struct ants_node* next;
	struct ants_node* prev;

} ants_node_t;

typedef struct ants_elem
{
	int idx;
	void* data;
	int len_data;
	
} ants_elem_t;

void init_ants_node(ants_node_t** node, void* data, const unsigned long len_data);
void init_ants_elem(ants_elem_t** elem, int idx, void* data, unsigned long len_data);

void free_ants_node(ants_node_t** node);
void free_ants_elem(ants_elem_t** elem); 

#endif
