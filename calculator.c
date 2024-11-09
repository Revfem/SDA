#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NOD {
    int cifra;
    struct NOD * next;
};
struct NOD * citire(struct NOD *head){
    struct NOD * nou = malloc(sizeof(struct NOD));
    scanf("%i", &nou->cifra);
    nou->next = NULL;
    if(head==NULL){
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
        printf("%i\n", current->cifra);
        current = current->next;
    }
}
void adunare(struct NOD * head){
    struct NOD * current = head;
    int S=0;
    while(current!= NULL){
        S+= current->cifra;
        current = current->next;
    }
    printf("%i\n", S);
}
void scadere(struct NOD * head){
    struct NOD * current = head;
    int S = current->cifra - current->next->cifra;
    printf("%i\n", S);
}
void palindrom(struct NOD * head){
    struct NOD * current = head;
    int S =  current->cifra + current->next->cifra;
    int n = S;
    int invers= 0;
    while(n!=0){
        int cifra = n%10;
        invers = invers *10+ cifra;
        n=n/10;
    }
    if(invers== S){
        printf("da\n");
    }
    else{
        printf("nu\n");
    }
}
int main(){
    struct NOD * cifre = NULL;
    cifre = citire(cifre);
    cifre= citire(cifre);
    int test;
    scanf("%i", &test);
    switch(test){
        case 1 :
            afisare(cifre);
            break;
        case 2 :
            adunare(cifre);
            break;
        case 3 :
            scadere(cifre);
            break;
        case 4 :
            palindrom(cifre);
            break;
    }
    return 0;
}
