#include <stdlib.h>
#include <stdio.h>

#include "stack.h"
#include "queue.h"
#include "binary_tree.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define abs(a) \
   ({ __typeof__ (a) _a = (a); \
     _a > 0 ? _a : -_a; })

BTNode *initNode(int value) {
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));

    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

void destroyTree(BTNode **root) {
    if (*root == NULL) {
        return;
    }

    // Sterg subarborele stang
    destroyTree(&(*root)->left);

    // Sterg subarborele drept
    destroyTree(&(*root)->right);

    // Sterg nodul curent
    free(*root);

    *root = NULL;
}

int isLeaf(BTNode *node) {
    return (node->left == NULL
            && node->right == NULL);
}

int getNodeDegrees(BTNode *node) {
    return (node->left != NULL) + (node->right != NULL);
}

BTNode *insertNode(BTNode *root, int value) {
    // TODO Ex1
    if (root == NULL){
        root = initNode(value);
        return root;
    }
    else{
        if(value == root->data){
            return root;
        }else if(value < root->data){
            if(root->left == NULL){
                root->left = initNode(value);
                root->left->parent = root;
                return root->left;
            }else{
                insertNode(root->left,value);
            }
        }else if(value > root->data){
            if(root->right == NULL){
                root->right = initNode(value);
                root->right->parent = root;
                return root->right;
            }else{
                insertNode(root->right,value);
            }
        }
    }
    return NULL;
}

BTNode *searchNode(BTNode *root, int value) {
    // TODO Ex2
    if(root == NULL)
        return NULL;
    if(value == root->data){
        return root;
    }else if(value < root->data){
        if(root->left == NULL){
            return NULL;
        }else{
            return searchNode(root->left,value);
        }
    }else if(value > root->data){
        if(root->right == NULL){
            return NULL;
        }else{
            return searchNode(root->right,value);
        }
    }
    return NULL;
}

int removeNode(BTNode **root, BTNode *node) {
    // TODO Ex 3
    if(node->left == NULL && node->right == NULL){
        if(node->parent->data > node->data){
            node->parent->left = NULL;
            free(node);
        }else if(node->parent->data < node->data){
            node->parent->right = NULL;
            free(node);
        }
    }
    else if(node->left != NULL && node->right == NULL){
        if(node->parent->right->data == node->data)
            node->parent->right = node->left;
        else 
            node->parent->left= node->left;
        node->left->parent = node->parent;

        free(node);
    }else if(node->left == NULL && node->right != NULL){
        if(node->parent->right->data == node->data)
            node->parent->right = node->right;
        else 
            node->parent->left= node->right;
        node->right->parent = node->parent;

        free(node);
    }else{
        BTNode *nod=node;
        nod=searchNode(*root,node->data);
        printf("%d\n", nod->data);
        nod=nod->right;
        while(nod->left != NULL ){
            nod=nod->left;
        }
        node->data=nod->data;
        nod->parent->left=NULL;
        free(nod);
    }

    return 0;
}

void printInOrder(BTNode *root) {
    // TODO Ex4
    if(root == NULL)
        return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

void printPreOrder(BTNode *root) {
    printf("%d ", root->data);
    printInOrder(root->left);
    printInOrder(root->right);
    // TODO Ex4
}

void printPostOrder(BTNode *root) {
    printInOrder(root->left);
    printInOrder(root->right);
    printf("%d ", root->data);
    // TODO Ex4
}

size_t getHeight(BTNode *root) {
    // TODO Ex5
    if(root == NULL)
        return 0;
    else{
        int left_height, right_height;
        left_height = getHeight(root->left);
        right_height = getHeight(root->right);
        if(left_height <= right_height)
            return right_height+1;
        else
            return left_height+1;
    }
}

int isBSTreeBalanced(BTNode *root) {
    // TODO Ex6
    int left_height, right_height;
    if(root == NULL)
        return 1;
    left_height = getHeight(root->left);
    right_height = getHeight(root->right);
    if((left_height-right_height)<=1 && isBSTreeBalanced(root->left) && isBSTreeBalanced(root->right))
        return 1;
    return 0;
}


