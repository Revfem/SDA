#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct NOD {
    char cuvant[20];
    struct NOD * next;
    
}nod;

unsigned int hash_key(const char * cuv, int n){
    unsigned int sum = 0;
    int dim = strlen(cuv);
    for(int i=0; i <dim ; i++){
        sum+=*cuv;
        cuv++;
    }
    return sum%n;
}

void citire_hash(struct NOD ** hash, int nr, int n){
    for(int i=0; i<nr; i++){
        struct NOD * nou = malloc(sizeof(struct NOD));
        nou->next = NULL;
        scanf("%s", nou->cuvant);
        int poz = hash_key(nou->cuvant, n);
        if(hash[poz]==NULL){
            hash[poz] = nou;
        }
        else{
            struct NOD * current = hash[poz];
            while(current->next!=NULL){
                current=current->next;
            }
            current->next = nou;
        }
        
    }
}
void afisare_hash(struct NOD ** hash, int n){
    for(int i=0; i<n; i++){
        if(hash[i]!=NULL){
            struct NOD * current = hash[i];
            while(current!=NULL){
                printf("%s %i\n", current->cuvant, i);
                current = current->next;
            }
            
        }
    }
}
void ordonare_cuv( char * str){
    int len = strlen(str);
    for(int i=0; i<len ; i++){
        for(int j=i+1; j<len; j++){
            if(str[i]>str[j]){
                char temp = str[i];
                str[i]=str[j];
                str[j]=temp;
            }
        }
    }

    
}
void afisare_anagrame(struct NOD ** hash, int n , const char * cuv){
    int key = hash_key(cuv,n);
    if(hash[key] == NULL){
        return;
    }
    char ord[20];
    strcpy(ord, cuv);
    ordonare_cuv(ord);
    // printf("%s", ord);
    struct NOD * current = hash[key];
    while(current!=NULL){
        char temp[20];
        strcpy(temp, current->cuvant);
        ordonare_cuv(temp);
        // printf("%s ", temp);
        if(strcmp(ord, temp)==0){
            printf("%s\n", current->cuvant);
        }
        current=current->next;
    }
    
}
void eliminare_anagrame(struct NOD **hash, int n, int nr){
    struct NOD * lista = malloc(nr*sizeof(struct NOD));
    int j=0;
    for(int i=0; i<n; i++){
        if(hash[i]!=NULL){
            struct  NOD * current = hash[i];
            while(current!=NULL){
                strcpy(lista[j].cuvant, current->cuvant);
                j++;
                current = current->next;
            }
        }
    }
    // for(int i=0; i<nr; i++){
    //     printf("%s\n", lista[i].cuvant);
    // }
    for(int i=0; i<nr; i++){
        char cuv_temp[20];
        strcpy(cuv_temp, lista[i].cuvant);
        ordonare_cuv(cuv_temp);
        for(int k =i+1; k<nr; k++){
            char ord[20];
            strcpy(ord, lista[k].cuvant);
            ordonare_cuv(ord);
            if(strcmp(ord, cuv_temp)==0){
                strcpy(lista[k].cuvant,"-");
                strcpy(lista[i].cuvant,"-");
            }
        }
    }
    for(int i=0; i<nr; i++){
        if(strcmp(lista[i].cuvant, "-")!=0){
          printf("%s\n", lista[i].cuvant);  
        }
        
    }
    
}

int main(){
    int n;
    scanf("%i", &n);
    struct NOD ** hash = malloc(n*sizeof(struct NOD*));
    for(int i=0; i <n; i++){
        hash[i] = NULL;
    }
    int nr;
    scanf("%i", &nr);
    citire_hash(hash, nr, n);
    int  test;
    scanf("%i", &test);
    switch(test){
        case 1:{
            afisare_hash(hash,n);
            break;
        }
        case 2:{
            char temp[20];
            scanf("%s", temp);
            afisare_anagrame(hash,n,temp);
            break;
        }
        case 3:{
            eliminare_anagrame(hash,n,nr);
            break;
        }
    }
    
    
    return 0;
}
