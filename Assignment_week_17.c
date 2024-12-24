#include <stdio.h>
#include <stdlib.h>  

typedef struct AvlNode {
    int elem;
    struct AvlNode* left;
    struct AvlNode* right;
    int height;
} AvlNode;

int height(AvlNode* t) {
    return t == NULL ? -1 : t->height;
}

void rotateWithLeftChild(AvlNode** k2) {
    AvlNode* k1 = (*k2)->left;
    (*k2)->left = k1->right;
    k1->right = *k2;
    (*k2)->height = max(height((*k2)->left), height((*k2)->right)) + 1;
    k1->height = max(height(k1->left), (*k2)->height) + 1;
    *k2 = k1;
}

void rotateWithRightChild(AvlNode** k2) {
    AvlNode* k1 = (*k2)->right;
    (*k2)->right = k1->left;
    k1->left = *k2;
    (*k2)->height = max(height((*k2)->left), height((*k2)->right)) + 1;
    k1->height = max(height(k1->right), (*k2)->height) + 1;
    *k2 = k1;
}

void doubleWithLeftChild(AvlNode** k3) {
    rotateWithRightChild(&(*k3)->left);
    rotateWithLeftChild(k3);
}

void doubleWithRightChild(AvlNode** k3) {
    rotateWithLeftChild(&(*k3)->right);
    rotateWithRightChild(k3);
}

void balance(AvlNode** t) {
    if (*t == NULL) return;
    if (height((*t)->left) - height((*t)->right) > 1) {
        if (height((*t)->left->left) >= height((*t)->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if (height((*t)->right) - height((*t)->left) > 1) {
        if (height((*t)->right->right) >= height((*t)->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }
    (*t)->height = max(height((*t)->left), height((*t)->right)) + 1;
}

AvlNode* createNode(int x) {
    AvlNode* node = (AvlNode*)malloc(sizeof(AvlNode));
    node->elem = x;
    node->left = node->right = NULL;
    node->height = 0;
    return node;
}

void insert(int x, AvlNode** t) {
    if (*t == NULL) {
        *t = createNode(x);
    }
    else if (x < (*t)->elem) {
        insert(x, &(*t)->left);
    }
    else if (x > (*t)->elem) {
        insert(x, &(*t)->right);
    }
    balance(t);
}

void printInOrder(AvlNode* t) {
    if (t != NULL) {
        printInOrder(t->left);
        printf("%d ", t->elem);
        printInOrder(t->right);
    }
}

void freeTree(AvlNode* t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
}

int main() {
    AvlNode* root = NULL;
    int inputArray[] = { 20, 10, 30, 5, 15, 25, 35 };
    int n = sizeof(inputArray) / sizeof(inputArray[0]);
    printf("Qua trinh them phan tu va in cay AVL:\n");
    for (int i = 0; i < n; i++) {
        printf("\nThem %d:\n", inputArray[i]);
        insert(inputArray[i], &root);
        printInOrder(root);
        printf("\n");
    }
    freeTree(root);
    return 0;
}
