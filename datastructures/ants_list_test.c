#include "ants_list.h"
#include <string.h>

int test_init();
int test_add();
int test_show();
int test_compare();
int test_pop();

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

	if (test_show(pants_list) == -1)
	{
		fprintf(stderr, "test_show() was failed..\n");
		return -1;
	}

	if (test_pop(pants_list) == -1)
	{
		fprintf(stderr, "test_pop() was failed..\n");
		return -1;
	}

	if (test_show(pants_list) == -1)
	{
		fprintf(stderr, "test_show() was failed..\n");
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


int test_add(ants_list_t* ants_list)
{
	char* tmplt_msg="test message";
	char buf_msg[8192] = {0};
	int len_buf = 0;
	int i = 0;

	for (i=0; i<10; i++)
	{
		sprintf(buf_msg, "%s%d\n", tmplt_msg, i);
		len_buf = strlen(buf_msg);
		if (ants_list_add_head(ants_list, buf_msg, len_buf) == -1)
		{
			return -1;
		}
	}

	for (; i<20; i++)
	{
		sprintf(buf_msg, "%s%d\n", tmplt_msg, i);
		len_buf = strlen(buf_msg);
		if (ants_list_add_tail(ants_list, buf_msg, len_buf) == -1)
		{
			return -1;
		}
	}

	return 0;
}

int test_show(ants_list_t* ants_list)
{
	if (ants_list_show(ants_list) == -1)
	{
		return -1;
	}
	
	return 0;
}


int test_pop(ants_list_t* ants_list)
{
	ants_node_t* pnode = NULL;
	int i = 0;

	for (i=0; i<10; i++)
	{
		pnode =	ants_list_pop_head(ants_list);
		if (pnode)
		{
			fprintf(stdout, "%s", pnode->data);
			free(pnode);
		}
		else
		{
			fprintf(stderr, "pop_head() was failed...\n");
		}
	}

	for (; i<20; i++)
	{
		pnode =	ants_list_pop_tail(ants_list);
		if (pnode)
		{
			fprintf(stdout, "%s", pnode->data);
			free(pnode);
		}
		else
		{
			fprintf(stderr, "pop_tail() was failed...\n");
		}
	}


	return 0;
}

