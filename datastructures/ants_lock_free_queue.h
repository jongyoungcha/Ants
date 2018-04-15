#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct qnode
{
	void* data;
	int len;
	struct qnode* next;
} qnode_t;


typedef struct lf_queue
{
	int len;
	char* qname;
	qnode_t* first;
	qnode_t* end;
	
} lf_queue_t;

qnode_t* new_node(void* data, int len);
int free_node( qnode_t* qnode );
lf_queue_t* init_queue( const char* qname );
int push_node( lf_queue_t* queue , void* data, int len );
int pop_node( lf_queue_t* queue, qnode_t** node_out );
void print_queue ( lf_queue_t* queue );
