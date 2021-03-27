#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
using namespace std;
const char *nombre_archivo = "palabras.dat";

struct Palabras{
    char palabra[100];
    char traduccion[100];
    char funcionalidad[100];
};

void menu();
void ingresar_palabra();
void abrir_registro();
void ver_palabras();
void eliminar_palabra();
void modificar_palabra();
bool buscar_palabra(string);

int main(){
	menu();    
}

void menu(){
	
		int op;
	do{
		system("cls");
		system("color f0");
		cout<<"\n\t\t***MENU***\n\n";
		cout<<"\t1. Agregar palabra\n";
		cout<<"\t2. Mostrar Palabras\n";
		cout<<"\t3. Eliminar palabra\n";
		cout<<"\t4. Actualizar palabra\n";
		cout<<"\t5. Menu Principal\n";
		cout<<"\t6. Salir\n"<<endl;
		cout<<"\tSeleccione una opcion: ";
		cin>>op;
        //op=getch();
        //cout<<op<<endl<<"\t";
        system("pause");
	}while((op<1)||(op>5));
	
        switch(op){
			case 1: ingresar_palabra(); break;
			case 2: abrir_registro(); getch(); break;
			case 3: eliminar_palabra(); break;
			case 4: modificar_palabra(); break;
			case 5: system("main.exe"); break;
			case 6: exit(1); break;
			default: cout<<"\n\t\t\t OPCION INVALIDA\n"; getch();
		}
		
    return menu();
}
void ingresar_palabra(){
	char continuar;
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "a");
    Palabras pal;
    string aux;
    do{
        fflush(stdin);
        cout<<"INGRESE PALABRA: ";
        getline(cin,aux);
        if(buscar_palabra(aux)){
            cout<<"PALABRA YA INGRESADA";
            fclose(archivo);
            cin.ignore();
            return;
        }
        strcpy(pal.palabra, aux.c_str());
        cout<<"INGRESE TRADUCCION: ";
        getline(cin,aux);
        strcpy(pal.traduccion, aux.c_str());
        fflush(stdin);
        cout<<"INGRESE FUNCIONALIDAD: ";
        getline(cin,aux);
        strcpy(pal.funcionalidad, aux.c_str());
        fwrite( &pal, sizeof(Palabras), 1, archivo );
        cout<<"\nDESEA AGREGAR OTRA PALABRA s/n: ";
        cin>>continuar;
    } while((continuar=='s') || (continuar=='S') );
    cout<<"REGISTROS INGRESADOS EXITOSAMENTE";
    fclose(archivo);
    cin.ignore();
}

void abrir_registro(){
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	Palabras pal;
	fread ( &pal, sizeof(Palabras), 1, archivo );
	cout<<"_____________________________________________________"<<endl;
	cout << "PALABRA TRADUCCION, FUNCIONALIDAD"<<endl;

	while (feof( archivo ) == 0){
		cout<<"_____________________________________________________"<<endl;
		cout << pal.palabra <<endl<<pal.traduccion<<endl;
		cout<<pal.funcionalidad<<endl;
		fread ( &pal, sizeof(Palabras), 1, archivo );
	}
    cout<<"_____________________________________________________"<<endl;
    cout<<endl;
	fclose(archivo);
}

void ver_palabras(){
    system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	Palabras pal;
	fread ( &pal, sizeof(Palabras), 1, archivo );
	cout<<"__________________"<<endl;
	cout <<"| -- PALABRA -- |"<<endl;
	while (feof( archivo ) == 0){
		cout<<"__________________"<<endl;
		cout << pal.palabra <<endl;
		fread ( &pal, sizeof(Palabras), 1, archivo );
	}
    cout<<"__________________"<<endl;
    cout<<endl;
	fclose(archivo);
}

void eliminar_palabra(){
    ver_palabras();
    bool enco;
    string palabra_elimina;
    cout<<"\nIngresa funcion a eliminar:"<<endl;
    fflush(stdin);
    getline(cin,palabra_elimina);
    if(!buscar_palabra(palabra_elimina)){
        cout<<"Palabra no encontrada";
        cin.ignore();
        return;
    }
    FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* archivo2 = fopen("auxi.dat", "a+b");
    Palabras pal;
    fread ( &pal, sizeof(Palabras), 1, archivo );
	while (feof( archivo ) == 0){
    if (palabra_elimina==pal.palabra){
        cout<<"Registro Eliminado"<<endl;
        cout<<endl;
    } else
        fwrite( &pal, sizeof(Palabras), 1, archivo2 );
    fread ( &pal, sizeof(Palabras), 1, archivo );
    }
    fclose(archivo);
    fclose(archivo2);
    remove("palabras.dat");
    rename("auxi.dat","palabras.dat");
    getch();
}

void modificar_palabra(){
    ver_palabras();
    fflush(stdin);
    string comp;
    cout<<"\n\nIngrese Palabra: ";
    fflush(stdin);
    getline(cin,comp);
    
	if(!buscar_palabra(comp)){
        cout<<"Palabra no encontrada";
        cin.ignore();
        return modificar_palabra();
    }
    
    bool res=0;
    FILE* archivo = fopen(nombre_archivo,"rb");
    int pos=0;
    Palabras pal;
	fread ( &pal, sizeof(Palabras), 1, archivo );
	while (!feof( archivo )){
	    if(!strcmp(pal.palabra,comp.c_str())){
            res=1;
            break;
        }
        pos+=1;
        fread ( &pal, sizeof(Palabras), 1, archivo );
	}
    fclose(archivo);
	if(res=0){
        cout<<"Palabra no encontrada";
        cin.ignore();
        return;
	}
    Palabras palm;
	archivo = fopen(nombre_archivo,"rb");
    fseek ( archivo,pos * sizeof(Palabras), SEEK_SET );
    fread ( &palm, sizeof( Palabras ), 1, archivo );
    int camp;
	fclose(archivo);
    cout<<"\n1. Palabra: "<<palm.palabra<<endl;
    cout<<"2. Traduccion: "<<palm.traduccion<<endl;
    cout<<"3. Funcionalidad: "<<palm.funcionalidad<<endl;
	cout<<"\nIngrese Campo a Modificar: ";
	cin>>camp;
	cin.ignore();
	string aux;
	switch(camp){
		case 1:{
			cout<<"\nIngrese la Palabra: ";
			getline(cin,aux);
            if(!buscar_palabra(aux)){
                cout<<"PALABRA YA INGRESADA";
                cin.ignore();
                return;
            }
        	strcpy(palm.palabra,aux.c_str());
			break;
		}
		case 2:{
			cout<<"\nIngrese la Traduccion: ";
			getline(cin,aux);
        	strcpy(palm.traduccion,aux.c_str());
			break;
		}
		case 3:{
			cout<<"\nIngrese la Funcionalidad: ";
			getline(cin,aux);
        	strcpy(palm.funcionalidad,aux.c_str());
			break;
		}
		default:{
			cout<<"\n  Ingrese un numero valido\n\n   ";
			cin.ignore();
			return modificar_palabra();
		break;
		}
	}
	archivo = fopen(nombre_archivo, "rb");
	FILE* archivo2 = fopen("auxi.dat", "a+b");
	int registro=0;
	fread ( &pal, sizeof(Palabras), 1, archivo );
	while (feof( archivo ) == 0){
		if(registro==pos){
       		fwrite( &palm, sizeof(Palabras), 1, archivo2 );
            cout<<"Registro Modificado"<<endl;
		}
       	else
            fwrite( &pal, sizeof(Palabras), 1, archivo2 );
		fread ( &pal, sizeof(Palabras), 1, archivo );
		registro += 1;
	}
	fclose(archivo2);
	fclose(archivo);
	remove("palabras.dat");
	rename("auxi.dat","palabras.dat");
	getch();
}
bool buscar_palabra(string aux){
    bool res=0;
    FILE* archivo = fopen(nombre_archivo,"rb");
    Palabras pal;
	fread ( &pal, sizeof(Palabras), 1, archivo );
	while (!feof( archivo )){
	    if(!strcmp(pal.palabra,aux.c_str())){
            res=1;
            break;
        }
        fread ( &pal, sizeof(Palabras), 1, archivo );
	}
    fclose(archivo);
	return res;
}
