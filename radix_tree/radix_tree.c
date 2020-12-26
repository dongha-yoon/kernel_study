#include "radix_tree.h"

Root* init(){
    // printf("init\n");
    Root* Rptr = (Root*)malloc(sizeof(Root));
    Rptr->height = 0;

    Rptr->rnode = (Node*)malloc(sizeof(Node));
    Rptr->rnode->shift = 0;
    Rptr->rnode->offset = 0;
    Rptr->rnode->count = 0;
    Rptr->rnode->parent = NULL;

    return Rptr;
}

int insert(Root* r,unsigned long index,unsigned char item){
    if(index>max_index(r))
        expand(r,index);
    
    Node* ptr = r->rnode;
    // while(){
    //     ptr = ptr->slot[index>>(ptr->shift)&63]
    // }
}
int expand(Root* r,unsigned long index){
    // printf("expand\n");
    while(index>max_index(r)){
        // printf("loop ");
        Node* nroot     = (Node*)malloc(sizeof(Node));
        nroot->slot[0]  = r->rnode;
        r->rnode->parent= nroot;
        nroot->count    = 1;
        nroot->offset   = 0;
        nroot->shift    = r->rnode->shift + 6;
        
        r->rnode        = nroot;
        r->height++;
    }
    return 0;
}

int erase(Node* nptr){
    // printf("erase\n");
    if(!nptr)
        return 0;
    if(nptr->count==0){
        free(nptr);
        return 0;
    }
        
    for(int i=0;i<max_slot;i++)
        erase(nptr->slot[i]);
    return 1;
}

unsigned long max_index(Root* r){
    // printf("max_index\n");
    return max_slot<<(r->rnode->shift)-1;
}

void visualize(Node* nptr){
    if(!nptr)
        printf("### ");    
        return;
    
    for(int i=0;i<max_slot;i++){
        printf("%d ",nptr->offset);
        visualize(nptr->slot[i]);
    }

    if(nptr->shift==0){
        printf("%d ",nptr->offset);
    }
}