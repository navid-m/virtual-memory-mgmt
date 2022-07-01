#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

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


int getRandom() {
    int x;
    srand(time(NULL));
    while (1) {
        x = rand() % 16; 
        if (x != 0) {
            break;
        }
    }
    return x;
}


void push(int topush, struct list *plist) {
    struct node *head = malloc(sizeof(struct node));
    struct node *n = malloc(sizeof(struct node));
    struct list *inst = plist;
    
    head = inst->head;
    printf("%d\n", head->value);
    n->value = topush;
    if (n->value % 2 == 0) {                
        while (head->value == -1) {         
            head = head->next;
        }
        n->next = head;
        head = head->previous;
        n->previous = head;
        head->next = n;
    } else {                                    
        while (head->value == -1) { 
            head = head->previous;                      
        }
        n->next = head; 
        head = head->previous;                              
        n->previous = head;
        head->next = n;
    }
    
    inst->head = head;
    *plist = *inst;
}


void pull(struct node *topull, struct list *plist) {
    struct node *a = topull->previous;
    struct node *b = topull->next;
    a->next = b; b->previous = a;
    free(topull);
    plist->head = b;
}


void *pushIntegers(void *plist) {
    int c = 0;
    while (c < 15) {
        int x = getRandom();
        push(x, plist);
        c++;
    }
    return NULL;
}


void *pullIntegers(void *plist) {
    int c = 0;
    while (c < 15) {
        int x = getRandom();
        struct node *topull = malloc(sizeof(struct node));
        topull->value = x;
        pull(topull, plist);
        c++;
    }
    return NULL;
}


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


void freeList(struct list *tofree) {
    struct node *head = tofree->head;
    struct node *iter;
    while (head != NULL) {
        iter = head; head = head->next;
        free(iter);
    }
    tofree->head = iter;
}


int main() {
    struct node *head = NULL;
    struct list *myList = malloc(sizeof(struct list));
    pthread_t pullid, pushid;
        
    pthread_create(&pullid, NULL, pullIntegers, NULL);
    pthread_join(pullid, NULL);
    pthread_create(&pushid, NULL, pushIntegers, NULL);
    pthread_join(pullid, NULL);
            
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
    freeList(myList);
    
    return 0;
}