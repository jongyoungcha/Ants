#include "ants_list.h"


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

	printf("called!!!\n");

    if (!list || !data || len_data == 0)
    {
		return -1;
    }

	printf("test1");

    node_new = malloc(sizeof(ants_node_t));
    node_new->data = data;
	node_new->len_data = len_data;
    node_new->next = NULL;
    node_new->prev = NULL;

	printf("test2");

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

    if (!list)
    {
		return -1;
    }

    node_new = malloc(sizeof(ants_node_t));

    node_new->data = data;
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


int ants_list_find(ants_list_t* list, void* data, int len_data)
{
	int ret = 0;
	ants_node_t* node_curr = NULL;
	ants_node_t node_to_find;

	if (!list || !data)
	{
		fprintf(stderr, "[%s] %s\n", __func__, data);
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


int ants_list_pop_from_head(ants_list_t* list, ants_node_t* ants_node)
{
	
	
	return -1;
}
