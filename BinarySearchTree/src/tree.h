#ifndef LAB5_TREE_H
#define LAB5_TREE_H

typedef struct tree {
    struct tree *parent, *left, *right;
    int value;
} node;

node *createNewTree();
node *clearTree(node *root);
node *getMinNode(node *root);
node *getMaxNode(node *root);
int getHeight(node *root);
node *addNode(node *tree, int value);
int checkPresence(node *root, int value);
node *findNode(node *root, int value);
node *removeNodeByValue(node *root, int value);
node *removeNode(node *root, node *target);
void display(node *root, int mode);
void printTree(node *root);

#endif //LAB5_TREE_H