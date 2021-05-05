#include "queue.h"

/*
MIT License

Copyright (c) 2021 FranciscoCharles

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

Queue queue_create(void) {
    Queue queue = malloc(sizeof(struct Queue));
    queue->first = 0;
    queue->last = 0;
    queue->size = 0;
    return queue;
}
Queue queue_delete(Queue queue) {
    free(queue);
    queue = NULL;
    return queue;
}
bool queue_is_empty(Queue queue) {
    return queue->size == 0;
}
bool queue_is_full(Queue queue) {
    return queue->size == MAX_SIZE_QUEUE;
}
bool queue_push(Queue queue, int data) {
    if(queue_is_full(queue)) {
        return false;
    }
    queue->data[ queue->last ] = data;
    queue->last = (queue->last + 1)%MAX_SIZE_QUEUE;
    queue->size++;
    return true;
}
bool queue_pop(Queue queue, int *data) {
    if(queue_is_empty(queue)) {
        return false;
    }
    *data = queue->data[ queue->first ];
    queue->first = (queue->first + 1)%MAX_SIZE_QUEUE;
    queue->size--;
    return true;
}
void queue_print(Queue queue) {
    if(queue_is_empty(queue)) {
        printf("queue is empty.\n");
    } else {
        int index = queue->first;
        do {
            printf("[ %d ]\n", queue->data[ index ]);
            index = (index + 1)%MAX_SIZE_QUEUE;
        } while(index != queue->last);
    }
}
