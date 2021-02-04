#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "list.hpp"
#include <iostream>


template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
	Collection() { collection_ = new node<T>; isFirst = true; }
	void add(const T&);
	void remove(const T&);
	node<T>* last() { return collection_; }
	void print();

	
	friend bool equal(const Collection&, const Collection&);


private:
	bool isFirst;
	node<T>* collection_;
};






//Adds to BEGINNING
template <typename T>
void Collection<T>::add(const T& data) {
	//Creates new node and sets data equal to the passed data //next_ is nullptr
	node<T>* newNode = new node<T>;
	newNode->setData(data);
	
	//Checks if its the first in the collection
	if (isFirst) {
		collection_ = newNode;
		isFirst = false;
	}
	else {
		node<T>* i = collection_;
		while (i != nullptr) {
			if (i->getNext() == nullptr) {
				i->setNext(newNode);
				break;
			}
			else {
				i = i->getNext();
			}
		}
	}

	
}

template <typename T>
void Collection<T>::remove(const T& data) {
	//Creates itterator and sets it to the start of the collection and prev to keep track of the previous node
	node<T>* i = collection_;
	node<T>* prev = nullptr;


	while (i != nullptr) {
		//Checks to see if we need to remove the data;
		if (i->getData() == data) {
			//Checks to see if i is the beginning
			if (prev == nullptr) {
				node<T>* temp = i->getNext();
				delete i;
				i = temp;
			}
			else {
				prev->setNext(i->getNext());
				delete i;
				i = prev->getNext();
			}
		}
		else {
			prev = i;
			i = i->getNext();
		}
	}
}


template <typename T>
void Collection<T>::print() {
	node<T>* i = collection_;

	while (i != nullptr) {
		std::cout << i->getData() << '\n';
		i = i->getNext();
	}
}


template <typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
	//Creating new nodes for traversal
	node<T>* i = lhs.collection_;
	node<T>* j = rhs.collection_;

	while ((i != nullptr) || (j != nullptr)) {
		//Checks if either itterator is a nullptr
		if ((i == nullptr) || (j == nullptr)) {
			return false;
		}

		if (i->getData() != j->getData()) {
			return false;
		}
		i = i->getNext();
		j = j->getNext();
	}
	return true;
}




#endif