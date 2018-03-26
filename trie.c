#include "trie.h"

struct Trie{
    struct  Trie_node* head;
    int     total_words;
};

struct Trie_node{
    struct Trie_node*    next;
    struct Trie_node*    child;
    struct postingList *pL;
    char                character; 
};

struct Trie_node* _horizontalTraverse(struct Trie_node *, char);
struct Trie_node* _pushChar(struct Trie_node *,char,int*);

struct Trie_node* _get_trie_node(){
    struct Trie_node* new_trie_node;
    
    new_trie_node = malloc(sizeof(struct Trie_node));
    if(new_trie_node == NULL){
        printf("Error: Couldn't allocate memory [trie.c]\n" );
        exit(-1);
    }
    return new_trie_node;
}

struct Trie* initTrie(){
    struct Trie* trie = malloc(sizeof(struct Trie));

    if(trie == NULL){
        printf("Error: Couldn't allocate memory [trie.c]\n" );
        exit(-1);
    }
    trie->total_words = 0;
    trie->head        = NULL;

    return trie;
}

int pushTrie(struct Trie* trie, char* word, int id){

    int lenght,i,flag;  
    struct Trie_node* cursor   = trie->head;
    struct Trie_node* previous = cursor;
    struct Trie_node* tmp;

    lenght = strlen(word);
    for(i = 0; i < lenght + 1; i++){
        tmp = _pushChar(cursor,word[i],&flag);


        if(i == 0 && flag == 1){  
            trie->head = tmp;
        }
        else if(flag == 1){
            previous->child = tmp;
        }
        
        previous = tmp;
        cursor   = tmp->child;

        /* In Leaf Nodes Add a Posting List */
        if(i == lenght){
                                            
            if(tmp->pL == NULL){
                tmp->pL = initList();
            }
            pushList(tmp->pL,id);
        }   
    } 
    trie->total_words = trie->total_words + 1;
    return 0;
}

struct postingList* search(struct Trie* trie, char* word){
    int lenght,i;
    lenght = strlen(word);

    struct Trie_node* cursor = trie-> head;
    for(i = 0; i < lenght + 1; i++){
        cursor = _horizontalTraverse(cursor, word[i]);

        /* Word not Found*/
        if(cursor == NULL){
            return NULL;
        }
        /* Word Found */
        if(i == lenght){
            return cursor->pL;
        }

        cursor = cursor->child;
    }
}

    
int get_total_words(struct Trie* trie){
    if(trie == NULL){
        printf("Error: get_freq()\n");
        return -1;
    }

    return trie -> total_words;
}

struct Trie_node* _horizontalTraverse(struct Trie_node* node, char character){
    struct Trie_node* cursor = node;
    while(cursor != NULL){
        if(character == cursor->character){
            return cursor;
        }

        cursor = cursor->next;
    }

    return NULL;
}

struct Trie_node* _pushChar(struct Trie_node* trie_node,char character, int* flag){
    struct Trie_node* cursor   = trie_node;
    struct Trie_node* previous = trie_node;
    // Iterate nodes till find the node with the letter 
    while(cursor != NULL){
    
        /* Key exists */ 
        if(character == cursor->character){            
            return cursor;
        }

        previous = cursor;
        cursor   = cursor->next;
    } 
    struct Trie_node* new_node = _get_trie_node();

    new_node->character = character;
    new_node->next      = NULL;
    new_node->child     = NULL;
    new_node->pL        = NULL;

    if(trie_node == NULL){
        *flag = 1;
        return new_node;
    }
    
    previous->next = new_node;
    new_node->next = cursor;


    return new_node;
}

/*****************  Print Trie  ***************************/
char word[512];

int _print(struct Trie_node* cursor,int level){
    int i;
    if(cursor->next != NULL){
        _print(cursor->next,level);
    }
    word[level] = cursor->character;
    if(cursor->pL != NULL){
        for ( i = 0; i < level+1; i++){
            printf("%c", word[i]); 
        }
        printf(" %d\n", get_freq(cursor->pL));
    }
    if(cursor->child != NULL){
        _print(cursor->child,level+1);
    }
    return 0;
}



int printTrie(struct Trie* trie){
    printf("Print The Trie\n");
    if(trie->head == NULL){
        return -1;
    }
    struct Trie_node* currNode = trie->head;
    _print(currNode,0);
    
    return 0;
}


/*****************  Free Trie  ***************************/
int _destroy(struct Trie_node* cursor,int level){
    if(cursor->next != NULL){
        _destroy(cursor->next,level);
    }
    if(cursor->pL != NULL){
        destroyList(cursor->pL);
    }
    if(cursor->child != NULL){
        _destroy(cursor->child,level+1);
    }
    return 0;
}

void destroyTrie(struct Trie* trie){
    struct Trie_node* currNode = trie->head;
    
    _destroy(currNode, 0);
    free(trie);
    trie = NULL;

    return;
}
