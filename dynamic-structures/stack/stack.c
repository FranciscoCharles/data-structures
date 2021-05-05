#include "stack.h"

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

Stack stack_create(void) {
    Stack stack = malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}
Stack stack_delete(Stack stack) {
    Data tmp = NULL;
    while(stack->top != NULL) {
        tmp = stack->top;
        stack->top = tmp->next;
        tmp = data_delete(tmp);
    } 
    free(stack);
    stack = NULL;
    return stack;
}
bool stack_is_empty(Stack stack) {
    return stack->top == NULL;
}
bool stack_push(Stack stack, int data) {
    Data new_data = data_create();
    if(new_data == NULL) {
        return false;
    }
    new_data->value = data;
    new_data->next = stack->top;
    stack->top = new_data;
    return true;
}
bool stack_pop(Stack stack, int *data) {
    if(stack_is_empty(stack)) {
        return false;
    }
    Data tmp = stack->top;
    *data = tmp->value;
    stack->top = tmp->next;
    tmp = data_delete(tmp);
    return true;
}
void stack_print(Stack stack) {
    if(stack_is_empty(stack)) {
        printf("stack is empty.\n");
    } else {
        Data data;
        for(data = stack->top; data!=NULL; data=data->next) {
            printf("[ %d ]\n", data->value);
        }
        data = NULL;
    }
}

size_t stack_size(Stack stack) {
    size_t size = 0;
    Data data = stack->top;
    while( data != NULL ) {
        data = data->next;
        ++size;
    }
    data = NULL;
    return size;
}
