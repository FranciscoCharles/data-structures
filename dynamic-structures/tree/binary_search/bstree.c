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

static int max_number(int a, int b) {
    return (a>b)?a:b;
}
Tree tree_init() {
    return NULL;
}
bool tree_is_empty(Tree tree) {
    return tree == NULL;
}
Tree tree_create() {
    Tree tree = (Tree)malloc(sizeof(struct Tree));
    tree->left = tree->right = NULL;
    return tree;
}
size_t tree_count(Tree tree){
	if(tree_is_empty(tree)){
		return 0;
	}
	return 1 + tree_count(tree->left) + tree_count(tree->right);
}
Tree tree_delete(Tree tree) {
    if(!tree_is_empty(tree)) {
        tree_delete(tree->left);
        tree_delete(tree->right);
        free(tree);
        tree = NULL;
    }
    return tree;
}
Tree tree_find(Tree tree, int number) {
    if(tree_is_empty(tree) || number == tree->number) {
        return tree;
    }
    if(number > tree->number) {
        return tree_find(tree->right, number);
    }
    return tree_find(tree->left, number);

}
bool tree_include(Tree tree, int number) {
    if(tree_is_empty(tree))
        return false;
    return (tree->number == number)
           || tree_include(tree->left, number)
           || tree_include(tree->right, number);
}
Tree tree_insert(Tree tree, int number) {
    if(tree_is_empty(tree)) {
        tree = tree_create();
        tree->number = number;
    } else if(number < tree->number) {
        tree->left = tree_insert(tree->left, number);
    } else {
        tree->right = tree_insert(tree->right, number);
    }
    return tree;
}
int tree_height(Tree tree) {
    if(tree_is_empty(tree))
        return -1;
    return 1 + max_number(tree_height(tree->left), tree_height(tree->right));
}
void tree_print(Tree tree) {
    if(!tree_is_empty(tree)) {
        tree_print(tree->left);
        printf(" %d ",tree->number);
        tree_print(tree->right);
    }
}
Tree tree_remove(Tree tree, int number) {
    Tree tmp = NULL;
    if(tree_is_empty(tree)) {
        return NULL;
    }
    if(tree->number > number) {
        tree->left = tree_remove(tree->left, number);

    } else if(tree->number < number) {
        tree->right = tree_remove(tree->right, number);

    } else if((tree->left == NULL) && (tree->right==NULL)) {
        free(tree);
        tree=NULL;

    } else if(tree->right == NULL) {
        tmp = tree;
        tree = tree->left;
        free(tmp);

    } else if(tree->left == NULL) {
        tmp = tree;
        tree = tree->right;
        free(tmp);

    } else {
        tmp = tree->left;
        while(tmp->right != NULL) {
            tmp = tmp->right;
        }
        tree->number = tmp->number;
        tmp->number = number;
        tree->left = tree_remove(tree->left, number);
    }

    return tree;
}
