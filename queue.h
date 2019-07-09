#include <stdbool.h>

// Queue: provides an Integer Queue ADT
// NOTE: ALL queue parameters must be valid queues

struct queue;

// queue_create() creates a new empty queue
// effects: allocates memory (client must call queue_destroy)
struct queue *queue_create(void);

// queue_is_empty(q) determines if queue q is empty
bool queue_is_empty(const struct queue *q);

// queue_front(q) returns the front item in queue q
// requires: queue is not empty
int queue_front(const struct queue *q);

// queue_remove_front(q) returns and removes the front item from queue q
// requires: queue is not empty
// effects: modifies q
int queue_remove_front(struct queue *q);

// queue_add_back(item, q) adds item to the back of queue q
// effects: modifies q
void queue_add_back(int item, struct queue *q);

// queue_destroy(q) frees all memory for q
// effects: q is no longer valid
void queue_destroy(struct queue *q);