#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD {
    char nume[128];
    struct NOD * next;
};
struct NOD * adauga(struct NOD * head, char* volum){
    struct NOD * nou = malloc(sizeof(struct NOD));
    
    strcpy(nou->nume,volum);
    if(head==NULL){
        nou->next= NULL;
        head = nou;
        return head;
    }
    nou->next = head;
    return nou;
}
struct NOD * scoate(struct NOD * head){
    if(head==NULL){
        return NULL;
    }
    if(head->next==NULL){
        printf("%s,", head->nume);
        free(head);
        return NULL;
    }
    struct NOD * sterge_head = head;
    printf("%s,", head->nume);
    head = head->next;
    
    free(sterge_head);
    return head;
}
int main(){
    struct NOD * carti = NULL;
    int dim =1;
    int c;
    char nume[128];
    int check =0;
    while(1){
        c= getchar();
        getchar();
        // printf("%c", c);
        if(c=='+'){
            fgets(nume,sizeof(nume),stdin);
            nume[strcspn(nume, "\n")] = 0;
            carti = adauga(carti,nume);
            check = 1;
            // printf("+1");
        }
        else{
            carti=scoate(carti);
            
            // printf("-1");
        }
        if(carti == NULL && check==1){
            break;
        }
        
    }
    return 0;
}
