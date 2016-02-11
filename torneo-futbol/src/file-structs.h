/*
 * file-structs.h
 *
 *  Created on: 31 de ene. de 2016
 *      Author: jcullen
 */

#ifndef FILE_STRUCTS_H_
#define FILE_STRUCTS_H_


using namespace std;
const char NOMBRE_ARCHIVO [20] = "EquiposDeFutbol.bin";


/**
 * Iterador de archivo genérico
 */
template<typename T> struct FileIterator{
	FILE *file;
	T siguiente;
	bool haySiguiente;

	void setFile(FILE *file){
		this->file = fopen(NOMBRE_ARCHIVO, "ab+");
		intentarLeerSiguiente();
	}

	bool hasNext(){
		return haySiguiente;
	}

	bool close(){
		return fclose(file);
	}

	T next(){
		T anterior = siguiente;
		intentarLeerSiguiente();
		return anterior;
	}

	void intentarLeerSiguiente() {
		fread(&siguiente, sizeof(T), 1, file);
		haySiguiente = !feof(file);
		if(!haySiguiente){
			fclose(file);
		}
	}

};


/**
 * Contiene varios métodos para manejar un archivo de Equipos
 */
struct FileManager{

	FILE * file;
	FileIterator<Equipo> iterator;

	FileIterator<Equipo> getIterator(){
		iterator.setFile(file);
		return iterator;
	}

	void put(Equipo equipo){
		this->file = fopen(NOMBRE_ARCHIVO,"ab+");
		fwrite(&equipo, sizeof(Equipo), 1, file);
		fclose(file);
	}

	bool contains(char id[4]){
		return getIndex(id) != -1;
	}

	bool removeById(char id[4]){
		bool removed = false;

		FileIterator<Equipo> it = getIterator();

		FILE *tmp = fopen("tmp.bin", "ab+");

		Equipo equipo;

		while (it.hasNext()) {
			equipo = it.next();

			if (strcmp (equipo.id, id) == 0) {
				removed = true;
			} else {
				fwrite(&equipo, sizeof(Equipo), 1, tmp);
			}
			fread(&equipo,sizeof(Equipo),1,file);
		}

		fclose(tmp);
		remove(NOMBRE_ARCHIVO);

		int result = rename("tmp.bin", NOMBRE_ARCHIVO);

		cout<<"result :"<<result<<endl;

		return removed;
	}

	int getIndex(char id[4]){
		FileIterator<Equipo> it =  getIterator();
		int pos = 0;
		while(it.hasNext()){
			Equipo equipo = it.next();
			if(strcmp(equipo.id, id) == 0){
				it.close();
				return pos;
			}
			pos++;
		}
		return -1;
	}

	List<Equipo> getList(){
		FileIterator<Equipo> it = getIterator();
		List<Equipo> list;
		while(it.hasNext()){
			list.put(it.next());
		}
		return list;
	}

};

/**
 * Lista doblemente enlazada con lógica propia necesaria para la
 * administración de los puntajes.
 */
struct ListaPuntaje{
	Node<Puntaje> *inicio = NULL;
	Node<Puntaje> *fin;

	void put(Puntaje puntaje){
		if(!inicio){
			Node<Puntaje> *node = new Node<Puntaje>();
			node->data = puntaje;
			inicio = node;
			fin = inicio;
		}else{
			ListIterator<Puntaje> it = this->getIterator();
			Puntaje p;
			while(it.hasNext()){
				p = it.next();
				if(strcmp(p.equipo.id, puntaje.equipo.id) == 0){
					merge(it.currentNode->data,puntaje);
					this->reorder(it.currentNode);
					return;
				}
			}
			Node<Puntaje> *node = new Node<Puntaje>();
			node->data = puntaje;
			Node<Puntaje> *ant = fin;
			fin->sig = node;
			fin = node;
			node->ant = ant;
			this->reorder(node);
		}
	}

	ListIterator<Puntaje> getIterator(){
		ListIterator<Puntaje> it;
		it.set(inicio, fin);
		return it;
	}

	/**
	 * Cuando se ingresa un Equipo que ya se encuentra en la lista
	 * se suman los valores
	 */
	void merge(Puntaje &actual, Puntaje nuevo){
		actual.jugados 		 += nuevo.jugados;
		actual.ganados 		 += nuevo.ganados;
		actual.empatados 	 += nuevo.empatados;
		actual.perdidos 	 += nuevo.perdidos;
		actual.difDeGoles 	 += nuevo.difDeGoles;
		actual.golesAFavor 	 += nuevo.golesAFavor;
		actual.golesEnContra += nuevo.golesEnContra;
		actual.puntos 		 += nuevo.puntos;
	}

	/**
	 * De acuerdo al puntaje, a la diferencia de goles y a los goles a favor,
	 * decide si tiene que mover un Equipo más arriba en la lista.
	 */
	void reorder(Node<Puntaje> *puntaje){
		if(puntaje->ant){
			Puntaje actual = puntaje->data;
			Puntaje anterior = puntaje->ant->data;

			if(
				actual.puntos > anterior.puntos ||
				(actual.puntos == anterior.puntos && actual.difDeGoles > anterior.difDeGoles) ||
				(actual.puntos == anterior.puntos
						&& actual.difDeGoles == anterior.difDeGoles
						&& actual.golesAFavor > anterior.golesAFavor)
				){
					puntaje->ant->sig = puntaje->sig;

					if(puntaje->sig){
						puntaje->sig->ant = puntaje->ant;
					}

					puntaje->sig = puntaje->ant;

					if(puntaje->ant->ant){
						puntaje->ant->ant->sig = puntaje;
					}

					puntaje->ant = puntaje->ant->ant;
					puntaje->sig->ant = puntaje;

					if(puntaje == fin){
						fin = puntaje->sig;
					}

					if(puntaje->sig == inicio){
						inicio = puntaje;
					}

					reorder(puntaje);
				}
			}
		}

	void deleteAll(){
		Node<Puntaje> *aux;
		while(inicio){
			aux = inicio;
			inicio = inicio->sig;
			free(aux);
		}
		delete(inicio);
		delete(fin);
	}

};






#endif /* FILE_STRUCTS_H_ */
