#include <ants_lock_free_queue.h>


int main( int argc, char* argv[] )
{
	int ret = 0;
	int len = 5;
	int i = 0;
		
	char* arr_data[5] = {
		"aaaa1",
		"aaaa2",
		"aaaa3",
		"aaaa4",
		"aaaa5",
	};

	lf_queue_t* queue = NULL;
	qnode_t* pqnode = NULL;
	
	queue = ants_lfq_init_queue("test_queue");
	for (i=0; i<5; i++)
	{
		ret = ants_lfq_push_node(queue, arr_data[i], strlen(arr_data[i]));
		if (ret < 0)
		{
			fprintf(stderr, "push_node() error!!!\n");
		}
	}
	ants_lfq_print_queue(queue);
	
	ants_lfq_pop_node(queue, &pqnode);
	printf("%d %s\n", pqnode->len, pqnode->data);
	ants_lfq_pop_node(queue, &pqnode);
	printf("%d %s\n", pqnode->len, pqnode->data);
	ants_lfq_pop_node(queue, &pqnode);
	printf("%d %s\n", pqnode->len, pqnode->data);
	ants_lfq_pop_node(queue, &pqnode);
	printf("%d %s\n", pqnode->len, pqnode->data);
	ants_lfq_pop_node(queue, &pqnode);
	printf("%d %s\n", pqnode->len, pqnode->data);

	if ((ret = ants_lfq_pop_node(queue, &pqnode)) != 0)
	{
		fprintf(stderr, "push_node() error!!!\n");
	}
	
	return 0;
}
