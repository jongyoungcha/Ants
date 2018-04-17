#include <ants_lock_free_queue.h>



qnode_t* ants_lfq_new_node(void* data, int len)
{
	qnode_t* ret_node = NULL;

	if (data)
	{
		ret_node = malloc(sizeof(qnode_t));
		memset(ret_node, 0x00, sizeof(qnode_t));
		ret_node->next = NULL;
		
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


int ants_lfq_free_node( qnode_t* qnode )
{
	if (qnode)
	{
		if (qnode->data) free(qnode->data);
		free(qnode);
	}
	
	return 0;
}


lf_queue_t* ants_lfq_init_queue( const char* qname )
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


int ants_lfq_push_node( lf_queue_t* queue , void* data, int len )
{
	qnode_t* node_new = NULL;

	if ( queue )
	{
		node_new = ants_lfq_new_node(data, len);
		if ( node_new == NULL ) fprintf(stderr, "Allocating new node was failed...\n");

		if ( (queue->first == NULL) && (queue->end == NULL) )
		{
			queue->first = node_new;
			queue->end = node_new;
		}
		else
		{
			queue->end->next = node_new;
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


int ants_lfq_pop_node( lf_queue_t* queue, qnode_t** node_out )
{
	qnode_t* node_old = NULL;

	if ( queue )
	{
		if ( queue->first )
		{
			node_old = queue->first;
			*node_out = node_old;
			
			if (__sync_val_compare_and_swap(&(queue->first), node_old, node_old->next))
			{
				if ( node_old->next )
				{
					queue->first = node_old->next;
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
				queue->first = node_old;
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
}


void ants_lfq_print_queue ( lf_queue_t* queue )
{
	qnode_t* node_crr = NULL;

	node_crr = queue->first;
	while ( node_crr )
	{
		printf("* length of data : %d, %s\n", node_crr->len, node_crr->data);
		
		if (node_crr->next)
		{
			node_crr = node_crr->next;
		}
		else
		{
			node_crr = NULL;
		}
	}
	
	return;
}
