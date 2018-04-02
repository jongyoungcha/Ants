#include <ants_map.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* test_string="my test!!!!\n";
	char* data1 = "node data1\n";
	char* data2 = "node data2\n";
	char* data3 = "node data3\n";
	int len_md5 = 0;
	unsigned char* md5 = NULL;
	ants_map_t* map = NULL;

	map = ants_map_new(NULL);

	ants_map_insert(map, data1, strlen(data1));
	ants_map_insert(map, data2, strlen(data2));
	ants_map_insert(map, data3, strlen(data3));

	return 0;
}
