#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Student{
    int *note;
    char nume[30];
    int check;
    int max_grade;
}student;

void citire(student *s, int nr){
    s->note=(int*)malloc(nr*sizeof(int));
    s->check =0;
    scanf("%s", s->nume);
    for(int i=0; i<nr; i++){
        scanf("%i", &s->note[i]);
    }
   
}
void afisare(student *s, int nr){
    printf("%s", s->nume);
    for(int i=0; i<nr; i++){
        printf(" %i", s->note[i]);
    }
}
void check_integralist(student *s, int nr){
    s->check=0;
    for(int i=0; i<nr; i++){
        if(s->note[i]<5){
            s->check = 1;
        }
    }
}
void nota_max(student *s, int nr){
    int aux = 0;
    for(int i=0; i<nr; i++){
        if(s->note[i]>aux){
            aux = s->note[i];
        }
    }
    s->max_grade = aux;
}
void swap( student *a, student *b){
    student temp = *a;
    *a=*b;
    *b=temp;
}

int main(){
    int n, nr,test;
    scanf("%i %i", &n, &nr);
    student *s = malloc(n*sizeof(struct Student));
    // printf("%i %i",n,nr);
    for(int i=0; i<n; i++){
        citire(s+i,nr);
    }
    
    scanf("%i", &test);
    // printf("%i", test);
    switch(test){
        case 1:{
           for(int i=0; i<n; i++){
                afisare(s+i, nr);
                 printf("\n");
            }
            break;
        }
        case 2:{
        
            for(int i=0; i<n; i++){
                check_integralist(s+i, nr);
                nota_max(s+i,nr);
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if( (s+j)->check ==0 && (s+j+1)->check ==0){
                        if( (s+j)->max_grade < (s+j+1)->max_grade){
                            swap(s+j,s+j+1);
                        }
                    }
                }
            }
            for(int i=0; i<n; i++){
                if((s+i)->check ==0){
                    printf("%s ", (s+i)->nume);
                    printf("%i\n", (s+i)->max_grade);
                }
            }
            
            
            
            break;
        }
    }
    return 0;
}
