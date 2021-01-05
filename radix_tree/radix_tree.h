#define max_slot 64
#include <stdlib.h>
#include <stdio.h>

union contents{
    struct radix_tree_Node* ptr;
    unsigned long item;
};

struct radix_tree_Node{
    unsigned char shift;
    unsigned char offset;
    unsigned char count;
    struct radix_tree_Node* parent;
    union contents slot[max_slot];
};

struct radix_tree_Root
{
    int height;
    struct radix_tree_Node* rnode;
};

typedef struct radix_tree_Root  Root;
typedef struct radix_tree_Node  Node;

Root* init();
int insert(Root*,unsigned long,unsigned long);
int expand(Root*,unsigned long);
int erase(Node*);
unsigned long max_index(Root*);
void visualize(Node*,int);
