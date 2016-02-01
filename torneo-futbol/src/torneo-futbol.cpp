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
	bool salir = false;
	int opcion = menu.MenuPrincipal();

	switch (opcion) {
		case 1:
			MenuEdicion(menu);
			break;
		case 2:
			{
				List<Fecha> fechas;
				MenuSimulacion(menu, fechas, true);
			}
			break;
		case 0:
			salir = true;
			break;
		default:
			break;
	}

	if(!salir){
		MenuPrincipal(menu);
	}else{
		menu.Salir();
	}

}

/**
 * Maneja las distintas respuestas del menú de edición
 */
void MenuEdicion(Menu menu){
	int opcion = menu.MenuEdicion();
	bool volver = false;

	switch (opcion) {
		case 1:
			fileManager.put(menu.CrearEquipo());
			break;
		case 2:
			menu.EliminarEquipo();
			break;
		case 3:
			menu.ListarEquipos();
			break;
		case 0:
			volver = true;
			break;
		default:
			break;
	}

	if(!volver){
		MenuEdicion(menu);
	}
}

/**
 * Maneja las distintas respuestas del menú de simulación
 */
void MenuSimulacion(Menu menu, List<Fecha> fechas, bool simular){
	int opcion = menu.MenuSimulacion();
	bool volver = false;

	if(simular){
		fechas = getFechas();
	}

	switch (opcion) {
		case 1:
			menu.TablaDePosiciones(fechas);
			break;
		case 2:
			menu.PartidosPorEquipo(fechas);
			break;
		case 3:
			menu.PartidosPorFecha(fechas);
			break;
		case 0:
			volver = true;
			break;
		default:
			break;
	}

	if(!volver){
		MenuSimulacion(menu, fechas, false);
	}
}

/**
 * Simula el torneo.
 */
List<Fecha> getFechas(){
	Equipo equipos[100] = {};
	FileIterator<Equipo> it = fileManager.getIterator();

	int count = 0;
	while(it.hasNext()){
		equipos[count++] = it.next();
	}

	List<Fecha> fechas;
	int l, v;
	for(int numFecha = 0; numFecha < count-1; numFecha++){
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




