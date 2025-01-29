#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct NOD{
    int data;
    char c;
    char cod[100];
    struct NOD * left;
    struct NOD * right;
};

struct NOD * adauga_nod( int data, char c){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->left = NULL;
    nou->right  = NULL;
    nou->c = c;
    nou->data = data;
    return nou;
}


struct NOD * arbore(struct NOD ** heap, int dim){
    struct NOD ** copie_heap = malloc(dim * sizeof(struct NOD *));
    for (int i = 0; i < dim; i++) {
        copie_heap[i] = heap[i];
    }
    while(dim > 1){
        struct NOD * stanga = copie_heap[0];
        struct NOD * dreapta = copie_heap[1];
        int suma = stanga->data + dreapta->data;
        struct NOD * parinte = malloc(sizeof(struct NOD));
        parinte->left = stanga;
        parinte->right = dreapta;
        parinte->c = '-';
        parinte->data = suma;
        copie_heap[1] = parinte;

        //shiftare la stanga
        for (int i = 0; i < dim - 1; i++) {
            copie_heap[i] = copie_heap[i + 1];
        }
         dim--;
        for (int i = 0; i < dim ; i++) {
            for (int j = i + 1; j < dim; j++) {
                if (copie_heap[i]->data > copie_heap[j]->data) {
                    struct NOD *temp = copie_heap[i];
                    copie_heap[i] = copie_heap[j];
                    copie_heap[j] = temp;
                }
            }
        }
       
    }
   
    struct NOD * root = copie_heap[0];
    free(copie_heap);
    return root;
}
void caz_2(struct NOD ** heap, int dim){
    // for(int i=0; i<dim; i++){
    //     printf("%i ", heap[i]->data);
    // }
    // printf("\n");
    struct NOD ** copie_heap = malloc(dim * sizeof(struct NOD *));
    for (int i = 0; i < dim; i++) {
        copie_heap[i] = heap[i];
    }
    int i =0;
    while(i<3){
        struct NOD * stanga = copie_heap[0];
        struct NOD * dreapta = copie_heap[1];
        int suma = stanga->data + dreapta->data;
        struct NOD * parinte = malloc(sizeof(struct NOD));
        parinte->left = stanga;
        parinte->right = dreapta;
        parinte->c = '-';
        parinte->data = suma;
        copie_heap[1] = parinte;

        //shiftare la stanga
         for (int i = 0; i < dim - 1; i++) {
            copie_heap[i] = copie_heap[i + 1];
        }
        
        for (int i = 0; i < dim ; i++) {
            for (int j = i + 1; j < dim; j++) {
                if (copie_heap[i]->data > copie_heap[j]->data) {
                    struct NOD *temp = copie_heap[i];
                    copie_heap[i] = copie_heap[j];
                    copie_heap[j] = temp;
                }
            }
        }
        dim--;
        i++;
        // for(int i=0; i<dim; i++){
        // printf("%i ", heap[i]->data);
        // }
        // printf("\n");
    }
    for(int i=0; i<dim; i++){
        printf("%i ", copie_heap[i]->data);
    }
    free(copie_heap);

}

// Modificăm funcția ca să returneze codul
char* cauta_nod(struct NOD * root, char c, char cod[], int index) {
    if(root == NULL) {
        return NULL;  
    }

    if(root->c == c){
        cod[index] = '\0';  
        return cod; 
    }

    if(root->left) {
        cod[index] = '0'; 
        char* result = cauta_nod(root->left, c, cod, index + 1);
        if (result) {
            return result;  
        }
    }

    if(root->right) {
        cod[index] = '1'; 
        char* result = cauta_nod(root->right, c, cod, index + 1);
        if (result) {
            return result;  
        }
    }

    return NULL;  
}



void afisare_drum(struct NOD * root, struct NOD ** lista, int dim){
    char cod[100]; 
    for(int i = 0; i < dim; i++){
        printf("%c:", lista[i]->c);
        char* cod_obtinut = cauta_nod(root, lista[i]->c, cod, 0);
        printf("%s\n", cod_obtinut);
        // printf("\n");
    }
}
// void preordine(struct NOD* root) {
//     if (root == NULL) return;
//     printf("%c:%d\n", root->c, root->data);
//     preordine(root->left);
//     preordine(root->right);
// }

int main() {
    char text[100];
    fgets(text,100,stdin);
    text[strcspn(text, "\n")] = 0;
    // printf("%s",text);
    int test;
    scanf("%i", &test);
    int v[256] = {0};
    for(int i = 0; text[i] != '\0'; i++){
        v[(unsigned char)text[i]]++;
    }
    // v[32] = 0; // scap de \n
    int dim = 0;
    for(int i=0; i<256 ; i++){
        if(v[i]!=0){
          dim++;  
        }
    }
    struct NOD ** lista = malloc(dim*sizeof(struct NOD*));
    for(int i =0; i<dim; i++){
        lista[i] = NULL;
    }
    int j = 0;
    for(int i=0; i<256; i++){
        if(v[i]!=0){
            lista[j] = adauga_nod( v[i], (char)i);
            j++;
        }
    }
    for(int i=0; i<dim; i++){
                for(int j =i; j<dim; j++){
                    if(lista[i]->data > lista[j]->data){
                        int temp = lista[i]->data;
                        char c = lista[i]->c;
                        lista[i]->data = lista[j]->data;
                        lista[i]->c = lista[j]->c;
                        lista[j]->data = temp;
                        lista[j]->c = c;
                    }
                }
            }
    // printf("%i ", dim);
    switch(test){
        case 1:{
            
           for(int i=0; i<dim; i++){
               printf("%c:%i\n", lista[i]->c, lista[i]->data);
           }
            break;
        }
        case 2:{
            caz_2(lista,dim);
            break;
        }
        case 3 :{
            struct NOD * root = arbore(lista,dim);
            // preordine(root);
            afisare_drum(root, lista,dim);
            break;
        }
        case 4 :{
            struct NOD * root = arbore(lista,dim);
            for(int i =0; i<dim; i++){
                char cod[100];
                char* cod_obtinut = cauta_nod(root, lista[i]->c, cod, 0);
                strcpy(lista[i]->cod, cod_obtinut);
            }
            // for(int i=0; i<dim; i++){
            //     printf("%c:%i\n", lista[i]->c, lista[i]->data);
            // }
            // inlocuieste_text()
            int i=0;
            while(text[i]!='\0'){
                for(int j =0; j<dim; j++){
                    if(lista[j]->c ==text[i]){
                        printf("%s",lista[j]->cod);
                    }
                }
                i++;
            }
            printf("\n");
            break;
        }
        case 5 :{
            // printf("%i", strlen(text));
            int len = strlen(text);
            struct NOD * root = arbore(lista,dim);
            for(int i =0; i<dim; i++){
                char cod[100];
                char* cod_obtinut = cauta_nod(root, lista[i]->c, cod, 0);
                strcpy(lista[i]->cod, cod_obtinut);
            }
            int i=0;
            int len_nou = 0;
            while(text[i]!='\0'){
                for(int j =0; j<dim; j++){
                    if(lista[j]->c ==text[i]){
                        len_nou+=strlen(lista[j]->cod);
                    }
                }
                i++;
            }
            printf("%i",len*8 - len_nou);
            break;
        }
        
    }
    return 0;

}

