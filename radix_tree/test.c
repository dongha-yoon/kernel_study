#include "radix_tree.h"


int main(){
    Root* rtree = init();
    expand(rtree,300000);
    printf("root: %d\n",rtree->height);
    printf("rnode: %d\n",rtree->rnode->count);
    visualize(rtree->rnode);
    erase(rtree->rnode);
}