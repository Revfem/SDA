#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct NOD {
    char nume[20];
    int produse;
    struct NOD * next;
}nod;

struct NOD * citeste(struct NOD * head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next = NULL;
    scanf("%s%i", nou->nume, &nou->produse);
    if(nou->produse == 0){
        free(nou);
        return head;
    }
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
void afisare(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%s %i\n", current->nume, current->produse);
        current = current->next;
    }
}
int calc_produse(struct NOD * head){
    struct NOD * current =head;
    int suma = 0;
    while(current!=NULL){
        suma +=current->produse;
        current = current->next;
    }
    return suma;
}
struct NOD * adauga_nod(struct NOD * head, struct NOD * org){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next = NULL;
    strcpy(nou->nume, org->nume);
    nou->produse = org->produse;
    if(head == NULL){
        head = nou;
        return head;
    }
    struct NOD * current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next=nou;
    return head;
    
}
void imparte_coada(struct NOD * head){
    struct NOD * current = head;
    int dim = 0;

    struct NOD * coada1 = NULL;
    struct NOD * coada2 = NULL;
    while(current!=NULL){
        if(dim%2==0){
            coada1=adauga_nod(coada1,current);
        }
        else{
           coada2=adauga_nod(coada2,current); 
        }
        dim++;
        current = current->next;
    }
    
    current = coada1;
    while(current!=NULL){
        printf("%s\n", current->nume);
        current = current->next;
    }
    current = coada2;
    while(current!=NULL){
        printf("%s\n", current->nume);
        current = current->next;
    }
}
void imparte_clienti(struct NOD* head){
    struct NOD * current = head;
    int suma1=0;
    int suma2=0;
    struct NOD * coada1 = NULL;
    struct NOD * coada2 = NULL;
    while(current!=NULL){
        if(suma1<=suma2){
            suma1+=current->produse;
            coada1=adauga_nod(coada1,current);
        }
        else{
            suma2+=current->produse;
            coada2=adauga_nod(coada2,current);
        }
        current = current->next;
    }
    current = coada1;
    // printf("coada 1 : ");
    while(current!=NULL){
        printf("%s\n", current->nume);
        current = current->next;
    }
    current = coada2;
    // printf("coada 2 : ");
    while(current!=NULL){
        printf("%s\n", current->nume);
        current = current->next;
    }
    
}
void calc_secunde(struct NOD * head, int secunde){
    struct NOD * current = head;
    int suma1=0;
    int suma2=0;
    struct NOD * coada1 = NULL;
    struct NOD * coada2 = NULL;
    while(current!=NULL){
        if(suma1<=suma2){
            suma1+=current->produse;
            coada1=adauga_nod(coada1,current);
        }
        else{
            suma2+=current->produse;
            coada2=adauga_nod(coada2,current);
        }
        current = current->next;
    }
    
    current = coada1;
    for(int i=0; i<secunde; i++){
        current->produse--;
        if(current->produse==0){
            current=current->next;
        }
    }
    current = coada2;
    for(int i=0; i<secunde; i++){
        current->produse--;
        if(current->produse==0){
            current=current->next;
        }
    }
    current = coada1;
    while(current!=NULL){
        if(current->produse!=0){
           printf("%s\n", current->nume); 
        }
        current = current->next;
    }
    current = coada2;
    // printf("coada 2 : ");
    while(current!=NULL){
        if(current->produse!=0){
           printf("%s\n", current->nume); 
        }
        current = current->next;
    }
}
int main(){
    
    int test;
    scanf("%i",&test);
    int secunde;
    scanf("%i", &secunde);
    struct NOD * clienti = NULL;
    while(1){
        if(getchar()== EOF){
            break;
        }
        clienti = citeste(clienti);
        
    }
    switch(test){
        case 1:{
            afisare(clienti);
            break;
        }
        case 2:{
            printf("%i\n",calc_produse(clienti));
            
            break;
        }
        case 3:{
            imparte_coada(clienti);
            break;
        }
        case 4:{
            imparte_clienti(clienti);
            break;
        }
        case 5:{
            calc_secunde(clienti, secunde);
            break;
        }
        
    }
}
