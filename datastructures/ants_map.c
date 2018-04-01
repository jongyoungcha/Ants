#include <ants_map.h>

int ants_map_compare_default(void* data_prev, void* data_next)
{
	return 0;
}

ants_map_t* ants_map_new(int (*fcompare)(void* data_prev, void* data_next))
{
	ants_map_t* map_new = NULL;
	map_new = malloc(sizeof(ants_map_t));

	if (fcompare)
	{
		map_new->cb_comapre = fcompare;
	}

	map_new->cnt_nodes=0;
	map_new->root = NULL;

	return map_new;
}


unsigned char* ants_map_get_key(const void* data, const int len)
{
	if (!data)
	{
		printf("data was NULL\n");
		return NULL;
	}
	
	unsigned char *ret_md5 = NULL;
	int i = 0;

	ret_md5 = malloc(MD5_DIGEST_LENGTH);
	MD5(data, len, ret_md5);
	printf("MD5 (%s) =", data);
	for (i=0; i<MD5_DIGEST_LENGTH; i++)
	{
		printf("%02x", ret_md5[i]);
	}
	printf("\n");

	return ret_md5;
}


int ants_map_push_with_data(ants_map_t* map, void* data, int len_data)
{
	ants_map_node_t* node_new = NULL;
	node_new = malloc(sizeof(ants_map_t));
	
	if (!map)
	{
		fprintf(stderr, "A map structure was NULL...\n");
	}


	return 0;
}


int ants_map_push_with_node(ants_map_t* map, ants_map_node_t* node)
{
	return 0;
}

int ants_map_find_with_data(ants_map_t* map, void* data, int len_data)
{
	return 0;
}


int ants_map_find_with_node(ants_map_t* map, ants_map_node_t* node)
{
	return 0;
}



