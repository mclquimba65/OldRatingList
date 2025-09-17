#pragma once

using namespace std;


template<typename T>
class Node {
private:
	Node<T>* nextNode;
	T rating;
	string gameName;
	T value;

public:
	Node();
	~Node();
	
	void setNextNode(Node<T>*);
	Node<T>* getNextNode();

	void setRating(T);
	T getRating();

	void setGameName(string);
	string getGameName();

	void setValue(T);
	T getValue();
};


//                 | IMPLEMENTATION |                 //


template<typename T>
Node<T>::Node() {
	nextNode = nullptr;
}


template<typename T>
Node<T>::~Node() {
	//Destructor for Node class.
}


template<typename T>
void Node<T>::setNextNode(Node<T>* nextNode) {
	this->nextNode = nextNode;
}


template<typename T>
Node<T>* Node<T>::getNextNode() {
	return nextNode;
}


template<typename T>
void Node<T>::setRating(T rating) {
	this->rating = rating;
}


template<typename T>
T Node<T>::getRating() {
	return rating;
}


template<typename T>
void Node<T>::setGameName(string gameName) {
	this->gameName = gameName;
}


template<typename T>
string Node<T>::getGameName() {
	return gameName;
}


template<typename T>
void Node<T>::setValue(T value) {
	this->value = value;
}


template<typename T>
T Node<T>::getValue() {
	return value;
}