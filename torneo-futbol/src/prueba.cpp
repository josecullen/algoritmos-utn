#include "includes.h"
#include "menu.h"

void MenuPrincipal();
void MenuEdicion();
void MenuSimulacion(bool simular);
List<Fecha> getFechas();
Menu menu;
List<Fecha> fechas;

int main(int argc, char** argv) {
	fechas = getFechas();
	MenuPrincipal();
	return 0;
}


void MenuPrincipal(){
	bool salir = false;
	int opcion = menu.MenuPrincipal();

	switch (opcion) {
		case 1:
			MenuEdicion();
			break;
		case 2:
			MenuSimulacion(true);
			break;
		case 0:
			salir = true;
			break;
		default:
			break;
	}

	if(!salir){
		MenuPrincipal();
	}else{
		menu.Salir();
	}

}

void MenuEdicion(){
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
		MenuEdicion();
	}
}

void MenuSimulacion(bool simular){
	int opcion = menu.MenuSimulacion();
	bool volver = false;



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
		MenuSimulacion(false);
	}
}


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




