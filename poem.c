#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD{
    char *strofa[4];
    struct NOD * next;
};

struct NOD * citire(struct NOD * head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    int c;
    for(int i=0; i<4; i++){
        int j =0;
        nou->strofa[i] = malloc((j+1)*sizeof(char));
        while((c=getchar())!='\n'){
            nou->strofa[i][j]=c;
            j++;
            nou->strofa[i] = realloc(nou->strofa[i],(j+1)*sizeof(char));
        }
        nou->strofa[i][j]='\0';
    }
    nou->next = NULL;
    if(head== NULL){
        head = nou;
        return head;
    }
    struct NOD * current =head;
    while(current->next!=NULL){
        current=current->next;
    }
    current->next=nou;
    return head;
}
void afisare(struct NOD * head){
    struct NOD * current = head;
    while(current!=NULL){
        for(int i=0; i<4; i++){
            printf("%s\n", current->strofa[i]);
        }
        printf("\n");
        current=current->next;
    }
}
void rima(struct NOD * head){
    struct NOD * current = head;
    char A[3];
    char B[3];
    int dimA= strlen(current->strofa[0]);
    int dimB=strlen(current->strofa[1]);
    int check = -2;
    A[0]=current->strofa[0][dimA-2];
    A[1]=current->strofa[0][dimA-1];
    A[2]='\0';
    //  printf("%s",A);
    B[0]=current->strofa[1][dimB-2];
    B[1]=current->strofa[1][dimB-1];
    B[2]='\0';
    //  printf("%s",B);
    dimB=strlen(current->strofa[2]);
    if(current->strofa[2][dimB-2]==B[0] && current->strofa[2][dimB-1]==B[1]){
        check++;
    }
    dimA=strlen(current->strofa[3]);
    if(current->strofa[3][dimA-2]==A[0] && current->strofa[3][dimA-1]==A[1]){
        check++;
    }
    if(check==0){
        printf("%s-%s-%s-%s\n",A,B,B,A);
    }
    else{
        printf("nu\n");
    }
}
void rima_frecventa(struct NOD* head, int nr_strofe){
    struct NOD * current = head;
    char rima[3];
    char ri[3];
    for(int i=0; i<nr_strofe; i++){
        for(int j=0; j<4; j++){
            int dim = strlen(current->strofa[j]);
            rima[0]=current->strofa[j][dim-2];
            rima[1]=current->strofa[j][dim-1];
            rima[2]='\0';
            struct NOD * temp = head;
            int check = 0;
            int aux = 0;
            
            // printf("%s\n", rima);
            while(temp!=NULL){
                for(int k=0; k<4;k++){
                    int dimK=strlen(current->strofa[k]);
                    if(rima[0]==temp->strofa[k][dimK-2] && rima[1]==temp->strofa[k][dimK-1]){
                        check++;
                    }
                }
                temp = temp->next;
            }
            if(check>aux){
                aux = check;
                strcpy(ri,rima);
            }
        }
        current=current->next;
    }
    printf("%s", ri);
}
struct NOD *  inversare(struct NOD * head){
    struct NOD * current = head;
    struct NOD * prev = NULL;
    struct NOD * next = NULL;
    while(current!=NULL){
        next = current->next;
        current->next = prev;
        prev= current;
        current = next;
    }
    head = prev;
    return head;
}
int main(){
    struct NOD * poezie = NULL;
    int n;
    scanf("%i", &n);
    getchar();
    for(int i=0; i<n; i++){
        poezie = citire(poezie);
    }
    int test;
    scanf("%i",&test);
    // printf("%i",test);
    switch(test){
        case 1:
            afisare(poezie);
            break;
        case 2:
            rima(poezie);
            break;
        case 3:
            poezie = inversare(poezie);
            afisare(poezie);
            break;
        case 4:
            rima_frecventa(poezie,n);
            break;
    }
    return 0;
}
