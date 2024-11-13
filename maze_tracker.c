#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct NOD {
    char comanda;
    struct NOD *  next;
    
};
struct instructiuni {
    int coordonate[2];
    struct instructiuni * next;
};
struct NOD * citire(struct NOD *head, char c){
    struct NOD * nou = malloc(sizeof(struct NOD));
    nou->comanda = c;
    nou->next = NULL;
    if(head ==NULL){
        head = nou;
        return head;
    }
    struct NOD  * current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next=nou;
    return head;
}
void afisare(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%c\n", current->comanda);
        current= current->next;
    }
}
void parcurge(struct NOD * head, int ** matrice, int * coordonate){
    struct NOD * current = head;
    int x = coordonate[0];
    int y=coordonate[1];
    while(current!=NULL){
        if(current->comanda == 'u' && matrice[x-1][y] ==0){
           
            x--;
        }
        else if(current->comanda == 'd' & matrice[x+1][y] ==0){
            x++;
            
        }
        else if(current->comanda == 'r' && matrice[x][y+1] ==0){
            y++;
            
        }
        else if (current->comanda == 'l' && matrice [x][y-1]==0){
            y--;
            
        }
        current=current->next;
    }
    printf("%i %i", x, y);
}
struct instructiuni * noi_valori(int x,int y, struct instructiuni *head){
    struct instructiuni * nou = malloc(sizeof(struct instructiuni));
    nou->next = NULL;
    nou->coordonate[0] = x;
    nou->coordonate[1]=y;
    struct instructiuni * current = head;
    while(current->next !=NULL){
        current=current->next;
    }
    current->next=nou;
    return head;
}
struct instructiuni * cauta_iesire(int **matrice, int * coordonate, struct instructiuni * head, int dim){
    int x= coordonate[0];
    int y=coordonate[1];
    head= malloc(sizeof(struct instructiuni));
    head->next = NULL;
    head->coordonate[0] = x;
    head->coordonate[1]=y;
    matrice[x][y]=1;
    // printf("%i %i",x,y);
    struct instructiuni * current = head;
    while( x<(dim-1) && x>=0 && y>=0 && y<(dim-1)){
        if(matrice[x-1][y]!=1){
            int move = matrice[x][y];
            if(move==0){
                matrice[x][y]=1;
                x--;
            }
            else{
                while(move !=0 && matrice[x-1][y]!=1){
                    matrice[x][y]=1;
                    x--;
                }
            }
            // printf("u ");
        }
        else if(matrice[x][y+1]!=1){
           int move = matrice[x][y];
            if(move==0){
                matrice[x][y]=1;
                y++;
            }
            else{
                while(move !=0 && matrice[x][y+1]!=1){
                    matrice[x][y]=1;
                    y++;
                }
            }
            // printf("r ");
        }
        else if(matrice[x+1][y]!=1){
            int move = matrice[x][y];
            if(move==0){
                matrice[x][y]=1;
                x++;
            }
            else{
                while(move !=0 && matrice[x+1][y]!=1){
                    matrice[x][y]=1;
                   x++;
                }
            }
            // printf("d ");
        }
        else if(matrice[x][y-1]!=1){
           int move = matrice[x][y];
            if(move==0){
                matrice[x][y]=1;
                y--;
            }
            else{
                while(move !=0 && matrice[x][y-1]!=1){
                    matrice[x][y]=1;
                    y--;
                }
            }
            // printf("l ");
        }
        else{
            break;
        }
        
        // printf("%i %i\n", x, y);
        head = noi_valori(x,y,head);
    }
    return head;
}
struct instructiuni * inversare(struct instructiuni * head){
    struct  instructiuni  * current= head;
    struct instructiuni * prev = NULL;
    struct instructiuni * next = NULL;
    while(current!=NULL){
      
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
    }
    head = prev;
    return head;
}
void afisare_drum (struct  instructiuni* head){
    struct instructiuni * current = head;
    while(current!=NULL){
        printf("%i %i\n", current->coordonate[0], current->coordonate[1]);
        current = current->next;
    }
    
}
int main(){
    int n;
    scanf("%i", &n);
    struct NOD * instructiuni = NULL;
    int **matrice = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        matrice[i] = (int*)malloc(n*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%i", &matrice[i][j]);
        }
    }
    //  for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++){
    //         printf("%i ", matrice[i][j]);
    //     }
    //     printf("\n");
    // }
    int plecare[2];
    scanf("%i %i",&plecare[0],&plecare[1]);
    int test;
    scanf("%i", &test);
   
    // printf("%i",test);
  
    switch(test){
        case 1:
            int c;
            while((c=getchar())!=EOF){
                if(c=='\n'){
                    continue;
                }
                instructiuni=citire(instructiuni,c);
            }
            afisare(instructiuni);
            break;
          
        case 2:
           
            while((c=getchar())!=EOF){
                if(c=='\n'){
                    continue;
                }
                instructiuni=citire(instructiuni,c);
            }
            parcurge(instructiuni, matrice, plecare);
           
            break;
        case 3:
            struct instructiuni * ins = NULL;
            ins = cauta_iesire(matrice, plecare,ins,n);
            ins = inversare(ins);
            afisare_drum(ins);
            break;
        case 4:
            ins = cauta_iesire(matrice,plecare,ins,n);
            afisare_drum(ins);
           
            break;
    }
    return 0;
}
