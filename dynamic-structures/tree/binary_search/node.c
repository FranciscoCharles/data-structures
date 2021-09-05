#include "node.h"

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

static int max_number(int a, int b) {
    return (a>b)?a:b;
}
bool node_is_empty(Node node) {
    return node == NULL;
}
Node node_create() {
    Node node = (Node)malloc(sizeof(struct Node));
    node->left = node->right = NULL;
    return node;
}
size_t node_count(Node node) {
    if(node_is_empty(node)) {
        return 0;
    }
    return 1 + node_count(node->left) + node_count(node->right);
}
Node node_delete(Node node) {
    if(!node_is_empty(node)) {
        node->left = node_delete(node->left);
        node->right = node_delete(node->right);
        free(node);
        node = NULL;
    }
    return node;
}
Node node_find(Node node, int number) {
    if(node_is_empty(node) || number == node->number) {
        return node;
    }
    node = (number > node->number) ? node->right : node->left;
    return node_find(node->left, number);
}
bool node_include(Node node, int number) {
    if(node_is_empty(node) || (node->number == number))
        return !node_is_empty(node);
    node = (number > node->number) ? node->right : node->left;
    return node_include(node, number);
}
Node node_insert(Node node, int number) {
    if(node_is_empty(node)) {
        node = node_create();
        node->number = number;
    } else if(number < node->number) {
        node->left = node_insert(node->left, number);
    } else {
        node->right = node_insert(node->right, number);
    }
    return node;
}
int node_height(Node node) {
    if(node_is_empty(node))
        return -1;
    return 1 + max_number(node_height(node->left), node_height(node->right));
}
void node_print(Node node) {
    if(!node_is_empty(node)) {
        node_print(node->left);
        printf(" %d ", node->number);
        node_print(node->right);
    }
}
Node node_remove(Node node, int number, Node* removed) {
    Node tmp = NULL;
    if(node_is_empty(node)) {
        *removed = NULL;
        return NULL;
    }
    if(node->number > number) {
        node->left = node_remove(node->left, number, removed);

    } else if(node->number < number) {
        node->right = node_remove(node->right, number, removed);

    } else if((node->left == NULL) && (node->right==NULL)) {
        *removed = node;
        node = NULL;

    } else if(node->right == NULL) {
        *removed = node;
        node = node->left;
        (*removed)->right = NULL;

    } else if(node->left == NULL) {
        *removed = node;
        node = node->right;
        (*removed)->right = NULL;

    } else {
        tmp = node->left;
        while(tmp->right != NULL) {
            tmp = tmp->right;
        }
        node->number = tmp->number;
        tmp->number = number;
        node->left = node_remove(node->left, number, removed);
    }

    return node;
}
