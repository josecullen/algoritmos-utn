/*
 * lista.h
 *  Se definen las estructuras que manejan listas
 *  Created on: 29 de ene. de 2016
 *      Author: jcullen
 */

#ifndef LISTAS_H_
#define LISTAS_H_

/**
 * Nodo genérico
 */
template<typename T> struct Node{
	T data;
	Node *sig = NULL;
	Node *ant = NULL;
};

/**
 * Iterador genérico
 */
template<typename T> struct ListIterator{
	Node<T>
		*inicio,
		*currentNode,
		*siguiente;
	bool haySiguiente;

	void set(Node<T> *inicio, Node<T> *fin){
		this->inicio = inicio;
		intentarLeerSiguiente();
	}

	bool hasNext(){
		return haySiguiente;
	}

	T next(){
		currentNode = siguiente;
		intentarLeerSiguiente();
		return currentNode->data;
	}

	void deleteAll(){
		Node<T> *aux;
		while(inicio){
			aux = inicio;
			inicio = inicio->sig;
			free(aux);
		}
		delete(this->currentNode);
	}

	void intentarLeerSiguiente() {
		siguiente = inicio;
		haySiguiente = siguiente != NULL;
		if(haySiguiente){
			inicio = inicio->sig;
		}
	}
};

/**
 * Lista genérica
 */
template<typename T> struct List{
	int length = 0;
	Node<T> *inicio = NULL;
	Node<T> *fin;

	void put(T t){
		length++;
		Node<T> *node = new Node<T>();
		node->data = t;

		if(!inicio){
			inicio = node;
			fin = inicio;
		}else{
			Node<T> *ant = fin;
			fin->sig = node;
			fin = node;
			node->ant = ant;
		}
	}

	ListIterator<T> getIterator(){
		ListIterator<T> it;
		it.set(inicio, fin);
		return it;
	}

	void deleteAll(){
		Node<T> *aux;
		while(inicio){
			aux = inicio;
			inicio = inicio->sig;
			free(aux);
		}
	}

};




#endif /* LISTAS_H_ */
