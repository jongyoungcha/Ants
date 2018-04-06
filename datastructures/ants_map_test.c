#include <ants_map.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


st_temp_t arr_test[] = {
	{1, "john"},
	{2, "Marry"},
	{3, "Zilea"},
	{4, "Garry"},
	{5, "Homma"},
	{6, "Tester"}
};


void print_node(void* data)
{
	st_temp_t* temp = (st_temp_t*) data;
	printf("===========================\n");
	printf("num : %d\n", temp->num);
	printf("name : %s\n", temp->name);
}


int main()
{
	ants_map_t* map = NULL;
	ants_map_node_t* node_none = NULL;
	ants_map_node_t* node_one = NULL;
	
	node_none = ants_map_node_new(&arr_test[5], sizeof(st_temp_t));	
	node_one = ants_map_node_new(&arr_test[4], sizeof(st_temp_t));

	map = ants_map_new(NULL);
	if (map)
	{
		ants_map_insert(map, &arr_test[0], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[1], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[2], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[3], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[4], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[0], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[1], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[2], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[3], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[4], sizeof(st_temp_t));
	}

	fprintf(stdout, "** We will start walk map!!!\n");
	ants_map_walk(map, print_node);
	
	fprintf(stdout, "** We will find a node not existing...\n");
	if (ants_map_find_with_node(map, node_none) == 0)
	{
		fprintf(stdout, "We found!!!\n");
	}
	else
	{
		fprintf(stdout, "Could not found!!!\n");
	}

	fprintf(stdout, "** We will find a node existing...\n");
	if (ants_map_find_with_node(map, node_one) == 0)
	{
		fprintf(stdout, "We found!!!\n");
	}
	else
	{
		fprintf(stdout, "Could not found!!!\n");
	}

	return 0;
}
