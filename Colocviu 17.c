#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct NOD {
    int valoare;
    char prop[20];
    int nr_celule;
    struct NOD * next;
}nod;
struct NOD * citeste( struct NOD * head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->next = NULL;
    scanf("%i%s", &nou->valoare, nou->prop);
    if(strcmp(nou->prop,"dubleaza")!=0){
        scanf("%i", &nou->nr_celule);
    }
    else{
        nou->nr_celule = 0;
    }
    if(head == NULL){
        head = nou;
        return head;
    }
    struct NOD * current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next= nou;
    return head;
}
void afiseaza(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        if(strcmp(current->prop, "dubleaza")!=0){
          printf("%i %s %i\n", current->valoare, current->prop, current->nr_celule);  
        }
        else{
          printf("%i %s\n", current->valoare, current->prop); 
        }
        current = current->next;
    }
}
int calculeaza_pozitie(struct NOD * head, int start, int zar){
    struct NOD * current = head;
    int suma = start+zar;
 
    while(current!=NULL){
        if(current->valoare == suma && strcmp(current->prop, "avanseaza")==0){
            suma+=current->nr_celule;
        }
        else if (current->valoare == suma && strcmp(current->prop, "dubleaza")==0){
            suma+=zar;
        }
        else if(current->valoare == suma){
            suma -= current->nr_celule;
            if(suma<0){
                suma =0;
            }
        }
       
        current  = current->next;
    }
    return suma;
}
void joc_piticot(struct NOD * head, int n){    
    int j1 = 0;
    int j2 = 0;
    int valoare;
    while(1){
        scanf("%i", &valoare);
        j1 = calculeaza_pozitie(head, j1, valoare);
        if(j1>=n){
           printf("1\n%i\n", j2);
           return;
        }
        scanf("%i", &valoare);
        j2 = calculeaza_pozitie(head, j2, valoare);
        // printf("j1:%i j2:%i\n", j1,j2);
        
        if(j2>n){
           printf("2\n%i\n", j1);
           return; 
        }
        
    }
    
}

int main(){
    int n, nr;
    scanf("%i%i", &n,&nr);
    struct NOD * speciale = NULL;
    for(int i=0; i<nr; i++){
        speciale = citeste(speciale);
    }
    int test;
    scanf("%i", &test);
    switch(test){
        case 1:{
            afiseaza(speciale);
            break;
        }
        case 2:{
            int start, zar;
            scanf("%i%i", &start,&zar);
            printf("%i\n",calculeaza_pozitie(speciale, start,zar));
            break;
        }
        case 3:{
            joc_piticot(speciale,n);
            break;
        }
    }
    
    return 0;
}
