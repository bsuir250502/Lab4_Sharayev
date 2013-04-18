#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

#define MAX_KEY_LENGTH 8
#define MAX_STRING_LENGTH 100
#define MAX_WORD_LENGTH 10

typedef struct ring {
    char string[MAX_STRING_LENGTH];
    struct ring *right;
    struct ring *left;
} ring_t;

typedef struct node {
    char key[MAX_KEY_LENGTH];
    ring_t *ring;
    struct node *left;
    struct node *right;
} node_t;

int display_tree(node_t *);
char read_argument(int, char **);
int attach_node(node_t * , char *);
int add_node(node_t * );
int attach_ring(ring_t *);
int attach_elem(ring_t **, char *);
int display_ring(ring_t *);

int main(int argc, char **argv)
{
    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }

    node_t *root;
    root = (node_t *)calloc(1, sizeof(*root));

    printf("Specify root key:\n");
    myfgets(root->key, MAX_KEY_LENGTH);
    while(add_node(root));
    display_tree(root); 

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
    display_ring(root->ring);
    display_tree(root->right);
    display_tree(root->left);

    return 0;
}

int add_node(node_t * root)
{
    char key[MAX_KEY_LENGTH];

    printf("Specify key (\"end\"to stop input):  ");
    myfgets(key, MAX_KEY_LENGTH);
    if (!strncmp(key, "end", 3)) {
        return 0;
    }
    attach_node(root, key);

    return 1;
}

int attach_node(node_t * root, char *key) 
{
    node_t *tmp;
    tmp = root;

        if (0 < strncmp(key, tmp->key, MAX_KEY_LENGTH)) {
            if (tmp->left) {
                tmp = tmp->left;
            } else {
                tmp->left= (node_t *)calloc(1,sizeof(*tmp->left));
                tmp = tmp->left;
            }
        } else {
            if (tmp->right) {
                tmp = tmp->right;
            } else {
                tmp->right = (node_t *)calloc(1,sizeof(*tmp->right));
                tmp = tmp->right;
            }
        }
    strncpy(tmp->key, key, MAX_KEY_LENGTH);
    attach_ring(tmp->ring);

    return 0;
}

int attach_ring(ring_t *ring)
{
    char buffer[MAX_STRING_LENGTH];
    ring = (ring_t *) calloc(1, sizeof(*ring));
    while(1) {
        printf("Enter string(end, to stop reading):\n");
        myfgets(buffer, MAX_STRING_LENGTH);
        if(!strncmp(buffer, "end", 3)){
            return 0;
        }
        attach_elem(&ring, buffer);

    }

    return 0;
}

int attach_elem(ring_t **ring, char *string) 
{
    ring_t *new_elem;
    new_elem = (ring_t *) calloc(1, sizeof(*new_elem));
    strncpy(new_elem->string, string, MAX_STRING_LENGTH);

    if(!*ring)
    {
        (*ring) = new_elem;
        (*ring)->right = (*ring);
        (*ring)->left = (*ring);
    }
    else {
        new_elem = (*ring)->right->left;
        (*ring)->right->left = new_elem->right;
        (*ring)->right = new_elem->left;
        (*ring)->right = new_elem->left;
    }

    return 0;
}

int display_ring(ring_t *ring) 
{
    ring_t *tmp;
    if(!ring){
        return 0;
    }
    tmp = ring;

    do {
        printf("%s\n", tmp->string);
        tmp = tmp->left;
    }
    while(tmp != ring);

    return 0;
}