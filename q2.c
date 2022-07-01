#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *previous;
    struct node *next;
};

struct list {
    int size;
    struct node *head;
    struct node *tail;
    struct node *left;
    struct node *right;
};


void printList(struct list *toprint) {
    struct node *cur = toprint->head;
    if (cur != NULL) {
        while (cur->previous != NULL) {
            cur = cur->previous;
        }
        printf("[");
        while (cur->next != NULL) {
            printf("%d, ", cur->value);
            cur = cur->next;
        }
        printf("%d]\n", cur->value);
    }
    else {
        printf("[0, 0]\n");
    }
}


void push(int topush, struct list *plist) {
    struct node *head = malloc(sizeof(struct node));
    struct node *n = malloc(sizeof(struct node));
    struct list *inst = plist;
    int even;
    
    head = inst->head;
    n->value = topush;

    while (head->previous->value != 0) {
        head = head->previous;
    }
    if (n->value % 2 == 0) {                                
        even = 1;
        while (head->value == -1) {
            head = head->next;
        }
        n->next = head;
        head = head->previous;                              
        n->previous = head;
        head->next = n;                     
    } else {
        even = 0;
        while (head->value == -1) { 
            head = head->previous;
        }   
        n->previous = head;                                 
        head = head->next;                                  
        n->next = head;                                     
        head->previous = n; 
        head = head->previous;  
    }
    
    inst->head = head;
    inst->size++;
    *plist = *inst;

    if (even == 1) {
        plist->right = n;
    } else {
        plist->left = n;
    }
}


void pull(struct node *topull, struct list *plist) {
    struct node *a = topull->previous;
    struct node *b = topull->next;
    a->next = b; b->previous = a;
    free(topull);
    plist->head = b;
}


void freeList(struct list *tofree) {
    struct node *head = tofree->head;
    struct node *iter = malloc(sizeof(struct node));
    while (head != NULL) {
        iter = head; head = head->next;
        free(iter);
    }
    tofree->head = iter;
}


int main() {
    struct node *head = NULL;
    struct list *myList = malloc(sizeof(struct list));
    
    myList->head = NULL;
    myList->tail = NULL;
    myList->size = 0;
    
    printList(myList);
    
    for (int a = 0; a < 7; a++) {
        struct node *this = malloc(sizeof(struct node));

        if (a == 0 || a == 6) {
            this->value = 0;
        } else {
            this->value = -1;
        }
        
        if (a > 0) {
            this->previous = head;          
            head->next = this;              
        } else {
            this->previous = NULL;
        }
        
        this->next = NULL;
        head = this;                        
        myList->head = head;
        myList->size++;
    }
    
    printList(myList);
    push(12, myList);
    push(34, myList);
    push(23, myList);
    printList(myList);
    
    freeList(myList);
    
    return 0;
}