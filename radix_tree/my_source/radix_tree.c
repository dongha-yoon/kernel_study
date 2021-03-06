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

int insert(Root* r,unsigned long index,Item_t item){
    while(index>max_index(r))
        extend(r);
    
    Node* nptr = r->rnode;
    while(nptr->shift){
        int slot_ind = (index>>(nptr->shift))&(max_slot-1);
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
        }
    }
    if(nptr->slot[index&(max_slot-1)].item){//if the item is not null
        printf("Index %ld is already inserted.\n",index);
        return -1;
    }
    Item_t* iptr = nptr->slot[index&(max_slot-1)].item = (Item_t*)malloc(sizeof(Item_t));
    *(iptr)=item;
    nptr->count++;
    return 1;
}
int extend(Root* r){
    Node* nroot         = (Node*)malloc(sizeof(Node));
    nroot->slot[0].ptr  = r->rnode;
    r->rnode->parent    = nroot;
    nroot->count        = 1;
    nroot->offset       = 0;
    nroot->shift        = r->rnode->shift + 6;
    
    r->rnode        = nroot;
    r->height++;
    return 0;
}

int delete(Root *r,unsigned long index){
    Node* nptr = r->rnode;
    while(nptr->shift){
        int slot_ind = (index>>(nptr->shift))&(max_slot-1);
        Node* prev = nptr;
        nptr = nptr->slot[slot_ind].ptr;
        if(!nptr){
            printf("Index %ld is not exist.\n",index);
            return -1;
        }
    }
    if(nptr->slot[index&(max_slot-1)].item==NULL){
        printf("Index %ld is not exist.\n",index);
        return -1;
    }
    free(nptr->slot[index&(max_slot-1)].item);
    nptr->slot[index&(max_slot-1)].item = NULL;
    nptr->count--;

    while(nptr->count==0){
        Node* pptr = nptr->parent;
        pptr->slot[nptr->offset].ptr = NULL;
        pptr->count--;
        free(nptr);
        nptr = pptr;
    }
    shrink(r);
}

int shrink(Root *r){
    while(r->height!=0 && r->rnode->count<=1){
        Node* old_root = r->rnode;
        Node* new_root = r->rnode->slot[0].ptr;
        free(old_root);
        r->rnode = new_root;
        r->height--;
    }
    return 0;
}

int erase(Node* nptr){
    // printf("erase\n");
    if(!nptr)
        return 0;
    if(nptr->shift==0){
        for(int i=0;i<max_slot;i++){
            Item_t* iptr = nptr->slot[i].item;
            if(iptr){
                free(iptr);
                iptr=NULL;
            }       
        }
    }
    else{
        for(int i=0;i<max_slot;i++){
            erase(nptr->slot[i].ptr);
        }    
    }
    // printf("(%2d,%2d)-deleted\n",nptr->shift,nptr->offset);
    free(nptr);
    nptr = NULL;
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
    if(nptr->shift==0){
        printf("    ");
        for(int i=0;i<max_slot;i++){
            Item_t* iptr = nptr->slot[i].item;
            if(iptr)
                printf("[%2d: 0x%10lx]",i,*iptr);
        }
    }        
    else{
        for(int i=0;i<max_slot;i++){
            visualize(nptr->slot[i].ptr,rcount+1);
        }
    }
}