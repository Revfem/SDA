#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Elev {
    char nume[20];
    char cod[20];
    int note[9];
    float medie;
    // int size;
    
}elev;
void medie(elev *e){
    float suma=0;
    for(int i=0; i<9; i++){
        suma+= (float)e->note[i];
    }
    float medii = suma/9;
    e->medie = medii;
    // printf("%f ", e->medie);
    
}
void citire( elev *e){
    scanf("%s", e->nume);
    scanf("%s", e->cod);
    // int size =1;
    // e->cod = malloc(size*sizeof(struct Elev));
    // int c;
    // while((c=getchar())!='\n'){
    //     e->cod[size] =c;
    //     size++;
    //     e->cod=realloc(e->cod,size*sizeof(struct Elev));
    // }
    // e->size = size;
    for(int i=0; i<9; i++){
        scanf("%i", &e->note[i]);
    }
    
}
void afisare(elev *e){
    printf("%s\n", e->nume);
    printf("%s\n", e->cod);
    for(int i=0; i<9; i++){
        printf("%i ", e->note[i]);
    }
    printf("\n");
}
void sortare(elev *e){
    
    for(int i=0; i<9; i++){
        for(int j=0; j< 9; j++){
            if(e->note[i]>e->note[j]){
                int aux = e->note[i];
                e->note[i] = e->note[j];
                e->note[j]=aux;
            }
        }
    }
}

int main(){
    int n;
    scanf("%i", &n);
    elev *e = malloc(n*sizeof(struct Elev));
    for(int i=0; i<n; i++){
        citire(e+i);
    }
    
    int test;
    scanf("%i", &test);
   
    switch(test){
        case 1 : {
            for(int i=0;i <n; i++){
                afisare(e+i);
            }
            break;
        }
        case 2 : {
            for(int i=0; i<n; i++){
                medie(e+i);
            }
            float aux=0;
            int index = -1;
            for(int i=0; i<n; i++){
                if((e+i)->medie > aux){
                    aux = (e+i)->medie;
                    index = i;
                }
            }
            printf("%s\n",(e+index)->nume);
            break;
        }
        case 3 : {
            for(int i=0; i<n; i++){
                medie(e+i);
            }
            for(int i=0; i<n; i++){
                // printf("%.2f ",(e+i)->medie);
                if((e+i)->medie<6){
                  printf("%s\n",(e+i)->nume);  
                }
            }
            break;
        }
        case 4 : {
            for(int i=0; i<n; i++){
                medie(e+i);
            }
            
            char  cod_n[20];
            scanf("%s", cod_n);
            
            for(int i=0; i<n; i++){
                if(strcmp(cod_n, (e+i)->cod)==0){
                    sortare(e+i);
                    printf("%i", (e+i)->note[5]);
                }
            }
            break;
        }
    }
    
    return 0;
}
