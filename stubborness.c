#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct NOD{
    char comanda[20];
    struct NOD  * next ;
};
struct NOD * citire(struct NOD * head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    scanf("%s", nou->comanda);
    // printf("%s ", nou->comanda);
    nou->next = NULL;
    if(head==NULL){
        head=nou;
        return head;
    }
    struct NOD * current = head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next=nou;
    return head;
}
void afisare(struct NOD * head,int x, int y, int obsx, int obsy, int m, int n){
    struct NOD * current=head;
    int xa =x;
    int ya=y;
    if(head == NULL){
        printf("Lista goala\n");
    }
    // printf("afisare inainte: %i %i ", x,y);
    while(current!=NULL){
        if(strcmp(current->comanda,"dreapta") ==0 &&(ya+1)<n ){
            if((ya+1)==obsy && xa==obsx){
                break;
            }
            printf("%s\n", current->comanda);
            ya++;
        }
        else if(strcmp(current->comanda,"stanga") ==0 && (ya-1)>=0 ){
            if((ya-1)==obsy && xa==obsx){
                break;
            }
            printf("%s\n", current->comanda);
            ya--;
        }
        else if(strcmp(current->comanda,"sus") ==0 && (xa-1)>=0 ){
            if(ya==obsy && (xa-1)==obsx){
                break;
            }
            printf("%s\n", current->comanda);
            xa--;
        }
        else if(strcmp(current->comanda,"jos") ==0 && (xa+1)<m){
            if(ya==obsy && (xa+1)==obsx){
                break;
            }
            printf("%s\n", current->comanda);
            xa++;
        }
        current = current->next;
    }
// printf("afisare: %i %i %i %i", x,y, xa,ya);
}
struct NOD * inversare( struct NOD * head){
    struct NOD * prev = NULL;
    struct NOD * current = head;
    struct NOD * next = NULL;
    while(current!=NULL){
        next = current->next;
        current->next=prev;
        prev=current;
        current = next;
    }
    head = prev;
    return head;
}
struct NOD * afisare_drum(struct NOD * head, int *x, int *y, int obsx,int obsy,int m,int n){
    struct NOD * current = head;
    while(current!=NULL){
        if(strcmp(current->comanda,"dreapta") ==0 &&(*y+1)<n ){
            if((*y+1)==obsy && *x==obsx){
                break;
            }
            (*y)++;
        }
        else if(strcmp(current->comanda,"stanga") ==0 && (y-1)>=0 ){
            if((*y-1)==obsy && *x==obsx){
                break;
            }
            (*y)--;
        }
        else if(strcmp(current->comanda,"sus") ==0 && (x-1)>=0 ){
            if(*y==obsy && (*x-1)==obsx){
                break;
            }
            (*x)--;
        }
        else if(strcmp(current->comanda,"jos") ==0 && (*x+1)<m){
            if(*y==obsy && (*x+1)==obsx){
                break;
            }
            (*x)++;
        }
        current = current->next;
    } // am x si y in poz finala
    // printf("pozitie finala x y : %i %i", x,y);
    current = head;
    while(current!=NULL){
        if(strcmp(current->comanda,"dreapta") ==0){
            strcpy(current->comanda,"stanga");
        }
        else if(strcmp(current->comanda,"stanga")==0){
            
            strcpy(current->comanda,"dreapta");
         
        }
        else if(strcmp(current->comanda,"sus")==0){
            
            strcpy(current->comanda,"jos");
            
        }
        else if(strcmp(current->comanda,"jos")==0){
            
            strcpy(current->comanda,"sus");
           
        }
        current = current->next;
    }
    return head;
}
void calc_drum(struct NOD * head, int x,int y,int m, int n,int obsx,int obsy){
    struct NOD * current = head;
    while(current!=NULL){
        if(strcmp(current->comanda,"dreapta") ==0 &&(y+1)<n ){
            if((y+1)==obsy && x==obsx){
                break;
            }
            y++;
        }
        else if(strcmp(current->comanda,"stanga") ==0 && (y-1)>=0 ){
            if((y-1)==obsy && x==obsx){
                break;
            }
            y--;
        }
        else if(strcmp(current->comanda,"sus") ==0 && (x-1)>=0 ){
            if(y==obsy && (x-1)==obsx){
                break;
            }
            x--;
        }
        else if(strcmp(current->comanda,"jos") ==0 && (x+1)<m){
            if(y==obsy && (x+1)==obsx){
                break;
            }
            x++;
        }
        current = current->next;
    }
    printf("%i %i\n", x,y);
}
int main(){
    int m,n,x,y;
    scanf("%i %i %i %i",&m,&n, &x,&y);
    struct NOD * instructiuni = NULL;
    int obsx= -1;
    int obsy= -1;
    do{
        int test;
        scanf("%i",&test);
        
        switch(test){
            case 1:
                instructiuni = citire(instructiuni);
                break;
            case 2:
                afisare(instructiuni,x,y,obsx,obsy,m,n);
                exit(0);
                break;
            case 3:
                instructiuni = inversare(instructiuni);
                // afisare(instructiuni);
                instructiuni = afisare_drum(instructiuni,&x,&y,obsx,obsy,m,n); // am x si y final
                // printf("%i %i", x,y);
                afisare(instructiuni,x,y,obsx,obsy,m,n);
                break;
            case 4:
                calc_drum(instructiuni, x,y,m,n, obsx,obsy);
                
                break;
            case 5:
                scanf("%i %i", &obsx,&obsy);
                
                break;
            case 6:
                exit(0);
                break;
                
        }
    }while(1);
    return 0;
}
