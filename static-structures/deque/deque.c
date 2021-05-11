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

static int get_correct_index(int index) {
    if(index < 0) {
        return MAX_SIZE_DEQUE - abs(index)%MAX_SIZE_DEQUE;
    }
    return index % MAX_SIZE_DEQUE;
}
Deque deque_create(void) {
    Deque deque = malloc(sizeof(struct Deque));
    deque->first = 0;
    deque->last = 0;
    deque->size = 0;
    return deque;
}
Deque deque_delete(Deque deque) {
    free(deque);
    deque = NULL;
    return deque;
}
int deque_get_first(Deque deque){
	if(deque_is_empty(deque)){
		return -1;
	}
	return deque->first;
}
int deque_get_last(Deque deque){
	if(deque_is_empty(deque)){
		return -1;
	}
	return get_correct_index(deque->last - 1);
}
bool deque_is_empty(Deque deque) {
    return deque->size == 0;
}
bool deque_is_full(Deque deque) {
    return deque->size == MAX_SIZE_DEQUE;
}
bool deque_push(Deque deque, int data) {
    if(deque_is_full(deque)) {
        return false;
    }
    deque->data[ deque->last ] = data;
    deque->last = get_correct_index(deque->last + 1);
    ++deque->size;
    return true;
}
bool deque_push_front(Deque deque, int data) {
    if(deque_is_full(deque)) {
        return false;
    }
    deque->first = get_correct_index(deque->first - 1);
    deque->data[ deque->first ] = data;
    ++deque->size;
    return true;
}
bool deque_pop(Deque deque, int *data) {
    if(deque_is_empty(deque)) {
        return false;
    }
    *data = deque->data[ deque->last];
    deque->last = get_correct_index(deque->last - 1);
    --deque->size;
    return true;
}
bool deque_pop_front(Deque deque, int *data) {
    if(deque_is_empty(deque)) {
        return false;
    }
    *data = deque->data[ deque->first ];
    deque->first = get_correct_index(deque->first + 1);
    --deque->size;
    return true;
}
void deque_print(Deque deque) {
    if(deque_is_empty(deque)) {
        printf("Deque is empty.\n");
    } else {
        int index = deque->first;
        do {
            printf("[ %d ]\n", deque->data[ index ]);
            index = (index + 1)%MAX_SIZE_DEQUE;
        } while(index != deque->last);
    }
}

