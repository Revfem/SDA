#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD {
    char nume[15];
    int nr;
    int check;
    struct NOD * next;
};
struct NOD * adauga( struct NOD * head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    scanf("%s %i", nou->nume, &nou->nr);
    nou->next=NULL;
    nou->check=0;
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
void afisare(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        printf("%s %i \n", current->nume,current->nr);
        current=current->next;
    }
}
void echipe(struct NOD * head, int dim){
    struct NOD * current = head;
    while(dim>=3){
        current = head;
        struct NOD* team[3]={NULL,NULL,NULL};
        while(current!=NULL){
            if(team[0]==NULL && current->nr == 1 && current->check==0){
                current->check =1;
                team[0]=current;
                dim--;
            }
            else if(team[1]==NULL && current->nr == 2 && current->check==0){
                current->check =1;
                team[1]=current;
                dim--;
            }
            else if(team[2]==NULL && current->nr == 3 && current->check==0){
                current->check =1;
                team[2]=current;
                dim--;
            }
            current=current->next;
        }
        if( team[0]!=NULL && team[1]!=NULL && team[2]!=NULL){
            printf("%s %s %s\n",  team[0]->nume, team[1]->nume, team[2]->nume);
        }
    }
    
}
int main(){
    struct NOD *  coada = NULL;
    int dim =0;
    while(1){
        coada = adauga(coada);
        if(getchar() == EOF){
            break;
        }
        dim++;
    }
    // printf("%i", dim);
    echipe(coada,dim);
    // afisare(coada);
    return 0;
}
