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

	
	queue = init_queue("test_queue");

	for (i=0; i<5; i++)
	{
		ret = push_node(queue, arr_data[i], strlen(arr_data[i]));
		if (ret < 0)
		{
			fprintf(stderr, "push_node() error!!!\n");
		}
	}


	print_queue(queue);
	
	return 0;
}
