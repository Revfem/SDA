#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD {
    char nume[20];
    struct NOD * next;
};
struct NOD * citire(struct NOD * head){
    struct NOD * nod_nou = malloc(sizeof(struct NOD));
    scanf("%s", nod_nou->nume);
    nod_nou->next = NULL;
    if(head == NULL){
        head = nod_nou;
        return head;
    }
    struct NOD * current = head;
    while(current->next!=NULL){
        current =current->next;
    }
    current->next =nod_nou;
    return head;
}
void afisare_istoric(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%s\n", current->nume);
        current = current->next;
    }
}
struct NOD * inversare_n(struct NOD * head,int n){ // FOARTE IMPORTANTA
    struct NOD * prev = NULL;
    struct NOD * current = head;
    struct NOD * next= NULL;
    while(current!=NULL){
        struct NOD * start = current;
        struct NOD * end = NULL;
        int count = 0;
        while(current!=NULL && count<n){
            next = current->next;
            current->next = end; // current devine ultimul nod
            end = current;
            current = next;
            count++;
        }
        if (prev == NULL) {
            head = end;
        } else {
            prev->next = end;
        }
        start->next = current; // point ultimul din gr inversat la urmatorul normal (examen 1->examen 4)
        prev = start; 
    }
    return head;
}
void afisare_istoric_exclude(struct NOD * head){
    struct NOD * current = head;
    int count =1;
    while(current!=NULL){
        if(count %7 != 0){
           printf("%s\n", current->nume); 
        }
        current = current->next;
        count++;
    }
}
int main(){
    
    int nr_examinari;
    scanf("%i", &nr_examinari);
    struct NOD * lista = NULL;
    for(int i=0; i<nr_examinari; i++){
        lista = citire(lista);
    }
    int test;
    scanf("%i", &test);
    
    switch(test){
        case 1 :
            afisare_istoric(lista);
            break;
        case 2 :
            lista = inversare_n(lista,3);
            afisare_istoric(lista);
            break;
        case 3 :
            int n;
            scanf("%i", &n);
            lista = inversare_n(lista,n);
            afisare_istoric(lista);
            break;
        case 4 :
            lista = inversare_n(lista,3);
            afisare_istoric_exclude(lista);
            break;
            
        
    }
    return 0;
}
