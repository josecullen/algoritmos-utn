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
		if(local){
			this->equipo = partido.local;
			this->jugados = 1;
			this->golesAFavor = partido.golesLocal;
			this->golesEnContra = partido.golesVisitante;
			this->difDeGoles = partido.golesLocal - partido.golesVisitante;

			if(partido.golesLocal > partido.golesVisitante){
				this->ganados = 1;
				this->empatados = 0;
				this->perdidos = 0;
				this->puntos = 3;
			}else if(partido.golesLocal < partido.golesVisitante){
				this->ganados = 0;
				this->empatados = 0;
				this->perdidos = 1;
				this->puntos = 0;
			}else{
				this->ganados = 0;
				this->empatados = 1;
				this->perdidos = 0;
				this->puntos = 1;
			}
		}else{
			this->equipo = partido.visitante;
			this->jugados = 1;
			this->golesAFavor = partido.golesVisitante;
			this->golesEnContra = partido.golesLocal;
			this->difDeGoles = partido.golesVisitante - partido.golesLocal;

			if(partido.golesVisitante > partido.golesLocal){
				this->ganados = 1;
				this->empatados = 0;
				this->perdidos = 0;
				this->puntos = 3;
			}else if(partido.golesVisitante < partido.golesLocal){
				this->ganados = 0;
				this->empatados = 0;
				this->perdidos = 1;
				this->puntos = 0;
			}else{
				this->ganados = 0;
				this->empatados = 1;
				this->perdidos = 0;
				this->puntos = 1;
			}

		}
	}
};



struct Fecha{
	List<Partido> partidos;
};



