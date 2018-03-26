#include "postingList.h"

struct postingList{
    int    total_freq; //How many times a word exists in the text file.TOTAL frequency
    struct node* start;
    struct node* tail;
};

struct node{
    int     id;
    int     query_freq; //How many times a word exists in a specific query [id: 0],[freq: 3]
    struct  node* next_node;
};

struct node* _get_node(){
    struct node* new_node;
    new_node = malloc(sizeof(struct node));
    if(new_node == NULL){
        printf("Error: Couldn't allocate memory [_get_node()/postingList.c]\n");
        exit(-1); 
    }
    return new_node;
}

struct postingList* initList(){
    struct postingList* pL = malloc(sizeof(struct postingList));

    if(pL == NULL){
        printf("Error: Couldn't allocate memory [postingList.c]\n" );
        exit(1);
    }

    pL->total_freq  = 0;
    pL->start       = NULL;
    pL->tail        = NULL;

    return pL;
}
/*****************  Insert in Posting List  ***************************/
void pushList(struct postingList* pL, int id){
    /* Node Exists in pL */
    if(pL -> tail != NULL && pL->tail->id == id){
            pL->tail->query_freq = pL->tail->query_freq + 1; 
            return;
    }
    /* Node Doesn't Exists in pL */
    else{  
        struct node* pLnode = _get_node();

        pLnode -> next_node  = NULL;
        pLnode -> id         = id;
        pLnode -> query_freq = 1;
        pL     -> total_freq = pL ->total_freq + 1;

        /* Insert pL node at the end */
        if(pL ->start == NULL){
            pL->start  = pLnode;
        }
        if(pL ->tail != NULL){
            pL->tail->next_node = pLnode;
        }

        pL ->tail = pLnode;
        return;
    }

}

/*****************  Get Total Word Frequency  ***************************/
int get_freq(struct postingList* pL){   
    if( pL == NULL){
        printf("Error: get_freq()\n");
        return -1;
    }

    return pL->total_freq;
}


int get_list_data(struct postingList* pL, int* id, int* query_freq){
    if( pL -> start == NULL){
        return -1;  //Break point
    }else{

        /* Get pL Data */    
        *query_freq = pL -> start -> query_freq;
        *id         = pL -> start -> id;
        pL->start   = pL -> start -> next_node;    // Iterate to the next

        return 0;
    }
}

/*****************  Print Posting List  ***************************/
void printList(struct postingList* pL){
    int idd,qu_fr;
    printf("Print Posting List: \n");
    while(pL -> start != NULL){
        idd        = pL -> start -> id;
        qu_fr      = pL -> start -> query_freq;
        pL->start  = pL -> start -> next_node;
        printf("\t\t[id: %d, freq: %d]\n", idd,qu_fr);
    }
    return;
}


/*****************  Free Posting List  ***************************/
void destroyList(struct postingList* pL){
    struct node* pLnode = pL -> start;

    while(pLnode != NULL){
        pLnode = pLnode -> next_node;
        free(pLnode);
    }

    free(pL);
    pL = NULL;
    return;
}
