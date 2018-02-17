#include "ants_list.h"

int test_init();
int test_add();
int test_show();
int test_compare();
int test_delete();

int main()
{
	char* test_msg="test message";
	int test_len=strlen(test_msg);
	
	printf("Start ants list test !!!\n");
	
	ants_list_t* pants_list = NULL;
	
	if (test_init(&pants_list) == -1)
	{
		fprintf(stderr, "test_init() was failed...\n");
		return -1;
	}

	if (test_add(pants_list, test_msg, test_len) == -1)
	{
		fprintf(stderr, "test_add() was failed...\n");
		return -1;
	}
	
	return 0;
}


int test_init(ants_list_t** ants_list)
{
	*ants_list = ants_list_new(NULL);
	if (*ants_list == NULL)
	{
		return -1;
	}

	return 0;
}


int test_add(ants_list_t* ants_list, void* data, int len_data)
{
	if (ants_list_add_head(ants_list, data, len_data) == -1)
	{
		return -1;
	}
	
	return 0;
}


