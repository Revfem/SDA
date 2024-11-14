#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD{
    int cod;
    char stare;
    struct NOD * next;
};
struct NOD * citire(struct NOD *head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    scanf("%i", &nou->cod);
    nou->stare = 'n';
    nou->next= NULL;
    if(head==NULL){
        head=nou;
        return head;
    }
    struct NOD  * current = head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next= nou;
    return head;
}
void afisare(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%i ", current->cod);
        current = current->next;
    }
}
void proces(struct NOD * head, char *instructiuni) {
    struct NOD * current = head;
    for(int i=0; i<strlen(instructiuni) && current!=NULL; i++){
        if(instructiuni[i]=='r'){
            current->stare='r';
            current = current->next;
        }
    } // le face receptionate;
    current = head;
    for(int i=0; i<strlen(instructiuni) && current!=NULL; i++){
        if(instructiuni[i]=='p' && current->stare=='r'){
            current->stare='p';
            current = current->next;
        }
    }
    current = head;
    for(int i=0; i<strlen(instructiuni) && current!=NULL; i++){
        if(instructiuni[i]=='l' && current->stare=='p'){
            current->stare='l';
            current=current->next;
        }
    }
    current = head;
    while(current!=NULL){
        if(current->stare == 'n'){
            printf("%i ", current->cod);
        }
        current=current->next;
    }
    printf("\n");
    current = head;
    while(current!=NULL){
        if(current->stare == 'r'){
            printf("%i ", current->cod);
        }
        current=current->next;
    }
    printf("\n");
    current = head;
    while(current!=NULL){
        if(current->stare == 'p'){
            printf("%i ", current->cod);
        }
        current=current->next;
    }
    printf("\n");
    current = head;
    while(current!=NULL){
        if(current->stare == 'l'){
            printf("%i ", current->cod);
        }
        current=current->next;
    }
    printf("\n");
}
int main(){
    int n;
    scanf("%i",&n);
    struct NOD *fabrica = NULL;
    for(int i=0; i<n; i++){
        fabrica = citire(fabrica);
    }
    char instructiuni[30];
    scanf("%s", instructiuni);
    proces(fabrica,instructiuni);
    // printf("%i", strlen(instructiuni));
    // afisare(fabrica);
    return 0;
}
