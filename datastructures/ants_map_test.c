#include <ants_map.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* struct st_temp */
/* { */
/* 	int num; */
/* 	char name[100]; */
	
/* } arr_test[] = { */
/* 	{1, "john"}, */
/* 	{2, "Marry"}, */
/* 	{3, "Zilea"}, */
/* 	{4, "Garry"}, */
/* 	{5, "Homma"} */
/* }; */

/* typedef struct st_temp st_temp_t; */

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
	ants_map_node_t* node_find = NULL;

	node_find = ants_map_node_new(&arr_test[5], sizeof(st_temp_t));

	map = ants_map_new(NULL);
	if (map)
	{
		/* print_node(&arr_test[0]); */
		/* print_node(&arr_test[1]); */
		/* print_node(&arr_test[2]); */
		
		ants_map_insert(map, &arr_test[0], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[1], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[2], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[3], sizeof(st_temp_t));
		ants_map_insert(map, &arr_test[4], sizeof(st_temp_t));
	}

	ants_map_walk(map, print_node);
	ants_map_find_with_node(map, node_find);

	return 0;
}
