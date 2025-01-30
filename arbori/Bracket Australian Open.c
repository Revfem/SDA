#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct NOD {
    char nume[30];
    int * set;
    struct NOD * left, * right;
    int size;
};
struct NOD * add_nod ( struct NOD * stanga, struct NOD * dreapta, char *nume){
    struct NOD  * nou = malloc(sizeof(struct NOD));
    nou->left = stanga;
    nou->right = dreapta;
    // nou->nume = malloc(strlen(nume) + 1);
    strcpy(nou->nume, nume);
    return nou;
}
void afiseaza_bracket(struct NOD ** lista, int dim){
    for(int i=0; i<dim; i++){
        
        printf("%s\n", lista[i]->nume);
        if(i%2 != 0 && i != 0 ){
            printf("\n");    
            
        }
    }
    
}
void cauta_runda(struct NOD ** lista, int dim, char * nume1, char * nume2){
    int count = 1;
    while(1){
         while(dim > 1){  /// pana ramane un castigator
            int new_dim = 0;
            struct NOD ** lista_noua = calloc(dim / 2, sizeof(struct NOD*)); // scad la jumate din playeri
            
            for(int i = 0; i < dim; i += 2){
                if(i + 1 < dim){ 
                    if((strcmp(lista[i]->nume, nume1) == 0 && strcmp(lista[i+1]->nume, nume2) == 0) ||
                       (strcmp(lista[i]->nume, nume2) == 0 && strcmp(lista[i+1]->nume, nume1) == 0)){
                        printf("%i\n", count);
                        free(lista_noua);
                        return;
                    }
                    else if(strcmp(lista[i]->nume, nume1) == 0 ){
                          lista_noua[new_dim] = add_nod(NULL, NULL, nume1 );
                   
                    }
                    else if(strcmp(lista[i+1]->nume, nume1) == 0){
                        lista_noua[new_dim] = add_nod(NULL, NULL, nume1 ); 
                    }                            
                    else if(strcmp(lista[i]->nume, nume2) == 0){
                        lista_noua[new_dim] = add_nod(NULL, NULL, nume2 );
                              
                    }
                    else if(strcmp(lista[i+1]->nume, nume2) == 0){
                        lista_noua[new_dim] = add_nod(NULL, NULL, nume2 ); 
                    }
                    else{
                        lista_noua[new_dim] = add_nod(NULL, NULL, lista[i]->nume); 
                        
                    }
                    new_dim++;
                } else {
                    // Dacă avem un număr impar de jucători, ultimul avansează automat
                    lista_noua[new_dim] = lista[i];
                    new_dim++;
                }
            }
    
            free(lista); // Eliberăm vechea listă
            lista = lista_noua;
            dim = new_dim;
            count++;
        }
    }
}

void adauga_set(struct NOD * nod, int * set, int dim){
    nod->set = calloc(dim, sizeof(struct NOD));
    nod->size = dim;
    for(int i=0; i<dim; i++){
        nod->set[i] = set[i];
    }
}
int calcul_set(struct NOD * nod){
    int suma = 0;
    for(int i = 0; i<nod->size; i++){
        suma += nod->set[i];
    }
    return suma;
}
void show_winners(struct NOD ** lista,int dim){
    int count = 0;
    for(int i =0; i<dim; i+= 2){
        int suma1 = calcul_set(lista[i]);
        int suma2 = calcul_set(lista[i+1]);
        if(suma1>=suma2){
            printf("%s\n", lista[i]->nume);
        }
        else{
            printf("%s\n", lista[i+1]->nume);
        }
        
        if(count%2!=0 && count!=0){
            printf("\n");
        }
        count++;
    }  
}
void meci_lung(struct NOD ** lista, int dim){
    int aux = 0;
    char nume1[30], nume2[30];  
    nume1[0] = '\0'; 
    nume2[0] = '\0';

    for(int i = 0; i < dim; i += 2){
        int suma = calcul_set(lista[i]) + calcul_set(lista[i+1]);
        
        if (suma > aux) {
            aux = suma;
            strcpy(nume1, lista[i]->nume);  
            strcpy(nume2, lista[i+1]->nume);
        }
    }
    printf("%s\n%s\n", nume1, nume2);
}
int main(){
    
    int n;
    
    scanf("%i", &n);
    struct NOD ** lista = calloc(n,sizeof(struct NOD*)); 
    for(int i =0; i<n; i++){
        char nume[30];
        scanf("%s", nume);
        // printf("%s" , nume);
        lista[i] = add_nod(NULL, NULL , nume);
    }
    int test;
    scanf("%i", &test);
    switch(test){
        case 1:{
            afiseaza_bracket(lista,n);
            break;
        }
        case 2:{
            char nume1[30], nume2[30];
            scanf("%s%s", nume1, nume2);
            cauta_runda(lista, n , nume1, nume2);
            break;
        }
        case 3:{
            int * set; 
            int size;
            for(int i=0; i<n; i+=2){
                scanf("%i", &size);
                // printf("%i\n");
                set = calloc(size,sizeof(int));
                for(int j=0; j<size; j++){
                    scanf("%i", &set[j]);
                }
                adauga_set(lista[i], set, size);
                for(int j=0; j<size; j++){
                    scanf("%i", &set[j]);
                }
                adauga_set(lista[i+1], set, size);
                free(set);
            }
            // for(int i=0; i<n ;i++){
            //     printf("%s ", lista[i]->nume);
            //     for(int j = 0; j<lista[i]->size; j++){
            //         printf("%i ", lista[i]->set[j]);
            //     }
            //     printf("\n");
            // }
            show_winners(lista,n);
            break;
        }
        case 4:{
            int * set; 
            int size;
            for(int i=0; i<n; i+=2){
                scanf("%i", &size);
                // printf("%i\n");
                set = calloc(size,sizeof(int));
                for(int j=0; j<size; j++){
                    scanf("%i", &set[j]);
                }
                adauga_set(lista[i], set, size);
                for(int j=0; j<size; j++){
                    scanf("%i", &set[j]);
                }
                adauga_set(lista[i+1], set, size);
                free(set);
            }
            meci_lung(lista, n);
            break;
        }
        case 5:{
            int size;
            int dim = n;
            while (dim > 1) {  
                struct NOD **lista_noua = calloc(dim / 2, sizeof(struct NOD*)); 
                int new_dim = 0;  
        
                for (int i = 0; i < dim; i += 2) {
                    scanf("%i", &size);
                    int *set1 = calloc(size, sizeof(int));
                    int *set2 = calloc(size, sizeof(int));
        
                    for (int j = 0; j < size; j++) {
                        scanf("%i", &set1[j]);
                    }
                    adauga_set(lista[i], set1, size);
        
                    for (int j = 0; j < size; j++) {
                        scanf("%i", &set2[j]);
                    }
                    adauga_set(lista[i+1], set2, size);
                    int suma1 = calcul_set(lista[i]);
                    int suma2 = calcul_set(lista[i+1]);
        
                    if (suma1 >= suma2) {
                        lista_noua[new_dim] = lista[i]; 
                    } else {
                        lista_noua[new_dim] = lista[i+1];  
                    }
                    new_dim++;
        
                    free(set1);
                    free(set2);
                }
        
                free(lista); 
                lista = lista_noua;
                dim = new_dim;
            }

            printf("%s\n", lista[0]->nume);
            free(lista);
            
            break;
        }
    }
    return 0;
}
