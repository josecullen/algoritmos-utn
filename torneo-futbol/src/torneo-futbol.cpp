#include "includes.h"
#include "menu.h"

void MenuPrincipal(Menu menu);
void MenuEdicion(Menu menu);
void MenuSimulacion(Menu menu, List<Fecha> fechas, bool simular);
List<Fecha> getFechas();


/**
 * Método de entrada a la aplicación
 */
int main(int argc, char** argv) {
	Menu menu;
	MenuPrincipal(menu);
	return 0;
}

/**
 * Maneja las distintas respuestas del menú principal
 */
void MenuPrincipal(Menu menu){
	int opcion = menu.MenuPrincipal();

	switch (opcion) {
		case 1:
			MenuEdicion(menu);
			MenuPrincipal(menu);
			break;
		case 2:
			{
				List<Fecha> fechas;
				MenuSimulacion(menu, fechas, true);
				MenuPrincipal(menu);
				fechas.deleteAll();
			}
			break;
		case 0:
			break;
	}
}


/**
 * Maneja las distintas respuestas del menú de edición
 */
void MenuEdicion(Menu menu){
	int opcion = menu.MenuEdicion();

	switch (opcion) {
		case 1:
			fileManager.put(menu.CrearEquipo());
			MenuEdicion(menu);
			break;
		case 2:
			menu.EliminarEquipo();
			MenuEdicion(menu);
			break;
		case 3:
			menu.ListarEquipos();
			MenuEdicion(menu);
			break;
		case 0:
			break;
		default:
			break;
	}
}


/**
 * Maneja las distintas respuestas del menú de simulación
 */
void MenuSimulacion(Menu menu, List<Fecha> fechas, bool simular){
	int opcion = menu.MenuSimulacion();

	if(simular){
		fechas = getFechas();
	}

	switch (opcion) {
		case 1:
			menu.TablaDePosiciones(fechas);
			MenuSimulacion(menu, fechas, false);
			break;
		case 2:
			menu.PartidosPorEquipo(fechas);
			MenuSimulacion(menu, fechas, false);
			break;
		case 3:
			menu.PartidosPorFecha(fechas);
			MenuSimulacion(menu, fechas, false);
			break;
		case 0:
			break;
		default:
			break;
	}

}

/**
 * Simula el torneo.
 */
List<Fecha> getFechas(){
	Equipo equiposAux[100] = {};
	FileIterator<Equipo> it = fileManager.getIterator();

	int count = 0;
	while(it.hasNext()){
		equiposAux[count++] = it.next();
	}

	Equipo equipos[count] = {};
	int randomValues[count] = {};
	for(int i = 0; i < count; ){
		int value = rand() % count;
		bool newValue = true;
		for(int randoms = 0; randoms < i; randoms++){
			if(randomValues[randoms] == value){
				newValue = false;
				break;
			}
		}
		if(newValue){
			equipos[i] = equiposAux[value];
			randomValues[i] = value;
			i++;
		}
	}

	int totalFechas;
	count % 2 == 0 ? totalFechas = count-1 : totalFechas = count;
	cout<<"total fechas "<<totalFechas;
	List<Fecha> fechas;
	int l, v;
	for(int numFecha = 0; numFecha < totalFechas; numFecha++){
		Fecha fecha;

		for(int numPartido = 1; numPartido <= count/2; numPartido++){
			generarPartido(count,numFecha+1,numPartido,l,v);

			Equipo local = equipos[l];
			Equipo visitante = equipos[v];
			int golesLocal, golesVisitante;

			simularPartido(
					local.potenciaAtaque,
					local.potenciaDefensa,
					visitante.potenciaAtaque,
					visitante.potenciaDefensa,
					golesLocal,
					golesVisitante
			);

			Partido partido;
			partido.set(local, visitante, golesLocal, golesVisitante);
			fecha.partidos.put(partido);

		}
		fechas.put(fecha);
		cout<<endl<<endl;
	}

	return fechas;
}




