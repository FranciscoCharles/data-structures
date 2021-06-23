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
static void list_insert_into(List list, Data current, Data data, bool is_first) {

    data->next = current;
    current->previous->next = data;
    data->previous = current->previous;
    current->previous = data;

    if (is_first) {
        list->head = data;
    } else if(current == list->head) {
        list->last = data;
    }
}
static Data list_remove_from(List list, Data current, bool is_first) {
    if (is_first) {
        return list_pop_front(list);
    }
    current->previous->next = current->next;
    current->next->previous = current->previous;

    if(current == list->last) {
        list->last = current->previous;
    }
    list->size--;
    current->next = current->previous = NULL;
    return current;
}
void list_append(List list, Data data) {
	
    if(list->last == NULL) {
        list->head = list->last = data;
        data->previous = data->next = data;
    } else {
        list->last->next = data;
        data->next = list->head;
        list->head->previous = data;
        data->previous = list->last;
        list->last = data;
    }
    list->size++;
}
void list_insert_ordered(List list, Data data) {

    Data current = list->head;
    if(current == NULL) {
        data->previous = data->next = data;
        list->head = list->last = data;
    } else {
        bool is_first = (current->value >= data->value);
        do {
            if (current->value >= data->value) {
                break;
            }
            current = current->next;
        } while (current != list->head);

        list_insert_into(list, current, data, is_first);
    }
    list->size++;
}
void list_insert(List list, unsigned index, Data data) {

    Data current = list->head;
    if(current == NULL) {
        data->previous = data->next = data;
        list->head = list->last = data;
    } else {
        bool is_first = index==0;
        do {
            if (index < 1) {
                break;
            }
            index--;
            current = current->next;
        } while (current != list->head);
        
        list_insert_into(list, current, data, is_first);
    }
    list->size++;
}
bool list_is_empty(List list) {
    return list->head == NULL;
}

Data list_pop(List list) {
    Data current = list->last;
    if(current != NULL) {
        current = list_remove_from(list, current, current==list->head);
    }
    return current;
}
Data list_pop_front(List list) {
	
    Data current = list->head;
    if(current != NULL) {
        if(current == list->last) {
            list->head = list->last = NULL;
        } else {
            list->last->next = list->head = current->next;
            list->head->previous = list->last;
        }
        current->previous = current->next = NULL;
        list->size--;
    }
    return current;
}
void list_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->head;
        do {
            data_print(data);
            data = data->next;
        } while(data != list->head );
    }
}
void list_reverse_print(List list) {
    if (list_is_empty(list)) {
        printf("empty list\n");
    } else {
        Data data = list->last;
        do {
            data_print(data);
            data = data->previous;
        } while(data != list->last );
    }
}
void list_push(List list, Data data) {

    if(list->last == NULL) {
    	data->previous = data->next = data;
        list->head = list->last = data;
    } else {
    	data->next = list->head;
        list->last->next = list->head->previous = data;
        data->previous = list->last;
        list->head = data;
    }
    list->size++;
}
Data list_remove(List list, unsigned index) {

    Data current = list->head;

    if (current != NULL) {
        index = (index < list->size) ? index : (list->size - 1);
        bool is_first = index==0;
        do {
            if ( index < 1 ) {
                break;
            }
            index--;
            current = current->next;
        } while (current != list->head);

        current = list_remove_from(list, current, is_first);
    }
    return current;
}

Data list_remove_value(List list, int value) {

    Data current = list->head;

    if (current != NULL) {
        bool is_first = current->value == value;

        do {
            if (current->value == value) {
                break;
            }
            current = current->next;
        } while (current != list->head);

        current = (current->value == value) ? list_remove_from(list, current, is_first) : NULL;
    }
    return current;
}
