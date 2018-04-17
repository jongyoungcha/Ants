#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

typedef struct qnode
{
	void* data;
	int len;
	struct qnode* next;
} qnode_t;


typedef struct lf_queue
{
	int len;
	char qname[64];
	qnode_t* first;
	qnode_t* end;
	
} lf_queue_t;

qnode_t* ants_lfq_new_node(void* data, int len);
int free_node( qnode_t* qnode );
lf_queue_t* ants_lfq_init_queue( const char* qname );
int ants_lfq_push_node( lf_queue_t* queue , void* data, int len );
int ants_lfq_pop_node( lf_queue_t* queue, qnode_t** node_out );
void ants_lfq_print_queue ( lf_queue_t* queue );
