#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct NOD {
    char nume[50];
    int nr;
    struct NOD * stanga, *dreapta;
};
struct NOD *citire(struct NOD *head) {
    struct NOD *nou = malloc(sizeof(struct NOD));
    nou->dreapta = NULL;
    nou->stanga = NULL;
    scanf("%s", nou->nume);
    scanf("%i", &nou->nr);

    if (head == NULL) {
        head = nou;
        return head;
    }

    struct NOD *current = head;
    struct NOD *parinte = NULL;

    while (current != NULL) {
        parinte = current;  
        if (strcmp(nou->nume, current->nume)<0) {
            current = current->stanga;
        } else {
            current = current->dreapta;
        }
    }

    if (strcmp(nou->nume, parinte->nume)<0) {
        parinte->stanga = nou;
    } else {
        parinte->dreapta = nou;
    }

    return head;
}

struct NOD * cauta_nod(struct NOD * head, char * nume){
   
        if (head == NULL){
            return NULL;
        }
        if(strcmp(head->nume, nume)==0){
            return head;
        }
        struct NOD * tmp = cauta_nod(head->stanga, nume);
        if(tmp!=NULL){
            return tmp;
        }
        
        return cauta_nod(head->dreapta,nume);
}

struct NOD * LCA (struct NOD * root, char * nume1, char * nume2){
    if(root == NULL) {
        return NULL;
    }
    if(strcmp(nume1,root->nume)<0 && strcmp(nume2, root->nume) <0){ // daca ambele orase sunt in stanga parintelui inca n am gasit LCA
        return LCA(root->stanga, nume1,nume2);
    }
    if ( strcmp(nume1,root->nume) >0 && strcmp(nume2, root->nume) >0){
        return LCA(root->dreapta, nume1,nume2);
    }
    return root; // doar cand orasele sunt in parti diferite atunci am LCA
  
    
}
void nr_orase(struct NOD  * nod, int * a){
    if(nod!=NULL){
        (*a)++;
        nr_orase(nod->stanga,a);
        nr_orase(nod->dreapta,a);
        
    }
}
int distanta(struct NOD * root, char * nume){
    if(root == NULL){
        return 0;
    }
    if(strcmp(root->nume, nume)==0){
        return 0;
    }
    if(strcmp(root->nume, nume)>0){ // E pe dos idk why
        if(root->stanga == NULL){
            return 0;
        }
        return root->stanga->nr + distanta(root->stanga,nume);
        
    }
    if(root->dreapta == NULL){
        return 0;
    }
    
    return root->dreapta->nr + distanta(root->dreapta,nume);
}
int calcul_distanta(struct NOD * root, char *nume1, char*nume2){
    struct NOD * lca = LCA(root,nume1,nume2);
    // printf("%s ", lca->nume);
    int d1= distanta(lca,nume1);
    int d2=distanta(lca,nume2);
    // printf("%i %i ", d1, d2); 
    return d1+d2;
}

int main(){
    int n;
    scanf("%i", &n);
    struct NOD * radacina  = NULL;
    for(int i=0; i<n; i++){
        radacina = citire(radacina);
    }
    int test;
    scanf("%i", &test);
    // in_order(radacina);
    int a =0;
    switch(test){
        
        case 1:{
            char nume[50];
            scanf("%s", nume);
            
            // printf("%s",cauta_nod(radacina,nume)->nume);
            nr_orase(cauta_nod(radacina,nume), &a);
            printf("%i", a-1);
            break;
        }
        case 2:{
            char nume1[50], nume2[50];
            scanf("%s%s", nume1,nume2);
           printf("%i", calcul_distanta(radacina,nume1,nume2));
            break;
        }
    }
    return 0;
}
