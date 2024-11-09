#include"functii.h"




int main(){
    int c;
    struct  NOD * lista_evenimente = NULL;
    do{
        scanf("%i", &c);
        getchar();
        switch(c){
            case 1:
                lista_evenimente = adaugare_eveniment(lista_evenimente);
                
                break;
            case 2:
                char ev[20];
                scanf("%s", ev);
                cautare_titlu(lista_evenimente, ev);
                break;
            case 3:
                char data[8];
                for(int i=0; i<8; i++){
                   data[i]=getchar();
                }
                data[8]='\0';
                // for(int i=0; i<8; i++){
                //     printf("%c",data[i]);
                // }
                // printf("\n");
                cautare_data(lista_evenimente,data);
                break;
            case 4:
                afisare_evenimente(lista_evenimente);
               
                break;
            case 5:
                afisare_cronologica(lista_evenimente);
                break;
            case 6:
                exit(0);
                break;
            
        }
        
    }while(1);
    
    return 0;
}
