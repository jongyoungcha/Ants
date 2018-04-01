#include <ants_map.h>
#include <string.h>


int main()
{
	int ret = 0;
	char* test_string="my test!!!!\n";
	char* md5 = NULL;

	md5 = ants_map_get_key(test_string, strlen(test_string));

	
	return 0;
}
