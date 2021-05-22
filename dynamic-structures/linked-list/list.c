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

    Data current = list->head;
    if(current == NULL) {
        list->head = data;
    } else {
        Data previous = NULL;

        while ((current != NULL)) {
            previous = current;
            current = current->next;
        }
        if(previous == NULL) {
            current->next = data;
        } else {
            previous->next = data;
        }
    }
    list->size++;
}
void list_insert_ordered(List list, Data data) {

    Data current = list->head;
    Data previous = NULL;

    while ((current!=NULL) && (current->value < data->value)) {
        previous = current;
        current = current->next;
    }
    data->next = current;
    if (previous == NULL) {
        list->head = data;
    } else {
        previous->next = data;
    }
    list->size++;
}
void list_insert(List list, unsigned index, Data data) {

    Data current = list->head;
    Data previous = NULL;

    while ((current!=NULL) && index > 0) {
        previous = current;
        current = current->next;
        index--;
    }
    data->next = current;
    if (previous == NULL) {
        list->head = data;
    } else {
        previous->next = data;
    }
    list->size++;
}
bool list_is_empty(List list) {
    return list->head == NULL;
}
Data list_pop(List list) {

    Data current = list->head;

    if (current != NULL) {

        Data previous = NULL;

        while ((current->next != NULL)) {
            previous = current;
            current = current->next;
        }
        if(previous == NULL) {
            list->head = NULL;
        } else {
            previous->next = NULL;
        }
        list->size--;
    }
    return current;
}
Data list_pop_front(List list) {

    Data current = list->head;

    if (current != NULL) {
        list->head = current->next;
        list->size--;
    }
    return current;
}
void list_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->head;
        for ( ; data != NULL; data = data->next) {
            data_print(data);
        }
    }
}
void list_push(List list, Data data) {

    data->next = list->head;
    list->head = data;
    list->size++;
}
Data list_remove(List list, unsigned index) {

    Data current = list->head;

    if (current != NULL) {
        Data previous = NULL;
        while ((current->next != NULL) && (index > 0)) {
            previous = current;
            current = current->next;
            index--;
        }
        if (previous == NULL) {
            list->head = current->next;
        } else if(current != NULL) {
            previous->next = current->next;
        }
        list->size--;
    }
    return current;
}

Data list_remove_value(List list, int value) {

    Data current = list->head;

    if (current != NULL) {
        Data previous = NULL;

        while ((current != NULL) && (current->value != value)) {
            previous = current;
            current = current->next;
        }
        if (previous == NULL) {
            list->head = current->next;
            list->size--;
        } else if (current != NULL) {
            previous->next = current->next;
            list->size--;
        }
    }
    return current;
}