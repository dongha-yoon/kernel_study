#define max_slot 64

struct radix_tree_Node{
    unsigned char shift;
    unsigned char offset;
    unsigned char count;
    struct radix_tree_Node* parent;
    struct radix_tree_Node* slot[max_slot];
    unsigned char item[max_slot];

};

struct radix_tree_Root
{
    int height;
    struct radix_tree_Node* rnode;
};

typedef struct radix_tree_Root  Root;
typedef struct radix_tree_Node  Node;

Root* init();
int instert(Root r,unsigned char index,unsigned char key);
int extend();
int erase();


