#include"bstree.h"

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

bool tree_is_empty(Tree tree) {
    return tree == NULL;
}
Tree tree_create() {
    Tree tree = (Tree)malloc(sizeof(struct Tree));
    tree->root = NULL;
    return tree;
}
size_t tree_count(Tree tree) {
    if(tree_is_empty(tree)) {
        return 0;
    }
    return node_count(tree->root);
}
Tree tree_delete(Tree tree) {
    if(!tree_is_empty(tree)) {
        tree->root = node_delete(tree->root);
        free(tree);
        tree = NULL;
    }
    return tree;
}
Node tree_find(Tree tree, int number) {
    if(tree_is_empty(tree)) {
        return NULL;
    }
    return node_find(tree->root, number);;
}
bool tree_include(Tree tree, int number) {
    return !tree_is_empty(tree) && node_include(tree->root, number);
}
bool tree_insert(Tree tree, int number) {
    if(!tree_is_empty(tree)) {
        tree->root = node_insert(tree->root, number);
        return true;
    }
    return false;
}
int tree_height(Tree tree) {
    if(tree_is_empty(tree)) {
        return -1;
    }
    return node_height(tree->root);
}
void tree_print(Tree tree) {
    if(tree_is_empty(tree)) {
        printf("empty tree!\n");
    } else {
        node_print(tree->root);
        printf("\n");
    }
}
Node tree_remove(Tree tree, int number) {
	Node node = NULL;
    if(!tree_is_empty(tree)) {
        tree->root = node_remove(tree->root, number, &node);
    }
    return node;
}
