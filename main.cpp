/*
Aplicación para armar torneos de fútbol. 
Integrantes:

Karen Cano
José Cullen
Melisa Cruz Martínez
Soledad Ferrari 
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

char NOMBRE_ARCHIVO [20] = "EquiposDeFutbol.bin";
const int NOT_FOUND = -1;
const int MAX_EQUIPOS = 100;
FILE *archivo;


struct Equipo{
	char id [4];
	char nombre[32];
	int potenciaAtaque;
	int potenciaDefensa;
};

void MostrarMenu(bool permiteSalir);
void AgregarEquipo();
void ListarEquipos();
void EjecutarOpcion(int opcion);
int PedirOpcion(int opciones, bool permiteSalir);
int CantidadEquipos();
int PosicionDelEquipoEnArchivo(char id[4]);
void EliminarEquipo();
void SetearListaDeEquipos(Equipo equipos []);
void ReescribirArchivo(Equipo equipos[], int tamanio);
void AgregarEquipoAlArchivo(Equipo equipo);
Equipo CrearEquipo(bool permiteNuevo);


int main(int argc, char** argv) {
	int numero;
	
	archivo = fopen(NOMBRE_ARCHIVO,"ab");
	fclose(archivo);
	
	MostrarMenu(true);	
	return 0;
}


/*
	Muestra el menú principal
	permiteSalir	booleano que indica si debe mostrar dicha opción.
*/
void MostrarMenu(bool permiteSalir){
	cout<<"Bienvenido al Equipos de Futbol"<<endl<<endl;
	cout<<"1- Agregar Equipo."<<endl;
	cout<<"2- Eliminar Equipo."<<endl;
	cout<<"3- Ver Equipos."<<endl;

	if(permiteSalir){
		cout<<"0- Salir."<<endl;	
	}	
	EjecutarOpcion(PedirOpcion(3, permiteSalir));
}

/* 
	Pide una opción, validando que sea correcta. 
	return opción elegida
*/
int PedirOpcion(int opciones, bool permiteSalir){
	int opcion = NOT_FOUND;
	while(opcion < 0){
		cout<<"Ingrese la opción deseada: ";
		cin>>opcion;
		if( (opcion == 0 && !permiteSalir) || opcion < 0 || opcion > opciones ){
			cout<<"La opción ingresada no es válida"<<endl;
			opcion = NOT_FOUND;
		}
	}
	return opcion;
}

/*
	Ejecuta la opción elegida. 
*/
void EjecutarOpcion(int opcion){
	switch(opcion){
		case 1:
			AgregarEquipo();
			MostrarMenu(false);			
			break;
		case 2:
			EliminarEquipo();
			MostrarMenu(false);			
				break;
		case 3:
			ListarEquipos();
			MostrarMenu(false);
			break;				
	}
}


/*
	Imprime en pantalla la lista de los equipos anotados (en el archivo).
*/
void ListarEquipos(){
	if(CantidadEquipos() == 0){
		cout<<"No existen equipos anotados";
	}else{
		archivo = fopen(NOMBRE_ARCHIVO,"rb");
		Equipo equipo;
		cout<<"Lista de Equipos:"<<endl;
		cout << left << setw (5) << "Id" << setw (33) << "Nombre" << setw (18) << "(Ataque - Defensa)" << endl;
		fread(&equipo, sizeof(equipo), 1, archivo);
		while(!feof(archivo)){
			cout << left << setw (5) << equipo.id << setw (33) << equipo.nombre << "("<< equipo.potenciaAtaque<<" - "<<equipo.potenciaDefensa<<")"<< endl ;
			fread(&equipo, sizeof(equipo), 1, archivo);
		}
		fclose(archivo);
	}
}

Equipo CrearEquipo(bool permiteNuevo){
	int pos = NOT_FOUND;
	char modificarEquipo;	
	Equipo equipo;

	// Si el id existe, pregunta si desea modificar, si no te permite cargar un nuevo id
	do{
		cout<<"Ingrese identificador: ";
		cin>>equipo.id;
		pos = PosicionDelEquipoEnArchivo(equipo.id);
		if(pos > NOT_FOUND){
			cout<<"El equipo ya se encuentra ingresado. ¿Desea modificarlo? (s/n)";
			cin>>modificarEquipo;
		}		
	} while(pos > NOT_FOUND && modificarEquipo == 'n');
	
	if(pos > NOT_FOUND && !permiteNuevo){
		cout<<"Ha alcanzado el límite máximo de equipos. Para ingresar más, deberá eliminar alguno. ";
	}
	
	cout<<"Ingrese nombre: ";
	cin>>equipo.nombre;
	cout<<"Ingrese potencia en ataque: ";
	cin>>equipo.potenciaAtaque;
	cout<<"Ingrese potencia en defensa: ";
	cin>>equipo.potenciaDefensa;
	return equipo;
}

void AgregarEquipoAlArchivo(Equipo equipo){
	archivo = fopen(NOMBRE_ARCHIVO,"ab");
	fseek(archivo, 0L, SEEK_END);
	fwrite(&equipo, sizeof(Equipo), 1, archivo);
	cout<<"Equipo agregado con éxito"<<endl;
	fclose(archivo);
}

void ReescribirArchivo(Equipo equipos[], int tamanio){
	archivo = fopen(NOMBRE_ARCHIVO, "wb");	
	fwrite(&equipos, sizeof(Equipo), tamanio, archivo);	
	fclose(archivo);
}

/*
	Agrega o modifica un equipo.
*/
void AgregarEquipo(){
	Equipo equipo = CrearEquipo(CantidadEquipos() < 100);
	int pos = PosicionDelEquipoEnArchivo(equipo.id);	
	if(pos < 0){
		AgregarEquipoAlArchivo(equipo);	
	}else{			
		int tamanio = CantidadEquipos();
		Equipo equipos[tamanio];
		SetearListaDeEquipos(equipos);
		equipos[pos] = equipo;		
		
		archivo = fopen(NOMBRE_ARCHIVO, "wb");	
		fwrite(&equipos, sizeof(Equipo), tamanio, archivo);	
		fclose(archivo);
		//ReescribirArchivo(equipos, tamanio);
	}	
}

/*
	return	cantidad de equipos inscriptos (en el archivo).
*/
int CantidadEquipos(){
	archivo = fopen(NOMBRE_ARCHIVO,"rb");
	Equipo equipo;
	fread(&equipo, sizeof(equipo), 1, archivo);
	int count = 0;
	while(!feof(archivo)){
		count++;		
		fread(&equipo, sizeof(equipo), 1, archivo);		
	}
	fclose(archivo);	
	return count;
}

/*
	Busca el id del equipo en el archivo. 
	return	posición del equipo en el archivo
			si no existe, devuelve -1
*/
int PosicionDelEquipoEnArchivo(char id[4]){
	archivo = fopen(NOMBRE_ARCHIVO,"rb");
	Equipo equipo;
	fread(&equipo, sizeof(equipo), 1, archivo);
	int count = NOT_FOUND;
	bool found = false;
	while(!feof(archivo) && !found){
		count++;		
		if(strcmp(equipo.id, id) == 0){
			found = true;
		}
		fread(&equipo, sizeof(equipo), 1, archivo);		
	}
	fclose(archivo);
	if(!found){
		count = NOT_FOUND;
	}	
	return count;
}

/*
   Escribe en la lista pasada como parámetro todos los equipos del archivo.
*/
void SetearListaDeEquipos(Equipo equipos []){
	int tamanio = CantidadEquipos();
	archivo = fopen(NOMBRE_ARCHIVO,"rb");
	fseek(archivo, 0L, SEEK_SET);
	for(int i = 0; i < tamanio; i++){
		fread(equipos, sizeof(Equipo), tamanio, archivo);			
	}
	fclose(archivo);	
}


/*
	Elimina equipo
*/
void EliminarEquipo(){
	char id[4];
	int pos;
	int tamanio = CantidadEquipos();
	Equipo equipos [tamanio];
	Equipo equiposResult [tamanio-1];

	SetearListaDeEquipos(equipos);
	
	cout<<"Ingrese el ID del equipo que desea eliminar: ";
	cin>>id;
	pos = PosicionDelEquipoEnArchivo(id);	
	
	if(pos == NOT_FOUND){
		cout<<"El Equipo no existe."<<endl ;
	}else{
		// regeneramos la lista, sin el equipo a eliminar.
		int j = 0;
		for(int i = 0; i < tamanio; i++ ){
			if(i != pos){
				equiposResult[j] = equipos[i];
				j += 1;
			}		
		}
		tamanio--; // hay un equipo menos de la lista original.
		archivo = fopen(NOMBRE_ARCHIVO, "wb");
		fwrite(equiposResult, sizeof(Equipo), tamanio, archivo);	
		fclose(archivo);	
	}
	
	
}


