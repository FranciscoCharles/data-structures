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
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}
Queue queue_delete(Queue queue) {
    Data tmp = NULL;
    while(queue->first != NULL) {
        tmp = queue->first;
        queue->first = tmp->next;
        tmp = data_delete(tmp);
    }
    queue->last = NULL;
    free(queue);
    queue = NULL;
    return queue;
}
bool queue_is_empty(Queue queue) {
    return queue->first == NULL;
}
bool queue_push(Queue queue, int data) {
    Data new_data = data_create();
    if(new_data == NULL) {
        return false;
    }
    new_data->value = data;
    if(queue->first == NULL) {
        queue->first = new_data;
    } else {
        queue->last->next = new_data;
    }
    queue->last = new_data;
    return true;
}
bool queue_pop(Queue queue, int *data) {
    if(queue_is_empty(queue)) {
        return false;
    }
    Data tmp = queue->first;
    *data = tmp->value;
    queue->first = tmp->next;
    if(queue->first == NULL) {
        queue->last = NULL;
    }
    tmp = data_delete(tmp);
    return true;
}
void queue_print(Queue queue) {
    if(queue_is_empty(queue)) {
        printf("queue is empty.\n");
    } else {
        Data data;
        for(data = queue->first; data!=NULL; data=data->next) {
            printf("[ %d ]\n", data->value);
        }
        data = NULL;
    }
}
size_t queue_size(Queue queue) {
	size_t size = 0;
    Data data = queue->first;
    while( data != NULL ) {
    	data = data->next;
        ++size;
    }
    data = NULL;
    return size;
}