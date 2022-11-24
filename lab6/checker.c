#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "utils.h"

int main() {
    BTNode *root = NULL;

    // Inserez in arbore
    root = insertNode(root, 10);
    insertNode(root, 5);
    insertNode(root, 15);
    insertNode(root, 12);
    insertNode(root, 18);
    insertNode(root, 3);
    insertNode(root, 7);
    insertNode(root, 4);
    insertNode(root, 6);
    insertNode(root, 8);
    insertNode(root, 17);
    insertNode(root, 20);

    prettyPrintTree(root);


    removeNode(&root,searchNode(root,5));

    prettyPrintTree(root);

    // printInOrder(root);

    // BTNode *nod= searchNode(root,12);
    
    // printf("%d\n", nod->data);

    // printf("Inaltimea arborelui: %ld\n", getHeight(root));
    // printf("E balansat?: %d\n", isBSTreeBalanced(root));

    // Eliberez memoria ocupata de arbore
    destroyTree(&root);

    return 0;
}