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
    ring_t **ring;
    struct node *left;
    struct node *right;
} node_t;

char read_argument(int, char **);
int create_node(node_t * );
int attach_node(node_t * , char *);
int create_ring(ring_t **);
int attach_elem(ring_t **, char *);
int walk_through_the_tree(node_t *, char *);
int walk_through_the_ring(ring_t *, char *);
int find_word(char *, char *);
int input_and_check_word(node_t *);

// Temp functions
int display_tree(node_t *);
int display_ring(ring_t *);
//

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
    create_ring(root->ring);
    while(create_node(root));
    display_tree(root);
    //walk_through_the_tree(root);

    while(input_and_check_word(root));

    return 0;
}

int input_and_check_word(node_t *root)
{
    int counter;
    char buffer[MAX_WORD_LENGTH];

    printf("\nSpecyfy requied word to start search(end, to exit)\n");
    while(1) {
        myfgets(buffer, MAX_WORD_LENGTH);
        if(!(strncmp(buffer, "end", 3)) ){
            return 0;
        }
        else if(strlen(buffer) ){
            break;
        }
        printf("You don't have typed anything\n");
    }

    counter = walk_through_the_tree(root, buffer);
    printf("The word occurs %d times", counter);

    return 1; 
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

int walk_through_the_tree(node_t * root, char *word)
{
    if (!root) {
        return 0;
    }
    static int counter;
    //printf("(%s)", root->key);
    counter += walk_through_the_ring(*(root->ring), word);  
    
    
    
    walk_through_the_tree(root->right, word);
    walk_through_the_tree(root->left, word);

    return counter;
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
    while(1) {
        if (0 < strncmp(key, tmp->key, MAX_KEY_LENGTH)) {
            if (tmp->left) {
                tmp = tmp->left;
            } else {
                tmp->left= (node_t *)calloc(1,sizeof(*tmp->left));
                tmp = tmp->left;
                break;
            }
        } else if (tmp->right) {
                tmp = tmp->right;
            } else {
                tmp->right = (node_t *)calloc(1,sizeof(*tmp->right));
                tmp = tmp->right;
                break;
            }
    }
    strncpy(tmp->key, key, MAX_KEY_LENGTH);
    create_ring(tmp->ring);

    return 0;
}

int create_ring(ring_t **ring)
{
    char buffer[MAX_STRING_LENGTH];
    ring = (ring_t **) calloc(1, sizeof(*ring));
    while(1) {
        printf("Enter string(end, to stop reading):\n");
        myfgets(buffer, MAX_STRING_LENGTH);
        if(!strncmp(buffer, "end", 3)){
            return 0;
        }
        attach_elem(ring, buffer);

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

int walk_through_the_ring(ring_t *ring, char *word) 
{
    if(!ring){
        return 0;
    }

    int counter;
    ring_t *tmp;
    tmp = ring;

    do {
        if((counter = find_word(tmp->string, word)) != 0) {
            printf("%s\n", tmp->string);
        }   
        tmp = tmp->left;
    }
    while(tmp != ring);

    return counter;
}

int find_word(char *str, char *word) 
{
    int counter = 0;
    char *p;
    p = str;
    while(p){
        p = strstr(p, word);
        if(p) {
            counter++;
        }
    }

    return counter;
}

// Temp functions
int display_tree(node_t * root)
{
    if (!root) {
        return 0;
    }
    printf("(%s)", root->key);
    display_ring(*(root->ring));
    
    
    display_tree(root->right);
    display_tree(root->left);

    return 0;
}

int display_ring(ring_t *ring) 
{
    if(!ring){
        return 0;
    }
    ring_t *tmp;
    tmp = ring;
    puts("The contents of the ring:");
    do {
        printf("%s\n", tmp->string);    
        tmp = tmp->left;
    }
    while(tmp != ring);

    return 0;
}
