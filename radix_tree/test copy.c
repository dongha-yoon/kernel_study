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
    printf("\n=======\n");

    int selection;
    do{
        printf("1. insert\n2. delete\n");
        scanf("%d",&selection);
        if(selection==1){
            int idx,item;
            scanf("%d %d",&idx,&item);
            insert(rtree,idx,item);
        }
        else if(selection==2){
            int idx;
            scanf("%d",&idx);
            delete(rtree,idx);
        }
        visualize(rtree->rnode,0);
    }while(selection == 0);
    

}
