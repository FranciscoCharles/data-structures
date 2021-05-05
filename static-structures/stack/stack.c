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
    stack->top = -1;
    return stack;
}
Stack stack_delete(Stack stack) {
    free(stack);
    stack = NULL;
    return stack;
}
bool stack_is_empty(Stack stack) {
    return stack->top == -1;
}
bool stack_is_full(Stack stack) {
    return ( stack->top + 1 ) == MAX_SIZE_STACK;
}
bool stack_push(Stack stack, int data) {
    if(stack_is_full(stack)) {
        return false;
    }
    stack->data[ ++stack->top ] = data;
    return true;
}
bool stack_pop(Stack stack, int *data) {
    if(stack_is_empty(stack)) {
        return false;
    }
    *data = stack->data[ stack->top-- ];
    return true;
}
void stack_print(Stack stack) {
    if(stack_is_empty(stack)) {
        printf("stack is empty.\n");
    } else {
        int index;
        for(index = stack->top; index > -1 ; --index) {
            printf("[ %d ]\n", stack->data[ index ]);
        }
    }
}
