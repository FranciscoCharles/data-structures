#include "list.h"

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

List list_create() {
    List list = malloc(sizeof(struct List));
    list->size = 0;
    list->head = NULL;
    list->last = NULL;
    return list;
}
List list_delete(List list) {

    Data tmp = list->head;

    while (tmp != NULL) {
        list->head = tmp->next;
        tmp = data_delete(tmp);
        tmp = list->head;
    }
    free(list);
    list = NULL;
    return list;
}
void list_append(List list, Data data) {

    Data last = list->last;
    if(last == NULL) {
        list->head = list->last = data;
    } else {
        data->prev = last;
        last->next = list->last = data;
    }
    list->size++;
}
static void list_insert_into(List list, Data previous, Data current, Data data) {
    data->next = current;
    data->prev = previous;

    if (current != NULL) {
        current->prev = data;
    } else {
        list->last = data;
    }
    if(previous == NULL) {
        list->head = data;
    } else {
        previous->next = data;
    }
    list->size++;
}
void list_insert_ordered(List list, Data data) {

    Data previous = NULL;
    Data current = list->head;

    while ((current != NULL)&& (current->value < data->value)) {
        previous = current;
        current = current->next;
    }
    list_insert_into(list, previous, current, data);
}
void list_insert(List list, unsigned index, Data data) {

    Data previous = NULL;
    Data current = list->head;

    while ((current != NULL) && ( index > 0)) {
        previous = current;
        current = current->next;
        index--;
    }
    list_insert_into(list, previous, current, data);
}

bool list_is_empty(List list) {
    return list->head == NULL;
}

Data list_pop(List list) {

    Data current = list->last;

    if (current != NULL) {

        Data previous = current->prev;

        if (previous == NULL) {
            list->head = list->last = NULL;
        } else {
            previous->next = NULL;
            list->last = previous;
        }
        current->prev = current->next = NULL;
        list->size--;
    }
    return current;
}
Data list_pop_front(List list) {

    Data current = list->head;

    if (current != NULL) {
        if(current->next != NULL) {
            current->next->prev = NULL;
        } else {
            list->last = NULL;
        }
        list->head = current->next;
        current->prev = current->next = NULL;
        list->size--;
    }
    return current;
}
void list_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->head;
        while(data != NULL) {
            data_print(data);
            data = data->next;
        }
    }
}
void list_reverse_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->last;
        while(data != NULL) {
            data_print(data);
            data = data->prev;
        }
    }
}
void list_push(List list, Data data) {

    data->next = list->head;
    if(list->head != NULL) {
        list->head->prev = data;
    } else {
        list->last = data;
    }
    list->head = data;
    list->size++;
}
static Data list_remove_from(List list, Data previous, Data current) {
    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = previous;
    } else {
        list->last = previous;
    }
    current->prev = current->next = NULL;
    list->size--;
    return current;
}
Data list_remove(List list, unsigned index) {

    Data current = list->head;

    Data previous = NULL;

    while ((current->next != NULL) && ( index > 0)) {
        previous = current;
        current = current->next;
        index--;
    }
    return (current != NULL) ? list_remove_from(list, previous, current) : NULL;
}

Data list_remove_value(List list, int value) {

    Data current = list->head;
    Data previous = NULL;

    while ((current != NULL) && (current->value != value)) {
        previous = current;
        current = current->next;
    }
    return (current != NULL) ? list_remove_from(list, previous, current) : NULL;
}
