// Binary Search Tree
// Functions: add, remove, find, min, max, height, print, clear

#include "tree.h"
#include <stdio.h>
#include <string.h>

int main() {
    node *tree = createNewTree();
    display(tree, 1); // print tree and commands list

    char command[20];
    int fl; // 0 = right command, 1 = wrong command
    while (1) { // main program loop
        scanf(" %s", command);
        fl = 1;

        if (strcmp(command, "exit") == 0) break;

        if (strcmp(command, "add") == 0) {
            int intValue;
            int sum = scanf(" %d", &intValue);
            if (sum == 1) {
                fl = 0;
                tree = addNode(tree, (int) intValue);
                if (tree == NULL) {
                    printf("Memory error");
                    break;
                }
                display(tree, 1); // print tree and commands list
            }
        }

        if (strcmp(command, "remove") == 0) {
            int intValue;
            int sum = scanf(" %d", &intValue);
            if (sum == 1) {
                fl = 0;
                if (checkPresence(tree, (int) intValue) == 0)
                    printf("Not found\n");
                else {
                    tree = removeNodeByValue(tree, (int) intValue);
                    display(tree, 1); // print tree and commands list
                }
            }
        }

        if (strcmp(command, "find") == 0) {
            int intValue;
            int sum = scanf(" %d", &intValue);
            if (sum == 1) {
                fl = 0;
                if (checkPresence(tree, (int) intValue) == 0)
                    printf("Not found\n");
                else
                    printf("Found\n");
            }
        }

        if (strcmp(command, "min") == 0) {
            fl = 0;
            node *result = getMinNode(tree);
            if (result == NULL)
                printf("Tree is empty\n");
            else
                printf("%d\n", result->value);
        }

        if (strcmp(command, "max") == 0) {
            fl = 0;
            node *result = getMaxNode(tree);
            if (result == NULL)
                printf("Tree is empty\n");
            else
                printf("%d\n", result->value);
        }

        if (strcmp(command, "height") == 0) {
            fl = 0;
            printf("%d\n", getHeight(tree));
        }

        if (strcmp(command, "clear") == 0) {
            fl = 0;
            tree = clearTree(tree);
            display(tree, 1); // print tree and commands list
        }

        if (strcmp(command, "print") == 0) {
            fl = 0;
            display(tree, 0); // print tree
        }

        fgets(command, __INT32_MAX__, stdin); // read to the EOF
        if (fl) printf("Wrong command\n");
    }

    return 0;
}