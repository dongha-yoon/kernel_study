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

int insert(Root* r,unsigned long index,unsigned long item){
    if(index>max_index(r))
        expand(r,index);
    
    Node* nptr = r->rnode;
    while(nptr->shift){
        int slot_ind = (index>>(nptr->shift))&(max_slot-1);
        // printf("index: %ld, ptr_ind: %d\n",index,slot_ind);
        Node* prev = nptr;
        nptr = nptr->slot[slot_ind].ptr;
        if(!nptr){//if the slot is not allocated
            nptr = (Node*)malloc(sizeof(Node));
            prev->slot[slot_ind].ptr = nptr;
            prev->count++;
            nptr->count=0;
            nptr->offset=slot_ind;
            nptr->parent=prev;
            nptr->shift =prev->shift-6;// 6 = log2(64)
            // printf("new slot(%d,%d) allocated\n",nptr->shift,nptr->offset);
        }
    }
    nptr->slot[index&(max_slot-1)].item = item;
    // printf("index: %ld, item_ind: %ld\n",index,index&(max_slot-1));
    nptr->count++;

    return 0;
}
int expand(Root* r,unsigned long index){
    // printf("expand\n");
    while(index>max_index(r)){
        // printf("loop ");
        Node* nroot         = (Node*)malloc(sizeof(Node));
        nroot->slot[0].ptr  = r->rnode;
        r->rnode->parent    = nroot;
        nroot->count        = 1;
        nroot->offset       = 0;
        nroot->shift        = r->rnode->shift + 6;
        
        r->rnode        = nroot;
        r->height++;
    }
    return 0;
}

int erase(Node* nptr){
    // printf("erase\n");
    if(!nptr)
        return 0;
    if(nptr->shift==0){
        // printf("(%2d,%2d)-deleted\n",nptr->shift,nptr->offset);
        free(nptr);
        return 0;
    }
        
    for(int i=0;i<max_slot;i++){
        erase(nptr->slot[i].ptr);
    }
    // printf("(%2d,%2d)-deleted\n",nptr->shift,nptr->offset);
    free(nptr);
    return 1;
}

unsigned long max_index(Root* r){
    int max = (max_slot<<(r->rnode->shift))-1;
    return max;
}

void visualize(Node* nptr,int rcount){
    if(!nptr)
        return;
    if(nptr->count==0){
        return;
    }
    printf("\n");
    for(int rc=0;rc<rcount;rc++)printf("    ");printf("└ ");
    printf("(%2d,%2d)",nptr->shift,nptr->offset);
    if(!(nptr->shift)){
        printf("    ");
        for(int i=0;i<max_slot;i++){
            long itm = nptr->slot[i].item;
            if(itm)
                printf("0x%lx ",itm);
        }
    }        
    else{
        for(int i=0;i<max_slot;i++){
            visualize(nptr->slot[i].ptr,rcount+1);
        }
    }
}