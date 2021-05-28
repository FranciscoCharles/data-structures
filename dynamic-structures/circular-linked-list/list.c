#include "list.h"

/*
MIT License

Copyright (c) 2021 FranciscoCharles

Permission is hereby grpreved, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substprevial portions of the Software.

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
    Data data = list->head;

    if(data != NULL) {
        Data tmp = NULL;

        do {
            tmp = data;
            data = data->next;
            tmp = data_delete(tmp);
        } while(data != list->head );

        data = list->head = list->last = NULL;
    }
    free(list);
    list = NULL;
    return list;
}
void list_append(List list, Data data) {

    Data current = list->head;

    if(current == NULL) {
        list->head = list->last = data->next = data;
    } else {
        while (current->next != list->head) {
            current = current->next;
        }
        data->next = list->head;
        list->last = current->next = data;
    }
    list->size++;
}
void list_insert_ordered(List list, Data data) {

    Data current = list->head;
    Data previous = NULL;
    if(current == NULL) {
        list->head = list->last = data->next = data;
    } else {
        do {
            if (current->value > data->value) {
                break;
            }
            previous = current;
            current = current->next;
        } while (current != list->head);

        data->next = current;

        if (previous == NULL) {
            list->head = data;
            list->last->next = data;
        } else {
            previous->next = data;
            if(current == list->head) {
                list->last = data;
            }
        }
    }

    list->size++;
}
void list_insert(List list, unsigned index, Data data) {

    Data current = list->head;
    Data previous = NULL;
    if(current == NULL) {
        list->head = list->last = data->next = data;
    } else {
        do {
            if (index < 1) {
                break;
            }
            index--;
            previous = current;
            current = current->next;
        } while (current != list->head);

        data->next = current;

        if (previous == NULL) {
            list->head = data;
            list->last->next = data;
        } else {
            previous->next = data;
            if(current == list->head) {
                list->last = data;
            }
        }
    }
    list->size++;
}
bool list_is_empty(List list) {
    return list->head == NULL;
}
Data list_pop(List list) {
    Data current = list->head;
    if(current != NULL) {
        Data previous = NULL;
        while (current->next != list->head) {
            previous = current;
            current = current->next;
        }
        if(previous == NULL) {
            list->head = list->last = NULL;
        } else {
            previous->next = list->head;
            list->last = previous;
        }
        list->size--;
    }
    return current;
}
Data list_pop_front(List list) {
    Data current = list->head;
    if(current != NULL) {
        if(current->next != list->head) {
            list->last->next = list->head = current->next;
        } else {
            list->head = list->last = NULL;
        }
        list->size--;
    }
    return current;
}
void list_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->head;
        while(data->next != list->head ) {
            data_print(data);
            data = data->next;
        }
        data_print(data);
    }
}
void list_push(List list, Data data) {

    data->next = list->head;
    list->head = data;
    if(list->last == NULL) {
        list->last = data;
    } else {
        list->last->next = data;
    }
    list->size++;
}
Data list_remove(List list, unsigned index) {

    Data current = list->head;

    if (current != NULL) {
        Data previous = NULL;
        index = (index < list->size)? index : (list->size - 1);
        do {
            if ( index < 1 ) {
                break;
            }
            index--;
            previous = current;
            current = current->next;
        } while (current != list->head);

        if (previous == NULL) {
            if(current->next == list->head) {
                list->head = list->last = NULL;
            } else {
                list->head = list->last->next = current->next;
            }
        } else {
            previous->next = current->next;
            if(current == list->last) {
                list->last = previous;
            }
        }
        current->next = NULL;
        list->size--;
    }
    return current;
}

Data list_remove_value(List list, int value) {

    Data current = list->head;

    if (current != NULL) {
        Data previous = NULL;
        do {
            if (current->value == value) {
                break;
            }
            previous = current;
            current = current->next;
        } while (current != list->head);

        if(current->value == value) {

            if (previous == NULL) {
                if(current->next == list->head) {
                    list->head = list->last = NULL;
                } else {
                    list->head = list->last->next = current->next;
                }
            } else {
                previous->next = current->next;
                if(current == list->last) {
                    list->last = previous;
                }
            }
            current->next = NULL;
            list->size--;

        } else {
            current = NULL;
        }

    }
    return current;
}
