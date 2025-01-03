#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct NOD{
    char nume[20];
    int marime;
    char culoare[20];
    struct NOD * next;
}nod;
unsigned int hash_key(const char *nume, const char * culoare, int marime, int m){
    int dim = strlen(nume);
    unsigned int suma = 0;
    for(int i=0; i<dim; i++){
        suma+=*nume;
        nume++;
    }
    dim = strlen(culoare);
    for(int i =0; i<dim; i++){
        suma += *culoare;
        culoare++;
    }
    suma +=marime;
    return suma%m;
}
void chain_hash(struct NOD ** hash, int m, struct NOD *head){
    struct NOD * current = head;
    while(current!=NULL){
        int poz = hash_key(current->nume, current->culoare, current->marime,m);
        if(hash[poz]==NULL){
            hash[poz]=malloc(sizeof(struct NOD));
            hash[poz]->next = NULL;
            strcpy(hash[poz]->nume, current->nume);
            strcpy(hash[poz]->culoare,current->culoare);
            hash[poz]->marime = current->marime;
        }
        else{
            struct NOD * nou = malloc(sizeof(struct NOD));
            struct NOD * cur = hash[poz];
            nou->next = NULL;
            strcpy(nou->nume, current->nume);
            strcpy(nou->culoare,current->culoare);
            nou->marime = current->marime;
            while(cur->next!=NULL){
                cur=cur->next;
            }
            cur->next = nou;
        }
        current=current->next;
    }
    
}
struct NOD* citire_lista(struct NOD * head){

    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next  = NULL;
    scanf("%s %i %s", nou->nume, &nou->marime, nou->culoare);
    if(head == NULL){
        head = nou;
        return head;
    }
    else{
        struct NOD * current = head;
        while(current->next!=NULL){
            current = current->next;
        }
        current->next = nou;
        return head;
    }
}
void afisare_lista(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%s %i %s\n", current->nume, current->marime, current->culoare);
        current = current->next;
    }
}
void afisare_hash(struct NOD ** hash,int m){
    for(int i=0; i<m; i++){
        if(hash[i]!=NULL){
            struct NOD * current = hash[i];
            while(current!=NULL){
                printf("%s %i %s %i\n", current->nume, current->marime, current->culoare, i);
                current=current->next;
                
            }
        }
        
    }
}
void open_hash(struct NOD ** hash, int m, struct NOD * head){
    
    struct NOD * current = head;
    while(current!=NULL){
        int poz = hash_key(current->nume, current->culoare, current->marime,m);
        if(hash[poz]== NULL){
            hash[poz] = malloc(sizeof(struct NOD));
            hash[poz]->next = NULL;
            strcpy(hash[poz]->nume, current->nume);
            strcpy(hash[poz]->culoare,current->culoare);
            hash[poz]->marime = current->marime;
        }
        else{ // coliziune
            poz++;
            if(poz==m){
                poz = 0;
            }
            if(hash[poz]==NULL){
                hash[poz] = malloc(sizeof(struct NOD));
                hash[poz]->next = NULL;
            }
            strcpy(hash[poz]->nume, current->nume);
            strcpy(hash[poz]->culoare,current->culoare);
            hash[poz]->marime = current->marime;
        }
        
        current = current->next;
    }
}
void afisare_open_hash(struct NOD **hash, int m){
    for(int i=0; i<m; i++){
        printf("%s %i %s %i\n", hash[i]->nume, hash[i]->marime, hash[i]->culoare,i);
    }
}
void cauta_dimensiune_minima( struct NOD * lista, int m ){
    
    while(1){
        m++;
        struct NOD ** hash_open = malloc(m*sizeof(struct NOD*));
        struct NOD ** hash_chain = malloc(m*sizeof(struct NOD*));
        for(int i=0; i<m; i++){
            hash_open[i] = NULL;
            hash_chain[i]= NULL;
        }
        chain_hash(hash_chain,m,lista);
        open_hash(hash_open,m,lista);
        int flag = 0;
        for(int i=0; i<m; i++){
            if( hash_chain[i]!=NULL && hash_chain[i]->next!=NULL){
                flag = 1;
                break; 
            }
            if((hash_chain[i]  == NULL  && hash_open[i]!=NULL) || (hash_chain[i] != NULL && hash_open[i] == NULL)){
                flag = 1;
                break;
            }
            if(hash_chain[i]!=NULL && hash_open[i]!=NULL){
                if( strcmp(hash_chain[i]->nume, hash_open[i]->nume) != 0 || strcmp(hash_chain[i]->culoare, hash_open[i]->culoare)!=0 || hash_chain[i]->marime!=hash_open[i]->marime){
                    flag = 1;
                    break;
                }
            }
            
        }
        if(flag == 0){
            break;
        }
    }
    printf("%i\n", m);
    
}
int main(){
    int m;
    scanf("%i", &m);
    struct NOD ** hash_chain = malloc(m*sizeof(struct NOD*));
    for(int i=0; i<m; i++){
        hash_chain[i] = NULL;
    }
    
    int n;
    scanf("%i", &n);
    struct NOD * lista = NULL;
    for(int i=0; i<n; i++){
        lista = citire_lista(lista);
    }
    chain_hash(hash_chain,m, lista); // facut prin chaining;
    struct NOD ** hash_open = malloc(m*sizeof(struct NOD*));
    for(int i=0; i<m; i++){
        hash_open[i]=NULL;
    }
    open_hash(hash_open,m, lista);
    int test;
    scanf("%i", &test);
    switch(test){
        case 1:{
            afisare_lista(lista);
            break;
        }
        case 2:{
            afisare_hash(hash_chain, m);
            break;
        }
        case 3:{
            cauta_dimensiune_minima(lista,m);
            // afisare_open_hash(hash_open,m);
            
            break;
        }
    }
    
}
