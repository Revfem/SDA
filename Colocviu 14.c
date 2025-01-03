#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NOD  {
    char nume[30];
    int data[3];
    struct NOD * next;
}nod;

unsigned int hash_key ( const char * nume, int n ){ // unsigned este pt a asigura ca ramane pozitiv numarul neaparat!! (la sume prea mari poate devine negativ)
    unsigned int suma = 0;
    while(*nume){
        suma += * nume;
        nume++;
    }
    return suma % n;
}
void citeste(struct NOD ** hash, int n){
    char nume_temp[30];
    scanf("%s", nume_temp);
    int pozitie = hash_key(nume_temp,n);
    // printf("%s %i", nume_temp, data_temp[1]);
    if(hash[pozitie]== NULL){
        hash[pozitie] = malloc(sizeof(struct NOD));
        strcpy(hash[pozitie]->nume, nume_temp);
        scanf("%i %i %i", &hash[pozitie]->data[0],&hash[pozitie]->data[1],&hash[pozitie]->data[2]);
    }
    else{
        struct NOD * current =  hash[pozitie];
        while(current->next!=NULL){
            current = current->next;
        }
        struct NOD * nou = malloc(sizeof(struct NOD));
        strcpy(nou->nume, nume_temp);
        scanf("%i %i %i", &nou->data[0],&nou->data[1],&nou->data[2]);
        nou->next = NULL;
        current->next = nou;
    }
    
}
void afisare( struct NOD ** hash, int n){
    for(int i=0; i <n; i++){
        printf("Pozitia: %i\n", i);
        struct NOD * current = hash[i];
        if(current==NULL){
            printf("GOL\n");
        }
        else{
            while(current!=NULL){
                printf("%s %i %i %i\n", current->nume, current->data[0], current->data[1], current->data[2]);
                current=current->next;
            }
        }
    }
}
void verifica_varsta(struct NOD * current){
    if(2024 - current->data[0] > 17){
        printf("%s %i %i %i\n",current->nume, current->data[0], current->data[1], current->data[2]);
    }
    else if( 2024 - current->data[0] == 17 ){
        if(current->data[1] > 1){
            printf("%s %i %i %i\n",current->nume, current->data[0], current->data[1], current->data[2]);  
        }
        else if( current->data[1] == 1 && current->data[2] > 9){
            printf("%s %i %i %i\n",current->nume, current->data[0], current->data[1], current->data[2]);
        }
    }
    else{
        printf("%s Minor\n", current->nume);
    }
}
void afisare_majori(struct NOD ** hash, int n){
    for(int i = 0; i<n; i++){
        struct NOD * current = hash[i];
        if(current != NULL){
            while(current!=NULL){
                verifica_varsta(current);
                current = current->next;
            }
        }
    }
}
void sortare_caractere (char *str){
    int dim = strlen(str);
    for(int i=0; i<dim; i++){
        for(int j=i+1; j<dim ; j++){
            if(str[i] > str[j]){
                char temp = str[i];
                str[i]=str[j];
                str[j]=temp;
            }
        }
    }
} // sortez numele userului intr un format ordonat pt a le putea compara apoi
void cauta_user_similar(struct NOD ** hash, char * nume_temp, int n){
    int pozitie = hash_key(nume_temp,n);
    if(hash[pozitie]==NULL){
        printf("Nu exista useri similari\n");
        return;
    }
    
    char nume_temp_sortat[30];
    strcpy(nume_temp_sortat,nume_temp);
    sortare_caractere(nume_temp_sortat);
    int flag = 0;
    struct NOD * current = hash[pozitie];
    while(current!=NULL){
        char nume_current_sortat[30];
        strcpy(nume_current_sortat,current->nume);
        sortare_caractere(nume_current_sortat);
        
        if(strcmp(nume_current_sortat, nume_temp_sortat)==0 && strcmp(current->nume, nume_temp)!=0){
            if(flag == 1){
                printf(" %s", current->nume);
            }
            else{
               printf("%s", current->nume); 
            }
            flag =1;
        }
        
        current = current->next;
    }
   
    if(flag == 0){
        printf("Nu exista useri similari\n");
        return;
    }
     printf("\n");
     return;
}
void pozitie_optima( struct NOD ** hash, int n, int nr){
    
    int coliziuni;
    int dim_nou = n;
    struct NOD ** lista  = malloc(nr*sizeof(struct NOD *));
    int j=0;
    for(int i=0; i <n; i++){
        
        if(hash[i]!=NULL){
            struct NOD * current = hash[i];
            while(current!=NULL){
                lista[j] = current;
                current = current->next;
                j++;
            }
        }
    }
    // for(int i=0; i<nr; i++){
    //     printf("%s\n", lista[i]->nume);
    // }
    while(1){
        dim_nou++;
        int flag = 0;
        coliziuni = 0;
        struct NOD ** new_hash = malloc(dim_nou *sizeof(struct NOD*));
        for(int i=0; i< dim_nou; i++){
            new_hash[i] = NULL;
        }
        // fac un new hash, ii pun in hash, nr coliziuniile daac imi dau toate mai mici ca 2 atunci break?
        for(int i=0; i<nr; i++){
            int pozitie = hash_key(lista[i]->nume,dim_nou);
            if(new_hash[pozitie] == NULL){
                new_hash[pozitie]  = malloc(sizeof(struct NOD));
                strcpy(new_hash[pozitie]->nume, lista[i]->nume);
            }
            else{
                struct NOD * current = new_hash[pozitie];
                while(current->next!=NULL){
                    current = current->next;
                }
                struct NOD * nou = malloc(sizeof(struct NOD));
                nou->next = NULL;
                strcpy(nou->nume, lista[i]->nume);
                current->next = nou;
                
            }
        }
        // printf("dim :%i coliziuni:%i\n", dim_nou, coliziuni);
        // afisare(new_hash,dim_nou);
        // printf("\n");
        
        //calc coliziuni
        for(int i=0; i <dim_nou; i++){
            coliziuni =0;
            if(new_hash[i]!=NULL){
                struct NOD * current = new_hash[i];
                while(current!=NULL){
                    current = current->next;
                    coliziuni++;
                }
            }
            if(coliziuni > 2){
                flag = 1;
            }
        }
        
        // for(int i=0; i<dim_nou; i++){
        //     struct NOD * current  = new_hash[i];
        //         while(current!=NULL){
        //             struct NOD * temp = current;
        //             current = current->next;
        //             free(temp); 
        //         }
            
        // }
        
        // free(new_hash); primesc eroare double free, :(
        if(flag == 0){
            break;
        }
        
        
    }
    printf("%i\n", dim_nou);
    free(lista);
}
int main(){
    int n; //dimensiunea tabelului hash
    scanf("%i", &n);
    struct NOD ** hash = malloc(n*sizeof(struct NOD *)); // alocare dinamica  Fiecare pozitie din tabelul hash este un POINTER catre inceputul unei liste ( ARRAY DE POINTER LA NODURI).
    for(int i=0; i<n; i++){
        hash[i]= NULL;
    } // initializare cu NULL
    int nr;
    scanf("%i", &nr);
    
    for(int i=0; i<nr; i++){
        citeste(hash,n);
    }
    int test;
    scanf("%i", &test);
    switch(test){
        case 1:{
            // afisare(hash,n);
            afisare_majori(hash,n);
            break;
        }
        case 2:{
            for(int i=0; i<3; i++){
                char nume_temp[30];
                scanf("%s", nume_temp);
                cauta_user_similar(hash, nume_temp,n);
            }
            break;
        }
        case 3:{
            pozitie_optima(hash,n,nr);
            break;
        }
    }
    return 0;
}
