/*
 * estructuras.h
 *
 *  Created on: 31 de ene. de 2016
 *      Author: jcullen
 */


struct Equipo{
	char id [4];
	char nombre[32];
	int potenciaAtaque;
	int potenciaDefensa;
};

struct Partido{
	Equipo
		local,
		visitante;
	int
		golesLocal,
		golesVisitante;

	void set(Equipo local, Equipo visitante, int golesLocal, int golesVisitante){
		this->local = local;
		this->visitante = visitante;
		this->golesLocal = golesLocal;
		this->golesVisitante = golesVisitante;
	}
};

struct Puntaje{
	Equipo equipo;
	int
		puntos,
		jugados,
		ganados,
		perdidos,
		empatados,
		golesAFavor,
		golesEnContra,
		difDeGoles;

	void set(Partido partido, bool local){
		this->equipo = local ? partido.local : partido.visitante;
		this->golesAFavor = local ? partido.golesLocal : partido.golesVisitante;
		this->golesEnContra = local ? partido.golesVisitante : partido.golesLocal;
		this->difDeGoles = local ?
				partido.golesLocal - partido.golesVisitante :
				partido.golesVisitante - partido.golesLocal;

		this->jugados = 1;
		this->ganados = 0;
		this->empatados = 0;
		this->perdidos = 0;
		this->puntos = 0;

		if (this->golesAFavor > this->golesEnContra) {
		    this->ganados = 1;
		    this->puntos = 3;
		}else if (this->golesAFavor < this->golesEnContra) {
		    this->perdidos = 1;
		}else {
		    this->empatados = 1;
		    this->puntos = 1;
		}
	}

};



struct Fecha{
	List<Partido> partidos;
};



