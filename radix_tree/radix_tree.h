#define max_slot 64



struct radix_tree_Node{
    unsigned char shift;
    unsigned char offset;
    unsigned char count;
    struct radix_tree_Node* solt[max_slot]

};

struct radix_tree_Root
{
    int height;
    struct radix_tree_Node* rnode;
};

struct radix_tree_Root init(){

}

int instert(){

}

int extend(){

}

int erase(){

}
