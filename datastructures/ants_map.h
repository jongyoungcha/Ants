#ifndef _ANTS_MAP_H_
#define _ANTS_MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/md5.h>


#define ants_map_pushd(map, data, len) ants_map_push_with_data(map, data, len)
#define ants_map_pushn(map, node)      ants_map_push_with_node(map, node)

#define ants_map_findd(map, data, len) ants_map_find_with_data(map, data, len)
#define ants_map_findn(map, node)      ants_map_find_with_node(map, node)

typedef struct ants_map_node
{
	unsigned char* key;
	int check_sum;
	void* data;
	int len_data;
	struct ants_map_node* left;
	struct ants_map_node* right;
	
} ants_map_node_t;


typedef struct ants_map
{
	int cnt_nodes;
	ants_map_node_t* root;
	int (*cb_comapre)(void* data1, void* data2);
	
} ants_map_t;


struct st_temp
{
	int num;
	char name[100];
};

typedef struct st_temp st_temp_t;

int ants_map_compare_default(void* data_prev, void* data_next);

ants_map_t* ants_map_new(int (*fcompare)(void* data_prev, void* data_next));
unsigned char* ants_map_get_key(const void* data, const int len_data, int* len_md5);

int ants_map_insert(ants_map_t* map, void* data, const int len);
int ants_map_insert_leftorder(ants_map_node_t* map, ants_map_node_t* node);

int ants_map_search_with_data(ants_map_t* map, const void* data, const int len);
int ants_map_find_with_node(ants_map_t* map, ants_map_node_t* node);

int ants_map_walk(ants_map_t* map, void (*pfunc)(void*));
int ants_map_walk_inner(ants_map_node_t* node, void (*pfunc)(void*));
int ants_map_walk_compare(ants_map_node_t* node_finding, ants_map_node_t* node_crr, int (*pfunc_compare)(void*, void*));


#endif

