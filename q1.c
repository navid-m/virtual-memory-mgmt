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

        //setting the value
        if (a == 0 || a == 6) {
            this->value = 0;
        } else {
            this->value = -1;
        }

        //setting next and previous for non-first nodes
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