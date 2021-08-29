#ifndef _BSTREE_H_
#define _BSTREE_H_

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

typedef struct Tree* Tree;

struct Tree{
    int number;
    Tree left;
    Tree right;
};

Tree tree_init();
bool tree_is_empty(Tree tree);
size_t tree_count(Tree tree);
Tree tree_create();
Tree tree_delete(Tree tree);
Tree tree_find(Tree tree, int number);
Tree tree_insert(Tree tree, int number);
bool tree_include(Tree tree, int number);
int tree_height(Tree tree);
void tree_print(Tree tree);
Tree tree_remove(Tree tree, int number);

#endif