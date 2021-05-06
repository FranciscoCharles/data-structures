#ifndef _DEQUE_H_
#define _DEQUE_H_

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE_DEQUE 10

struct Deque{
	int size;
    int first;
    int last;
	int data[MAX_SIZE_DEQUE];
};
typedef struct Deque* Deque;

Deque deque_create(void);
Deque deque_delete(Deque deque);
int deque_get_first(Deque deque);
int deque_get_last(Deque deque);
bool deque_is_empty(Deque deque);
bool deque_is_full(Deque deque);
bool deque_push(Deque deque, int data);
bool deque_push_front(Deque deque, int data);
bool deque_pop(Deque deque, int *data);
bool deque_pop_front(Deque deque, int *data);
void deque_print(Deque deque);

#endif