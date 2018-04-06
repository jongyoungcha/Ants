#include <ants_map.h>


int ants_map_compare_default(void* data_prev, void* data_next)
{
	ants_map_node_t* node_prev = NULL;
	ants_map_node_t* node_next = NULL;

	if (data_prev && data_next)
	{
		node_prev = data_prev;
		node_next = data_next;

		fprintf(stdout, "comparing : %d, %d...\n", node_prev->check_sum, node_next->check_sum);

		if (node_prev->check_sum  > node_next->check_sum)
		{
			return 1;
		}
		else if (node_prev->check_sum < node_next->check_sum)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		fprintf(stdout, "arguments were invalid...\n");
		return -1;
	}
}


ants_map_t* ants_map_new(int (*fcompare)(void* data_prev, void* data_next))
{
	ants_map_t* map_new = NULL;
	map_new = malloc(sizeof(ants_map_t));

	if (fcompare)
	{
		map_new->cb_compare = fcompare;
	}
	else
	{
		map_new->cb_compare = ants_map_compare_default;
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

	node_new = malloc(sizeof(ants_map_node_t));
	memset(node_new, 0x00, sizeof(ants_map_node_t));
	
	node_new->data = malloc(len);
	memset(node_new->data, 0x00, len);

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
	ants_map_node_t* node_new = NULL;
	/* ants_map_node_t* node_crr = NULL; */
	
	if (!map)
	{
		fprintf(stderr, "A map structure was NULL...\n");
		return -1;
	}
	
	node_new = ants_map_node_new(data, len);

	st_temp_t* temp = data;
	temp = node_new->data;
	printf("=============\n");
	printf("#### : %d\n", temp->num);
	printf("#### : %s\n", temp->name);
		
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


ants_map_node_t* ants_map_get_root(ants_map_t* map)
{
	if (map && map->root) return map->root;
	else                  return NULL;
}


int ants_map_walk(ants_map_t* map, void (*pfunc)(void*))
{
	ants_map_node_t* node_crr = NULL;
	if (map && map->root)
	{
		node_crr = map->root;
		ants_map_walk_inner(node_crr, pfunc);
	}
	else
	{
		fprintf(stderr, "A map structure was NULL...\n");
		return -1;
	}

	return 0;
}


int ants_map_walk_inner(ants_map_node_t* node, void (*pfunc)(void*))
{
	if (node)
	{
		if (node->left)
		{
			ants_map_walk_inner(node->left, pfunc);
		}

		if (node->right)
		{
			ants_map_walk_inner(node->right, pfunc);
		}

		if (pfunc && node->data)
		{
			pfunc(node->data);
		}
	}

	return 0;
}


int ants_map_walk_compare(ants_map_node_t* node_finding, ants_map_node_t* node_crr, int (*pfunc_compare)(void*, void*))
{
	int ret = 0;
	
	if (node_crr)
	{
		if (node_crr->left)
		{
			ret = ants_map_walk_compare(node_finding, node_crr->left, pfunc_compare);
			if (ret == 0) return 0;
		}
		
		if (node_crr->right)
		{
			ret = ants_map_walk_compare(node_finding, node_crr->right, pfunc_compare);
			if (ret == 0) return 0;
		}

		ret = pfunc_compare(node_finding, node_crr);
		if (ret == 0) return 0;
		else return -1;
	}
	else
	{
		return -1;
	}
}


int ants_map_find_with_node(ants_map_t* map, ants_map_node_t* node_finding)
{
	int ret = 0;
	if (map && map->root && node_finding)
	{
		ret = ants_map_walk_compare(node_finding, map->root, map->cb_compare);
		if (ret == 0) return 0;
		else          return -1;
	}
	else
	{
		return -1;
	}
}
