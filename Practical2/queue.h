
#ifndef NSD_QUEUE_H
#define NSD_QUEUE_H

using namespace std;
struct Node{
    long val;
    Node* next;
};
typedef struct Node Node;

struct Queue{
    Node* first;
    Node* last;
    long length;
};
typedef struct Queue Queue;

Node* node_init(long val);
void node_deinit(Node* node);
Queue* queue_init();
void queue_deinit(Queue* queue);
long queue_pop(Queue* queue);
void queue_push(Queue* queue, long node);
long queue_first(Queue* queue);
long queue_last(Queue* queue);
void queue_print(Queue* queue);
bool queue_is_empty(Queue* queue);

#endif //NSD_QUEUE_H
