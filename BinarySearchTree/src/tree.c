#include "tree.h"
#include "DblLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

node *createNewTree() { return NULL; }

node *clearTree(node *root) {
    if (root == NULL) return NULL; // tree is empty

    DblLinkedList *linkedList = createDblLinkedList();
    pushBack(linkedList, root);

    while (linkedList->size != 0) {
        node *tmp = (node*) popFront(linkedList);
        if (tmp->left) pushBack(linkedList, tmp->left);
        if (tmp->right) pushBack(linkedList, tmp->right);
        free(tmp); // destroy node
    }

    deleteDblLinkedList(&linkedList);

    root = NULL;
    return root;
}

node *getMinNode(node *root) {
    if (root == NULL) return NULL; // tree is empty

    while (root->left)
        root = root->left;
    return root;
}

node *getMaxNode(node *root) {
    if (root == NULL) return NULL; // tree is empty

    while (root->right)
        root = root->right;
    return root;
}

int getHeight(node *root) {
    if (root == NULL) return 0;

    int left, right;
    if (root->left != NULL)
        left = getHeight(root->left);
    else
        left = 0;

    if (root->right != NULL)
        right = getHeight(root->right);
    else
        right = 0;

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

node *addNode(node *root, int value) {
    node *newNode = calloc(1, sizeof(node));
    if (newNode == NULL) return NULL;

    newNode->value = value;

    if (root == NULL) {
        // new node is root
        newNode->parent = newNode->left = newNode->right = NULL;
        root = newNode;
    } else {
        node *previous = NULL;
        node *current = root;

        while (current != NULL) {
            previous = current;
            if (value < current->value)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = previous;
        newNode->left = newNode->right = NULL;

        if (value < previous->value)
            previous->left = newNode;
        else
            previous->right = newNode;
    }

    return root;
}

// 0 = false (not found), 1 = true (found)
int checkPresence(node *root, int value) {
    node *result = findNode(root, value);
    if (result == NULL)
        return 0;
    else
        return 1;
}

node *findNode(node *root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return findNode(root->left, value);
    else
        return findNode(root->right, value);
}

node *removeNodeByValue(node *root, int value) {
    node *delete = findNode(root, value);
    if (delete == NULL) return root;

    return removeNode(root, delete);
}

node *removeNode(node *root, node *target) {
    node *tmp;

    // there are no branches
    if ((target->left == NULL) && (target->right == NULL)) {
        if (target->parent == NULL) { // target is root
            root = createNewTree();
        } else {
            tmp = target->parent;
            if (target == tmp->right)
                tmp->right = NULL;
            else
                 tmp->left = NULL;
        }

        free(target);

        return root;
    }

    // there is only right branch
    if ((target->left == NULL) && (target->right != NULL)) {
        if (target->parent == NULL) { // target is root
            tmp = target->right;
            target->value = tmp->value;
            if (tmp->left != NULL) {
                target->left = tmp->left;
                tmp->left->parent = target;
            }
            else
                target->left = NULL;

            if (tmp->right != NULL) {
                target->right = tmp->right;
                tmp->right->parent = target;
            }
            else
                target->right = NULL;

            free(tmp);
        } else {
            tmp = target->parent;
            if (target == tmp->right)
                tmp->right = target->right;
            else
                tmp->left = target->right;

            target->right->parent = tmp;

            free(target);
        }

        return root;
    }

    // there is only left branch
    if ((target->left != NULL) && (target->right == NULL)) {
        if (target->parent == NULL) { // target is root
            tmp = target->left;
            target->value = tmp->value;
            if (tmp->left != NULL) {
                target->left = tmp->left;
                tmp->left->parent = target;
            }
            else
                target->left = NULL;

            if (tmp->right != NULL) {
                target->right = tmp->right;
                tmp->right->parent = target;
            }
            else
                target->right = NULL;

            free(tmp);
        } else {
            tmp = target->parent;
            if (target == tmp->right)
                tmp->right = target->left;
            else
                tmp->left = target->left;

            target->left->parent = tmp;

            free(target);
        }

        return root;
    }

    // there are both branches
    if ((target->left != NULL) && (target->right != NULL)) {
        tmp = getMaxNode(target->left);
        target->value = tmp->value;
        removeNode(root, tmp);
    }

    return root;
}

// mode = 0 : print tree
// mode = 1 : print tree + commands list
void display(node *root, int mode) {
    printf("\n");
    printTree(root);

    if (mode) {
        printf("\nCOMMANDS LIST:\n");
        printf("\tadd/remove/find <int value>\n");
        printf("\tmin/max/height\n");
        printf("\tprint/clear\n");
        printf("\texit\n");
    }
}

void printTree(node *root) {
    if (root == NULL) {
        printf("<Empty tree>\n");
        return;
    }

    DblLinkedList *linkedList = createDblLinkedList();
    pushBack(linkedList, root);

    while (linkedList->size != 0) {
        node *tmp = (node*) popFront(linkedList);

        printf("ROOT: ");
        printf("%d", tmp->value);
        printf(", ");

        printf("LEFT: ");
        if (tmp->left)
            printf("%d", tmp->left->value);
        else
            printf("null");
        printf(", ");

        printf("RIGHT: ");
        if (tmp->right)
            printf("%d", tmp->right->value);
        else
            printf("null");
        printf(";\n");

        if (tmp->left) pushBack(linkedList, tmp->left);
        if (tmp->right) pushBack(linkedList, tmp->right);
    }

    deleteDblLinkedList(&linkedList);
}