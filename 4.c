#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

#define MAX_KEY_LENGTH 8


typedef struct node {
    char key[MAX_KEY_LENGTH];
    int data;
    struct node *left;
    struct node *right;
} node_t;

int display_tree(node_t *);
char read_argument(int, char **);
int attach_node(node_t * , char *, int );
int add_node(node_t * );

int main(int argc, char **argv)
{
    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }

    node_t root;
    root.data = 5;
    printf("Specify root key:\n");
    myfgets(root.key, MAX_KEY_LENGTH);
    while(add_node(&root));
    display_tree(&root); 

    return 0;
}

char read_argument(int argc, char **argv)
{
    if (argc == 2) {
        if (!(strcmp(argv[1], "-h"))) {
            return 'h';
        }
    }

    return '0';
}

int display_tree(node_t * root)
{
    if (!root) {
        return 0;
    }
    printf("(%d)", root->data);
    display_tree(root->right);
    display_tree(root->left);

    return 0;
}

int add_node(node_t * root)
{
    int data;
    char key[MAX_KEY_LENGTH];

    printf("Specify key (\"end\"to stop input):  ");
    myfgets(key, MAX_KEY_LENGTH);
    if (!strncmp(key, "end", 3)) {
        return 0;
    }
    printf("Specify data:  ");
    data = input_number_in_range(0, 1000);
    attach_node(root, key, data);

    return 0;
}

int attach_node(node_t * root, char *key, int data) 
{
    node_t *tmp;
    tmp = root;

        if (0 < strncmp(key, tmp->key, MAX_KEY_LENGTH)) {
            if (tmp->left) {
                tmp = tmp->left;
            } else {
                tmp->left = (node_t *)malloc(sizeof(*tmp->left));
                tmp = tmp->left;
                /*break;*/
            }
        } else {
            if (tmp->right) {
                tmp = tmp->right;
            } else {
                tmp->right = (node_t *)malloc(sizeof(*tmp->right));
                tmp = tmp->right;
                 /*break;*/
            }
        }
    strncpy(tmp->key, key, MAX_KEY_LENGTH);
    tmp->data = data;

    return 0;
}
