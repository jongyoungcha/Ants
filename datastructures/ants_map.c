#include <ants_map.h>


int ants_map_compare_default(void* data_prev, void* data_next)
{
	int checksum1 = 0;
	int checksum2 = 0;

	checksum1 = (int)data_prev;
	checksum2 = (int)data_next;

	printf("comparing : %d with %d", checksum1, checksum2);
	
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


unsigned char* ants_map_get_key(const void* data, const int len_data, int* len_key)
{
	unsigned char *ret_md5 = NULL;
	
	if (!data)
	{
		printf("data was NULL\n");
		return NULL;
	}

	ret_md5 = malloc(MD5_DIGEST_LENGTH);
	if (!MD5(data, len_data, ret_md5))
	{
		printf("Generating key was failed...\n");
	}
	
	*len_key = MD5_DIGEST_LENGTH;

	return ret_md5;
}


ants_map_node_t* ants_map_node_new(void* data, int len)
{
	ants_map_node_t* node_new = NULL;
	int len_md5 = 0;
	int i = 0;

	node_new = malloc(sizeof(ants_map_t));
	memset(node_new, 0x00, sizeof(ants_map_t));
	
	node_new->data = malloc(len);

	memcpy(node_new->data, data, len);
	node_new->len_data = len;
	node_new->key = ants_map_get_key(data, len, &len_md5);
	
	if (!(node_new->key))
	{
		printf("Inserting was failed...");
		free(node_new->key);
		free(node_new);
	}

	if (node_new->key){
		for(i=0; i<len_md5; i++){
			node_new->check_sum += node_new->key[i];
		}
	}
	
	if (node_new->key){
		printf("Inserted node : ");
		for(i=0; i<len_md5; i++){
			/* node_new->check_sum += node_new->key[i]; */
			printf("%02x ", node_new->key[i]);
		}
		printf("\n");
	}
	
	node_new->left = NULL;
	node_new->right = NULL;

	return node_new;
}


int ants_map_node_free(ants_map_node_t** node)
{
	if (*node)
	{
		if ((*node)->data) free((*node)->data);
		free(*node);
	}
	
	return 0;
}


int ants_map_insert(ants_map_t* map, void* data, const int len)
{
	int ret = 0;
	int i = 0;
	ants_map_node_t* node_new = NULL;
	/* ants_map_node_t* node_crr = NULL; */
	
	if (!map)
	{
		fprintf(stderr, "A map structure was NULL...\n");
		return -1;
	}
	
	node_new = ants_map_node_new(data, len);
	if (node_new)
	{
		if(!map->root)
		{
			map->root = node_new;
		}
		else
		{
			// Compare int data and push node.
			ret = ants_map_insert_leftorder(map->root, node_new);
			if (ret == 0)
			{
				fprintf(stdout, "Insert OK!!\n");
			}
			else
			{
				fprintf(stderr, "Insert was failed...\n");
			}
		}
	}
	else
	{
		fprintf(stderr, "Creating node was failed...\n");
	}

	return 0;
}


int ants_map_insert_leftorder(ants_map_node_t* node_crr, ants_map_node_t* node_toinsert)
{
	if (node_crr && node_toinsert)
	{
		if (node_crr->check_sum > node_toinsert->check_sum)
		{
			if (node_crr->left == NULL)
			{
				node_crr->left = node_toinsert;
				return 0;
			}
			else
			{
				return (ants_map_insert_leftorder(node_crr->left, node_toinsert));
			}
		}
		else if (node_crr->check_sum < node_toinsert->check_sum)
		{
			if (node_crr->right == NULL)
			{
				node_crr->right = node_toinsert;
				return 0;
			}
			else
			{
				return (ants_map_insert_leftorder(node_crr->right, node_toinsert));
			}
		}
		else
		{
			fprintf(stdout, "The checksum value was same.\n");
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "A arguments was invalid\n");
	}

	return 0;
}


int ants_map_search_with_data(ants_map_t* map, const void* data, const int len_data)
{
	
	return 0;
}


int ants_map_find_with_node(ants_map_t* map, ants_map_node_t* node)
{
	return 0;
}


int ants_map_walk(ants_map_node_t* node)
{
	if (!node)
	{
		fprintf(stderr, "A map structure was NULL...\n");
		return -1;
	}

	if (node->left)
	{
		ants_map_walk(node->left);
	}

	if (node->right)
	{
		ants_map_walk(node->right);
	}
	
	return 0;
}



