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
	Node<T> *inicio, *fin, *currentNode;
	bool has;

	void set(Node<T> *inicio, Node<T> *fin){
		this->inicio = inicio;
		this->fin = fin;
		has = inicio;
	}

	bool hasNext(){
		if(has){
			has = inicio != fin;
			return true;
		}else{
			return false;
		}
	}

	T next(){
		currentNode = inicio;
		T data = inicio->data;
		inicio = inicio->sig;
		return data;
	}

	void deleteAll(){
		delete(this->currentNode);
		delete(this->fin);
		delete(this->inicio);
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
		delete(inicio);
		delete(fin);
	}

};




#endif /* LISTAS_H_ */
