#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

#define MAX_KEY_LENGTH 8
#define MAX_STRING_LENGTH 100
#define MAX_WORD_LENGTH 10

typedef struct ring {
    char string[MAX_STRING_LENGTH];
    struct ring *next;
} ring_t;

typedef struct node {
    char key[MAX_KEY_LENGTH];
    ring_t *ring;
    struct node *left;
    struct node *right;
} node_t;

char read_argument(int, char **);
int create_node(node_t *);
int attach_node(node_t *, char *);
int create_ring(ring_t **);
int attach_elem(ring_t **, char *);
int walk_through_the_tree(node_t *, char *);
int walk_through_the_ring(ring_t *, char *);
int find_word(char *, char *);
int input_and_check_word(node_t *);

int main(int argc, char **argv)
{
    node_t *root;
    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }
    root = (node_t *) calloc(1, sizeof(*root));
    printf("Specify root key:  ");
    myfgets(root->key, MAX_KEY_LENGTH);
    create_ring(&(root->ring));
    while (create_node(root));
    while (input_and_check_word(root));

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

int create_node(node_t * root)
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
    while (1) {
        if (0 < strncmp(key, tmp->key, MAX_KEY_LENGTH)) {
            if (tmp->left) {
                tmp = tmp->left;
            } else {
                tmp->left = (node_t *) calloc(1, sizeof(*tmp->left));
                tmp = tmp->left;
                break;
            }
        } else if (tmp->right) {
            tmp = tmp->right;
        } else {
            tmp->right = (node_t *) calloc(1, sizeof(*tmp->right));
            tmp = tmp->right;
            break;
        }
    }
    strncpy(tmp->key, key, MAX_KEY_LENGTH);
    create_ring(&(tmp->ring));

    return 0;
}

int create_ring(ring_t ** ring)
{
    char buffer[MAX_STRING_LENGTH];
    printf("Enter strings(end, to stop reading):\n");
    while (1) {
        printf("    ");
        myfgets(buffer, MAX_STRING_LENGTH);
        if (!strncmp(buffer, "end", 3)) {
            return 0;
        }
        attach_elem(ring, buffer);

    }

    return 0;
}

int attach_elem(ring_t ** ring, char *string)
{
    ring_t *new_elem;

    new_elem = (ring_t *) calloc(1, sizeof(*new_elem));
    strncpy(new_elem->string, string, MAX_STRING_LENGTH);

    if (!*ring) {
        *ring = new_elem;
        (*ring)->next = *ring;
    } else {
        new_elem->next = (*ring)->next;
        (*ring)->next = new_elem;
    }

    return 0;
}

int walk_through_the_ring(ring_t * ring, char *word)
{
    int counter = 0, buffer;
    ring_t *tmp;

    if (!ring) {
        return 0;
    }
    tmp = ring;

    do {
        if ((buffer = find_word(tmp->string, word)) != 0) {
            printf("%s\n", tmp->string);
            counter += buffer;
        }
        tmp = tmp->next;
    }
    while (tmp != ring);

    return counter;
}

int walk_through_the_tree(node_t * root, char *word)
{
    int counter = 0;
    if (!root) {
        return 0;
    }
    counter += walk_through_the_ring(root->ring, word);

    counter += walk_through_the_tree(root->right, word);
    counter += walk_through_the_tree(root->left, word);

    return counter;
}

int find_word(char *str, char *word)
{
    int counter = 0;
    char *p;
    p = str;
    while (p) {
        p = strstr(p, word);
        if (p) {
            counter++;
        } else {
            break;
        }
        while (*p != ' ' && *p)
            p++;
    }

    return counter;
}

int input_and_check_word(node_t * root)
{
    int counter = 0;
    char buffer[MAX_WORD_LENGTH];

    printf("\n==================================================\n");
    printf("Specyfy requied word to start search(end, to exit)\n");
    printf("==================================================\n");
    myfgets(buffer, MAX_WORD_LENGTH);
    if (!(strncmp(buffer, "end", 3))) {
        return 0;
    }
    else if(!(strlen(buffer)) ) {
       printf("You don't have typed anything, try again\n");
       return 1;
    }

    printf("The word occurs at:\n");
    counter = walk_through_the_tree(root, buffer);
    printf("\n%d times\n", counter);

    return 1;
}
