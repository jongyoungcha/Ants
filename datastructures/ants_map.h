#ifndef _ANTS_MAP_H_
#define _ANTS_MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/md5.h>


#define ants_map_pushd(map, data, len) ants_map_push_with_data(map, data, len)
#define ants_map_pushn(map, node)      ants_map_push_with_node(map, node)

#define ants_map_findd(map, data, len) ants_map_find_with_data(map, data, len)
#define ants_map_findn(map, node)      ants_map_find_with_node(map, node)


typedef struct ants_map_node
{
	int key;
	void* data;
	struct ants_map_node* left;
	struct ants_map_ndoe* right;
} ants_map_node_t;


typedef struct ants_map
{
	int cnt_nodes;
	ants_map_node_t* root;
	int (*cb_comapre)(void* data1, void* data2);
} ants_map_t;
	

int ants_map_compare_default(void* data_prev, void* data_next);

ants_map_t* ants_map_new(int (*fcompare)(void* data_prev, void* data_next));
unsigned char* ants_map_get_key(const void* data, const int len);

int ants_map_push_with_data(ants_map_t* map, void* data, int len_data);
int ants_map_push_with_node(ants_map_t* map, ants_map_node_t* node);

int ants_map_find_with_data(ants_map_t* map, void* data, int len_data);
int ants_map_find_with_node(ants_map_t* map, ants_map_node_t* node);


#endif











