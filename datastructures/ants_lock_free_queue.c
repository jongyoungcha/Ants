#include <ants_lock_free_queue.h>

qnode_t* new_node(void* data, int len)
{
	qnode_t* ret_node = NULL;

	if (data)
	{
		ret_node = malloc(len);
		ret_node->data = malloc(len);
		memcpy(ret_node->data, data, len);
		ret_node->len = len;
		
		return ret_node;
	}
	else
	{
		printf("data was NULL");
		return NULL;
	}
}


int free_node( qnode_t* qnode )
{
	if (qnode)
	{
		if (qnode->data) free(qnode->data);
		free(qnode);
	}

	
	return 0;
}


lf_queue_t* init_queue( const char* qname )
{
	lf_queue_t* ret_queue = NULL;

	ret_queue = malloc(sizeof(lf_queue_t));
	memset(ret_queue, 0x00, sizeof(lf_queue_t));
	
	snprintf(ret_queue->qname, sizeof(ret_queue->qname), "%s", qname);
	ret_queue->len = 0;
	ret_queue->first = NULL;
	ret_queue->end = NULL;

	return ret_queue;
}


int push_node( lf_queue_t* queue , void* data, int len )
{
	qnode_t* node_new = NULL;

	if ( queue )
	{
		node_new = new_node(data, len);
		if ( node_new == NULL ) fprintf(stderr, "Allocating new node was failed...\n");

		if ( queue->end )
		{
			queue->end->next = node_new;
			queue->end = node_new;
		}
		else
		{
			queue->first = node_new;
			queue->end = node_new;
		}
		
		return 0;
	}
	else
	{
		fprintf(stderr, "queue was NULL....");
		return -1;
	}
}


int pop_node( lf_queue_t* queue, qnode_t** node_out )
{
	qnode_t* node_crr = NULL;

	if ( queue )
	{
		if ( queue->first )
		{
			node_crr = queue->first;
			
			*node_out = node_crr;
			if ( node_crr->next )
			{
				queue->first = node_crr->next;
			}
			else
			{
				queue->first = NULL;
				queue->end = NULL;
			}

			return 0;
		}
		else
		{
			return -1;
		}
	}
}


void print_queue ( lf_queue_t* queue )
{
	qnode_t* node_crr = NULL;

	node_crr = queue->first;
	while ( node_crr )
	{
		printf("* length of data : %d\n", node_crr->len);
		node_crr = node_crr->next;
	}
	
	return;
}
