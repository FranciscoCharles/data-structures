#include "deque.h"

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

Deque deque_create(void) {
    Deque deque = malloc(sizeof(struct Deque));
    deque->first = NULL;
    return deque;
}
Deque deque_delete(Deque deque) {
    Data tmp = NULL;
    while(deque->first != NULL) {
        tmp = deque->first;
        deque->first = tmp->next;
        tmp = data_delete(tmp);
    }
    deque->last = NULL;
    free(deque);
    deque = NULL;
    return deque;
}
bool deque_is_empty(Deque deque) {
    return deque->first == NULL;
}
bool deque_push_front(Deque deque, int data) {
    Data new_data = data_create();
    if(new_data == NULL) {
        return false;
    }
    new_data->value = data;
    new_data->next = deque->first;
    if(deque_is_empty(deque)) {
        deque->last = new_data;
    }
    deque->first = new_data;
    return true;
}
bool deque_push(Deque deque, int data) {
    Data new_data = data_create();
    if(new_data == NULL) {
        return false;
    }
    new_data->value = data;
    if(deque_is_empty(deque)) {
        deque->first = new_data;
    } else {
        deque->last->next = new_data;
    }
    deque->last = new_data;
    return true;
}
bool deque_pop_front(Deque deque, int *data) {
    if(deque_is_empty(deque)) {
        return false;
    }
    Data tmp = deque->first;
    *data = tmp->value;
    deque->first = tmp->next;
    tmp = data_delete(tmp);
    if(deque_is_empty(deque)) {
        deque->last = NULL;
    }
    return true;
}
bool deque_pop(Deque deque, int *data) {
    if(deque_is_empty(deque)) {
        return false;
    }
    Data tmp = deque->first;
    *data = deque->last->value;
    if(tmp != deque->last) {
        while(tmp->next != deque->last) {
            tmp = tmp->next;
        }
        tmp->next = data_delete(deque->last);
        deque->last = tmp;
    } else {
        deque->last = data_delete(deque->last);;
    }
    tmp = NULL;
    if(deque->last == NULL) {
        deque->first = NULL;
    }
    return true;
}
void deque_print(Deque deque) {
    if(deque_is_empty(deque)) {
        printf("deque is empty.\n");
    } else {
        Data data;
        for(data = deque->first; data!=NULL; data=data->next) {
            printf("[ %d ]\n", data->value);
        }
        data = NULL;
    }
}
size_t deque_size(Deque deque) {
    size_t size = 0;
    Data data = deque->first;
    while( data != NULL ) {
        data = data->next;
        ++size;
    }
    data = NULL;
    return size;
}
