#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
void fase1();
main(){
    char op[3];
    do{
        system("cls");
        cout<<"\n\n\n\n\t\t\t       MENU";
        cout<<"\n\n\t\t        1. Fase 1";
        cout<<"\n\t\t        2. Fase 2";
        cout<<"\n\t\t        0. Salir ";
        cout<<"\n\n              Ingrese opcion: ";
        fflush(stdin);
        cin>>op;
        if(strlen(op)>2 || atoi(op)>2 || atoi(op)<0)
            op[0]='f';
        for(int i=0;i<strlen(op);i++){
            if(!isdigit(op[i]))
                op[0]='f';
        }
        switch(op[0]){
            case '1':{
                system("fase1.exe");
                break;
            }
            case '2':{
                system("cls");
                system("fase2.exe");
                break;
            }
            case '0':
                break;
            default:{
                printf("\n\n\tOPCION INVALIDA!\n\n\t");
                system("pause");
                break;
            }
        }
    }while(op[0]!='0');
}



