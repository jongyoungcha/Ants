#include <ants_common.h>

void init_ants_node(ants_node_t** node, void* data, const unsigned long len_data)
{
	if (!*node)
	{
		*node = malloc(sizeof(ants_node_t));
		memset(*node, 0x00, sizeof(ants_node_t));
		
		(*node)->len_data = len_data;
		(*node)->data = malloc(len_data);
		memcpy((*node)->data, data, len_data);
		
		(*node)->next = NULL;
		(*node)->prev = NULL;
	}
	else
	{
		// error message
	}
}


void init_ants_elem(ants_elem_t** elem, int idx, void* data, unsigned long len_data)
{
	if (idx < 0)
	{
		// error message2
	}
	
	if (!*elem)
	{
		*elem = malloc(sizeof(ants_elem_t));
		memset(*elem, 0x00, sizeof(ants_elem_t));
		
		(*elem)->len_data = len_data;
		(*elem)->data = malloc(len_data);
		(*elem)->idx = idx;
	}
}


void free_ants_node(ants_node_t** node)
{
	if (*node)
	{
		if ((*node)->data)
		{
			free((*node)->data);
		}

		free(*node);
	}
}


void free_ants_elem(ants_elem_t** elem)
{
	if (*elem)
	{
		if ((*elem)->data)
		{
			free((*elem)->data);
		}

		free(*elem);
	}
}

