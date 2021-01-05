#include "radix_tree.h"


int main(){
    Root* rtree = init();

    int n_input;
    scanf("%d",&n_input);

    unsigned long index,item;
    for(int i=0;i<n_input;i++){
        scanf("%ld %ld",&index,&item);
        insert(rtree,index,item);
    }

    visualize(rtree->rnode,0);
    printf("\n");
    erase(rtree->rnode);
    // printf("=====\n");
    // insert(rtree,3000,22);
    // visualize(rtree->rnode,0);
}