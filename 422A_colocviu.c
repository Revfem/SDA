#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NOD {
    char cnp[14];
    char nume[20];
    struct NOD * next;
}nod;

unsigned int hash_key ( const char * str, int n){
    char temp[7];
    temp[6]='\0';
    strncpy(temp, str+7, 6);
    int nr = atol(temp);
    int doi = (str[1] -'0')*10 + str[2]-'0';
    unsigned long long produs = nr * doi;
    return produs%n;
}
int get_an ( struct NOD * head){
    return (head->cnp[1]-'0')*10 + head->cnp[2] -'0';
}
struct NOD ** adauga_hash(struct NOD ** hash, char *nume, char* cnp, int n){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next = NULL;
    strcpy(nou->cnp, cnp);
    strcpy(nou->nume,nume);
    int an_nou =  (cnp[1] -'0')*10 + cnp[2]-'0';
    int poz = hash_key(cnp,n);
    if(hash[poz] == NULL){
        hash[poz] = nou;
        return hash;
    }
    struct NOD * current = hash[poz];
    
    if(get_an(current)> an_nou){
        nou->next = current;
        hash[poz] = nou;
        return hash;
    }
    while(current->next!=NULL && get_an(current->next) <an_nou){
        current = current->next;
    }
    nou->next=  current->next;
    current->next = nou;
    return hash;
}
struct NOD * adauga_lista(struct NOD  * head, char *nume, char* cnp){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next = NULL;
    strcpy(nou->cnp, cnp);
    strcpy(nou->nume,nume);
    if(head == NULL){
        head = nou;
        return head;
    }
    struct NOD * current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = nou;
    return head;

}
void afisare_lista(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%s %s\n", current->nume, current->cnp);
        current= current->next;
    }
}
void key_show(struct NOD * head,int n){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%i\n", hash_key(current->cnp, n));
        current = current->next;
    }
}
void afisare_hash(struct NOD ** hash, int n){
    for(int i =0; i<n; i++){
        printf("%i:",i);
        if(hash[i]!= NULL){
            struct NOD * current = hash[i];
            while(current!=NULL){
                printf(" %s", current->nume);
                current = current->next;
            }
            printf("\n");
        }
        else{
            printf("\n");
        }
    }
}
void cauta_prag(struct NOD *head, float prag, int n){
    int dim =n;
    while(1){
        dim++;
        int *frecv = calloc(dim,sizeof(int));
        struct NOD * current =head;
        while(current!=NULL){
            int key = hash_key(current->cnp, dim);
            // printf("%i \n" , key);
            current = current->next;
            frecv[key]=1;
        }
        int count = 0;
        // printf("vector de frecv: ");
        for(int i=0; i <dim; i++){
            // printf("%i ", frecv[i]);
            if(frecv[i]==0){
                count++;
            }
        }
        // printf("\n");
        float s  = (float)(dim-count)/(float)dim;
        // printf("count: %i , dim: %i, s: %f\n", count, dim,s);
        // printf("%i\n",s);
        if(prag > s){
            printf("%i\n", dim);
            return;
        }
    }
    
}
int main(){
    int n, nr , test;
    scanf("%i %i", &n, &nr);
    // printf("%i %i", n, nr);
    struct NOD ** hash = malloc(n*sizeof(struct NOD*));
    for(int i=0; i<n; i++){
        hash[i]=NULL;
    }
    struct NOD * lista =  NULL;
    char nume_temp[20];
    char cnp_temp[14];
    for(int i=0; i<nr; i++){
        scanf("%s%s", nume_temp, cnp_temp);
        // printf("%s %s\n", nume_temp, cnp_temp);
       
        hash = adauga_hash(hash, nume_temp, cnp_temp, n);
        lista = adauga_lista(lista, nume_temp, cnp_temp);
    }
    scanf("%i", &test);
    switch(test){
        case 1:{
            afisare_lista(lista);
            break;
        }
        case 2:{
            key_show(lista,n);
            break;  
        }
        case 3:{
            afisare_hash(hash,n);
            break;
        }
        case 4:{
            float prag;
            scanf("%f", &prag);
            // printf("%f", prag);
            cauta_prag(lista,prag,n);
            break;
        }
    }
    return 0;
}
