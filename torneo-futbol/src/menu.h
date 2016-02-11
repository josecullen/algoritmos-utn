/*
 * menu.h
 *
 *  Created on: 26 de ene. de 2016
 *      Author: jcullen
 */
//#include "includes.h"


/**
 * Se encarga de las visualizaciones.
 */
struct Menu{
	/**
	 * Muestra el menú principal
	 */
	int MenuPrincipal(){
		int opcion;

		cout<<"Bienvenido al Torneos de Futbol"<<endl<<endl;
		cout<<"Menú Principal"<<endl;
		cout<<"1- Editar Equipos."<<endl;
		cout<<"2- Simular."<<endl;
		cout<<"0- Salir."<<endl;
		cout<<"Elija una opción: ";
		cin >> opcion;
		return opcion;
	}


	int MenuEdicion(){
		system("CLS");
		int opcion;

		cout<<"Torneos de Fútbol - Edición"<<endl<<endl;
		cout<<"1- Agregar Equipo."<<endl;
		cout<<"2- Eliminar Equipo."<<endl;
		cout<<"3- Ver Equipos."<<endl;
		cout<<"0- Volver."<<endl;
		cout<<"Elija una opción: ";
		cin >> opcion;
		return opcion;
	}

	/*
	 *
	 */
	int MenuSimulacion(){
		system("CLS");
		int opcion;

		cout<<"Torneos de Fútbol - Simulación"<<endl<<endl;
		cout<<"1- Ver tabla de posiciones."<<endl;
		cout<<"2- Ver partidos por equipo."<<endl;
		cout<<"3- Ver partidos por fecha."<<endl;
		cout<<"0- Volver."<<endl;
		cout<<"Elija una opción: ";
		cin >> opcion;
		return opcion;

	}

	/*
		Imprime en pantalla la lista de los equipos anotados (en el archivo).
	*/
	void ListarEquipos(){
		system("CLS");
		Equipo equipo;
		cout <<"Lista de Equipos:"<<endl;
		cout << left << setw (5) << "Id" << setw (33) << "Nombre" << setw (18) << "(Ataque - Defensa)" << endl;
		FileIterator<Equipo> iterator = fileManager.getIterator();

		while(iterator.hasNext()){
			equipo = iterator.next();
			cout << left << setw (5)
					<< equipo.id << setw (33)
					<< equipo.nombre << "("
					<< equipo.potenciaAtaque<< " - "
					<< equipo.potenciaDefensa<< ")"<< endl ;
		}

		wait();
	}

	Equipo CrearEquipo(){
		char mustContinue = 's';
		Equipo equipo;

		do{
			cout<<"Ingrese identificador: ";
			cin>>equipo.id;

			if(fileManager.contains(equipo.id)){
				cout<<"El equipo ya se encuentra ingresado. ¿Desea modificarlo? (s/n)";
				cin>>mustContinue;
			}
		} while(mustContinue == 'n');

		cout<<"Ingrese nombre: ";
		cin>>equipo.nombre;
		cout<<"Ingrese potencia en ataque: ";
		cin>>equipo.potenciaAtaque;
		cout<<"Ingrese potencia en defensa: ";
		cin>>equipo.potenciaDefensa;

		return equipo;
	}

	void EliminarEquipo(){
		char id[4];

		cout<<"Ingrese el ID del equipo que desea eliminar: ";
		cin>>id;
		fileManager.removeById(id);

		wait();
	}


	void MostrarPartidos(List<Fecha> fechas){

		ListIterator<Fecha> fechasIt = fechas.getIterator();

		while(fechasIt.hasNext()){
			Fecha fecha = fechasIt.next();
			ListIterator<Partido> it = fecha.partidos.getIterator();

			while(it.hasNext()){
				Partido p = it.next();
				Equipo loc = p.local;
				Equipo vis = p.visitante;

				cout << left
					<< setw (5) << loc.id
					<< setw (33) << loc.nombre
					<< setw (3) << p.golesLocal << " - " <<setw (3)<< p.golesVisitante << " "
					<< setw (5) << vis.id
					<< setw (33) << vis.nombre
					<< endl;
			}

		}
	}

	void PartidosPorEquipo(List<Fecha> fechas){
		char idEquipo[4];

		cout<<"Ingrese un Equipo: ";
		cin>>idEquipo;
		cout<<"Partidos de "<<idEquipo<<endl;

		ListIterator<Fecha> fechasIt = fechas.getIterator();
		while(fechasIt.hasNext()){
			ListIterator<Partido> it = fechasIt.next().partidos.getIterator();
			while(it.hasNext()){

				Partido p = it.next();
				if(	strcmp(p.local.id, idEquipo) == 0 ||
					strcmp(p.visitante.id, idEquipo) == 0){
					this->ImprimirPartido(p);
				}
			}
		}
		wait();
	}


	void PartidosPorFecha(List<Fecha> fechas){
		int numFecha;

		cout<<"Ingrese una Fecha: ";
		cin>>numFecha;
		cout<<"Partidos de la fecha "<<numFecha<<endl;

		ListIterator<Fecha> fechasIt = fechas.getIterator();
		int count = 1;
		while(fechasIt.hasNext()){
			Fecha fecha = fechasIt.next();

			if(count++ == numFecha){
				ListIterator<Partido> it = fecha.partidos.getIterator();
				while(it.hasNext()){
					this->ImprimirPartido(it.next());
				}
			}
		}
		wait();
	}

	void TablaDePosiciones(List<Fecha> fechas){
		int numFecha;

		cout<<"Ingrese una Fecha: ";
		cin>>numFecha;
		cout<<"Tabla de Posiciones "<<endl;

		ListaPuntaje listaPuntaje;
		ListIterator<Fecha> fechasIt = fechas.getIterator();

		int count = 1;
		while(fechasIt.hasNext() && count++ <= numFecha){
			Fecha fecha = fechasIt.next();
			ListIterator<Partido> partidos = fecha.partidos.getIterator();
			while(partidos.hasNext()){
				Partido partido = partidos.next();
				Puntaje puntajeLocal, puntajeVisitante;
				puntajeLocal.set(partido, true);
				puntajeVisitante.set(partido, false);

				listaPuntaje.put(puntajeLocal);
				listaPuntaje.put(puntajeVisitante);
			}
		}

		cout << left
			<< setw (38) << "Equipo"
			<< setw (8) << "Puntos"
			<< setw (5) << "PJ"
			<< setw (5) << "PG"
			<< setw (5) << "PE"
			<< setw (5) << "PP"
			<< setw (5) << "GF"
			<< setw (5) << "GC"
			<< setw (5) << "DG"
			<< endl;


		ListIterator<Puntaje> puntajesIt = listaPuntaje.getIterator();
		while(puntajesIt.hasNext()){
			ImprimirPuntaje(puntajesIt.next());
		}

		puntajesIt.deleteAll();
		listaPuntaje.deleteAll();
//		fechasIt.deleteAll();

		wait();
	}


	void ImprimirPuntaje(Puntaje p ){
		cout << left
			<< setw (5) << p.equipo.id
			<< setw (33) << p.equipo.nombre
			<< setw (8) << p.puntos
			<< setw (5) << p.jugados
			<< setw (5) << p.ganados
			<< setw (5) << p.empatados
			<< setw (5) << p.perdidos
			<< setw (5) << p.golesAFavor
			<< setw (5) << p.golesEnContra
			<< setw (5) << p.difDeGoles
			<< endl;
	}


	void ImprimirPartido(Partido p){
		Equipo loc = p.local;
		Equipo vis = p.visitante;

		cout << left
			<< setw (5) << loc.id
			<< setw (33) << loc.nombre
			<< setw (3) << p.golesLocal << " - " <<setw (3)<< p.golesVisitante << " "
			<< setw (5) << vis.id
			<< setw (33) << vis.nombre
			<< endl;

	}


	void Salir(){
		cout << "Gracias por jugar a Torneos de Fútbol" << endl;
	}


	void wait(){
		char t;
		cout << "Presione una tecla para continuar. . .";
		cin >> t;
	}




};
