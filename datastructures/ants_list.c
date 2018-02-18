#include "ants_list.h"

int ants_str2hex(char* str, char* str_hex, int limit_str_hex, char* delimit)
{
    int ret = 0;
    int len_hex = 0;
    
    unsigned char* offs_str = NULL;

    if (str == NULL || str_hex == NULL || limit_str_hex <= 0)
    {
		/* fprintf(stderr, "checking error\n"); */
		return  -1;
    }

	memset(str_hex, 0x00, limit_str_hex);

    for (offs_str = (unsigned char*)str;
		 *offs_str != '\0';
		 offs_str++)
    {
		if (++len_hex > limit_str_hex)
		{
			/* fprintf(stderr, "Length of hex was longer than limit.\n"); */
			return -1;
		}
	
		sprintf(str_hex + strlen(str_hex), "%02x", *offs_str);
	
		if (delimit)
		{
			if (( len_hex += strlen(delimit )) > limit_str_hex)
			{
				return -1;
			}
	    
			sprintf(str_hex + strlen(str_hex), "%s", delimit);
		}
    }

    return ret;
}


int ants_list_compare_default(void* data_prev, void* data_next)
{
	ants_node_t* ants_node_prev = data_prev;
	ants_node_t* ants_node_next = data_next;

	if (ants_node_prev->len_data == ants_node_next->len_data)
	{
		if (memcmp(ants_node_prev->data, ants_node_next->data, ants_node_prev->len_data) == 0)
		{
			return 0;
		}
		else
		{
			fprintf(stderr, "[%s] %s", __func__, "A function pointer to compare was NULL\n");
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "[%s] %s", __func__, "A data length was different\n");
		return -1;
	}
	
	return 0;
}


ants_list_t* ants_list_new(int (*fpcompare)(void* data_prev, void* data_next))
{
    ants_list_t* new_list = NULL;

    new_list = malloc(sizeof(ants_list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
	
	if (fpcompare == NULL) 	new_list->fpcompare = ants_list_compare_default;
	else 					new_list->fpcompare = fpcompare;

    new_list->cnt_nodes = 0;

    return new_list;
}


int ants_list_add_head(ants_list_t* list, void* data, int len_data)
{
    int ret = 0;
    ants_node_t* node_new = NULL;

    if (!list || !data || len_data == 0)
    {
		return -1;
    }

    node_new = malloc(sizeof(ants_node_t));
	memset(node_new, 0x00, sizeof(ants_node_t));
	
	node_new->data = malloc(len_data);
	memset(node_new->data, 0x00, len_data);
    memcpy(node_new->data, data, len_data);
	
	node_new->len_data = len_data;
	
    node_new->next = NULL;
    node_new->prev = NULL;

    if (list->head)
    {
		list->head->prev = node_new;
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


int ants_list_add_tail(ants_list_t* list, void* data, int len_data)
{
    int ret = 0;
    ants_node_t* node_new = NULL;

	if (!list || !data || len_data == 0)
    {
		return -1;
    }

    node_new = malloc(sizeof(ants_node_t));
	memset(node_new, 0x00, sizeof(ants_node_t));
	
	node_new->data = malloc(len_data);
	memset(node_new->data, 0x00, len_data);
    memcpy(node_new->data, data, len_data);
	
	node_new->len_data = len_data;
	
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

	list->cnt_nodes++;

    return ret;
}

int ants_list_show(ants_list_t* list)
{
	ants_node_t* node_curr = NULL;
	char buff_hex[8192] ={0};
	int index = 0;

	if (list->cnt_nodes == 0)
	{
		fprintf(stderr, "The list was empty\n");
		return -1;
	}

	fprintf(stdout, "[%s] list count : %d\n", __func__, list->cnt_nodes);

	for (node_curr=list->head; node_curr; node_curr=node_curr->next)
	{
		buff_hex[0] = '\0';
		memset(buff_hex, 0x00, sizeof(buff_hex));
		ants_str2hex(node_curr->data, buff_hex, sizeof(buff_hex), " ");
		fprintf(stdout, "[%d] %s, %d\n", index, node_curr->data, node_curr->len_data);
		fprintf(stdout, "[%d] %s\n", index++, buff_hex);
	}
	
	return 0;
}


int ants_list_find(ants_list_t* list, void* data, int len_data)
{
	int ret = 0;
	ants_node_t* node_curr = NULL;
	ants_node_t node_to_find;

	if (!list || !data)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "Arguments were invalied...\n");
		return -1;
	}

	if (!list->head)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "The head of list was NULL...\n");
		return -1;
	}
	
	if (!list->fpcompare)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "The compare function of list was NULL\n");
		return -1;
	}

	node_to_find.data = malloc(len_data);
	node_to_find.len_data = len_data;

	for (node_curr = list->head; node_curr; node_curr = node_curr->next)
	{
		ret = list->fpcompare(node_curr, &node_to_find);
		if (ret == 0) return 0;
	}
	
	return -1;
}


ants_node_t* ants_list_pop_head(ants_list_t* list)
{
	ants_node_t* node_ret = NULL;
	
	if (list == NULL)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "Arguments were invalied...\n");
		return NULL;
	}

	if (list->head == NULL)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "The list was empty...\n");
		return NULL;
	}

	node_ret = list->head;

	if (list->head->next)
	{
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	else
	{
		list->head = NULL;
		list->tail = NULL;
	}

	return node_ret;
}


ants_node_t* ants_list_pop_tail(ants_list_t* list)
{
	ants_node_t* node_ret = NULL;
	
	if (!list)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "Arguments were invalied...\n");
		return NULL;
	}

	if (list->tail == NULL)
	{
		fprintf(stderr, "[%s] %s\n", __func__, "The list wes empty...\n");
		return NULL;
	}

	node_ret = list->tail;

	if (list->tail->prev)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else
	{
		list->head = NULL;
		list->tail = NULL;
	}
	
	return node_ret;
}
