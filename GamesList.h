#pragma once
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

template<typename T>
class GamesList {
private:
	int numElements;
	string fileName;
	Node<T>* headPtr;
public:
	GamesList();
	~GamesList();

	void inputFromFile();
	void insertInList(string, T);
	void recoverData(string, T, T);
	void previewList();
	void outputToFile();
	void removeFromList(const int&); //Uses value
	void modifyGame(const int&); //Uses value
	int size();
	void incrementValue(const int&);
	void decrementValue(const int&);
	bool isDigit(const char&);
	void displayEqualGameRatings(const int&);
	bool validateValue(const int&, const int&);
	bool checkIfInteger(const string&);
	//void outputToFilePreview(); //For testing purposes only
};


//---------------------| IMPLEMENTATION |---------------------//


template<typename T>
GamesList<T>::GamesList() {
	numElements = 0;
	headPtr = nullptr;
	fileName = "Mark's Games Rating List.txt";
}



template<typename T>
GamesList<T>::~GamesList() {

}



template<typename T>
int GamesList<T>::size() {
	return numElements;
}



template<typename T>
void GamesList<T>::incrementValue(const int& value) {
	Node<T>* valPtr;

	valPtr = headPtr;

	while ((valPtr != nullptr) && (valPtr->getValue() != value)) {
		valPtr = valPtr->getNextNode();
	}

	while (valPtr != nullptr) {
		valPtr->setValue(valPtr->getValue() + 1);
		valPtr = valPtr->getNextNode();
	}
}



template<typename T>
void GamesList<T>::decrementValue(const int& value) {
	Node<T>* valPtr;
	
	valPtr = headPtr;

	while ((valPtr != nullptr) && (valPtr->getValue() != value)) {
		valPtr = valPtr->getNextNode();
	}

	while (valPtr != nullptr) {
		valPtr->setValue(valPtr->getValue() - 1);
		valPtr = valPtr->getNextNode();
	}
}



template<typename T>
bool GamesList<T>::checkIfInteger(const string& toBeAssessed) {
	string number = "";
	bool integer = true;

	number = toBeAssessed;

	if ((number[0] == '0') && (number.length() > 1)) {
		integer = false;
	}
	else if (isDigit(number[0]) || (number[0] == '-')) {

		for (int i = 1; ((i < number.length()) && (integer)); i++) {
			
			if (!isDigit(number[i])) {
				integer = false;
			}

		}

	}
	else {
		integer = false;
	}

	return integer;
}



template<typename T>
bool GamesList<T>::isDigit(const char& character) {
	bool digit = false;
	if (character == '1' || character == '2' || character == '3' || character == '4' || character == '5' ||
		character == '6' || character == '7' || character == '8' || character == '9' || character == '0') {

		digit = true;
	}

	return digit;
}



template<typename T>
void GamesList<T>::inputFromFile() {
	Node<T>* tempNode;
	ifstream input_file;
	string temp = "", str = "";
	int valCounter = 1;

	input_file.open(fileName);

	if (!input_file.is_open()) {
		cout << "Unable to Open " << fileName << "." << endl;
		cout << "Terminating Program" << endl;
		exit(0);
	}

	input_file >> temp;

	while ((temp != "1") && (!input_file.eof())) { //Skip garbage lines in the file.
		input_file.ignore(1024, '\n');
		input_file >> temp;
	}

	tempNode = headPtr;

	//maybe add if (temp != "1")
	while (!input_file.eof()) {
		Node<T>* newNode = new Node<T>();

		getline(input_file, str);
		istringstream iss(str);

		getline(iss, temp, '-');
		getline(iss, temp, '-'); //temp contains game name

		newNode->setGameName(temp);

		getline(iss, temp, '(');
		getline(iss, temp, ')'); //temp contains game rating

		newNode->setRating(stoi(temp));

		newNode->setValue(valCounter);

		if (headPtr == nullptr) {
			headPtr = newNode;
			tempNode = newNode;
		}
		else {
			tempNode->setNextNode(newNode);
			tempNode = tempNode->getNextNode();
		}

		numElements++;
		valCounter++;
	}

	input_file.close();
}



template<typename T>
void GamesList<T>::previewList() {
	Node<T>* tempPtr;
	string tempGameName;

	tempPtr = headPtr;

	while (tempPtr != nullptr) {

		tempGameName = "-" + tempPtr->getGameName() + "-";

		cout << setw(5) << left << tempPtr->getValue() << setw(49) << left << tempGameName << setw(1) << right << "(" << tempPtr->getRating() << ")" << endl;

		tempPtr = tempPtr->getNextNode();
	}
}


//VALIDATE RATING IN DRIVER
template<typename T>
void GamesList<T>::insertInList(string gameName, T rating) {
	Node<T>* newNode = new Node<T>();
	Node<T>* tempPtr, * endPtr;
	bool error = false;
	int valueForSameRating = 0;

	newNode->setRating(rating);
	newNode->setGameName(gameName);

	tempPtr = headPtr;
	endPtr = headPtr;

	if (endPtr != nullptr) {
		while (endPtr->getNextNode() != nullptr) { //Traverses end pointer to the end of the list.
			endPtr = endPtr->getNextNode();
		}
	}

	if (headPtr == nullptr) { //If the list is empty.

		newNode->setValue(1);
		headPtr = newNode;
		tempPtr = newNode;

	}
	else if (newNode->getRating() > headPtr->getRating()) { //If the new node's rating is higher than head's.

		incrementValue(headPtr->getValue());

		newNode->setValue(1);
		newNode->setNextNode(headPtr);
		headPtr = newNode;
		tempPtr = headPtr;

	}
	else if (newNode->getRating() < endPtr->getRating()) { //If the new node's rating is lower than the end's.

		newNode->setValue(endPtr->getValue() + 1);
		endPtr->setNextNode(newNode);
		endPtr = newNode;

	}
	else { //If the new node's rating is inclusive to the list.

		Node<T>* prevPtr, * valPtr;
		prevPtr = headPtr;
		valPtr = headPtr;

		while ((tempPtr != nullptr) && (newNode->getRating() < tempPtr->getRating())) { //Traverses list. Updates prevPtr and tempPtr.
			prevPtr = tempPtr;
			tempPtr = tempPtr->getNextNode();
		}

		if (newNode->getRating() == tempPtr->getRating()) { //Case where the new node's rating is equal to a rating in the list.		|| 1 ||
			string valueString = "";

			displayEqualGameRatings(tempPtr->getRating());
				
			cout << "[ Enter Value of Game ]" << endl;
			cout << "-> ";
			getline(cin, valueString);

			cout << endl;

			if (!checkIfInteger(valueString)) { //Checks if the value is an integer.
				error = true;
				throw runtime_error("Invalid Entry");
			}
			else {
				valueForSameRating = stoi(valueString);
			}

			if (!checkIfInteger(valueString)) { //Checks if value is not an integer or is negative.
				//Leave blank
			}
			else if (!validateValue(valueForSameRating, tempPtr->getRating())) { //Checks if value is not within the bounds of the same rating interval.
				error = true;
				throw runtime_error("Value Out of Bounds");
			}

			if (!error) {
				if (valueForSameRating == 1) { //Case where input value == 1.									|1|
					incrementValue(headPtr->getValue());
					newNode->setValue(1);
					newNode->setNextNode(headPtr);
					headPtr = newNode;
				}
				else if (valueForSameRating > endPtr->getValue()) { //Case where input value > last value.		|2|
					newNode->setValue(endPtr->getValue() + 1);
					endPtr->setNextNode(newNode);
					endPtr = newNode;
				}
				else { //Case where input value is in between first and last.									|3|
					while (valueForSameRating != tempPtr->getValue()) {
						prevPtr = tempPtr;
						tempPtr = tempPtr->getNextNode();
					}
					newNode->setValue(tempPtr->getValue());
					incrementValue(tempPtr->getValue());
					newNode->setNextNode(tempPtr);
					prevPtr->setNextNode(newNode);
				}
			}

		} //End || 1 ||
		else { //Case where new node's rating is > another rating.		|| 2 ||

			newNode->setValue(prevPtr->getValue() + 1);
			incrementValue(tempPtr->getValue());
			newNode->setNextNode(tempPtr);
			prevPtr->setNextNode(newNode);

		} //End || 2 ||

	} //End else

	if (!error) {
		numElements++;
		cout << "Successfully inserted " << gameName << " into the list." << endl;
	}
}



template<typename T>
void GamesList<T>::recoverData(string gameName, T rating, T value) {
	Node<T>* recoveryNode = new Node<T>();
	Node<T>* tempPtr, * prevPtr, * endPtr;

	tempPtr = headPtr;
	prevPtr = headPtr;
	endPtr = headPtr;

	if (endPtr != nullptr) {
		while (endPtr->getNextNode() != nullptr) {
			endPtr = endPtr->getNextNode();
		}
	}

	recoveryNode->setGameName(gameName);
	recoveryNode->setRating(rating);
	recoveryNode->setValue(value);

	if (headPtr == nullptr) { //If the list is empty

		recoveryNode->setValue(1);
		headPtr = recoveryNode;
		tempPtr = headPtr;

	}
	else if (recoveryNode->getValue() == 1) { //If the value of the recovery node == 1

		incrementValue(headPtr->getValue());

		recoveryNode->setNextNode(headPtr);
		headPtr = recoveryNode;
		tempPtr = headPtr;

	}
	else if (value > endPtr->getValue()) { //If the value of the recovery node > last node's value

		endPtr->setNextNode(recoveryNode);
		endPtr = recoveryNode;

	}
	else { //If the value of the recovery node is inclusive to the list.

		while (tempPtr->getValue() != recoveryNode->getValue()) {	
			prevPtr = tempPtr;
			tempPtr = tempPtr->getNextNode();
		}

		incrementValue(tempPtr->getValue());

		recoveryNode->setNextNode(tempPtr);
		prevPtr->setNextNode(recoveryNode);

	}

	numElements++;
	cout << "Data has been recovered for " << recoveryNode->getGameName() << "." << endl;
}



template<typename T>
void GamesList<T>::displayEqualGameRatings(const int& rating) {
	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	Node<T>* stringPtr;
	stringPtr = headPtr;

	while ((stringPtr != nullptr) && (stringPtr->getRating() != rating)) {
		stringPtr = stringPtr->getNextNode();
	}

	cout << setfill('-') << setw(28) << right << "| " << "Equal Rated Games" << setw(28) << left << " |" << endl;
	cout.copyfmt(defaultStream);

	while ((stringPtr != nullptr) && (stringPtr->getRating() == rating)) {
		cout << setw(5) << left << stringPtr->getValue() << setw(49) << left << stringPtr->getGameName() << setw(1) << right << "(" << stringPtr->getRating() << ")" << endl;
		stringPtr = stringPtr->getNextNode();
	}

	cout << setfill('-') << setw(73) << "" << endl;
	cout.copyfmt(defaultStream);
}


//Is used for the case where multple of the game with the same ratings exist.
template<typename T>
bool GamesList<T>::validateValue(const int& value, const int& rating) {
	Node<T>* valPtr;
	valPtr = headPtr;
	bool valid = true;

	while ((valPtr != nullptr) && (valPtr->getRating() != rating)) { //Traverses the list until rating is found.
		valPtr = valPtr->getNextNode();
	}
	
	if (value < valPtr->getValue()) {
		valid = false;
	}
	else {

		while (valPtr->getRating() == rating) { //Traverses the list until past the rating.
			valPtr = valPtr->getNextNode();
		}
		if (value > valPtr->getValue()) {
			valid = false;
		}

	}

	return valid;
}


//VALIDATE VALUE IN DRIVER
template<typename T>
void GamesList<T>::removeFromList(const int& value) {
	Node<T>* tempPtr, * prevPtr, * valPtr;
	bool error = false;

	tempPtr = headPtr;
	prevPtr = headPtr;
	valPtr = headPtr;

	if (tempPtr == nullptr) { //If the list is empty.
		error = true;
		throw runtime_error("List Empty");
	}
	else if (value < 1 || value > numElements) { //If the value is not within the list.
		error = true;
		throw runtime_error("Value Out of Bounds");
	}
	else if ((tempPtr != nullptr) && tempPtr->getValue() == value) { //If the head node needs to get removed.

		valPtr = valPtr->getNextNode();

		decrementValue(valPtr->getValue());

		headPtr = tempPtr->getNextNode();

	}
	else if (value < numElements) { //If some other node needs to get removed.

		while ((tempPtr != nullptr) && tempPtr->getValue() != value) { //Traverses the list until the value is found.
			prevPtr = tempPtr;
			tempPtr = tempPtr->getNextNode();
			valPtr = tempPtr;
		}

		if (tempPtr != nullptr) {
			valPtr = valPtr->getNextNode();

			decrementValue(valPtr->getValue());

			prevPtr->setNextNode(tempPtr->getNextNode());
		}

	}
	else { //If end node needs to be removed.

		while ((tempPtr != nullptr) && tempPtr->getValue() != value) {
			prevPtr = tempPtr;
			tempPtr = tempPtr->getNextNode();
		}

		if (tempPtr != nullptr) {
			prevPtr->setNextNode(tempPtr->getNextNode());
		}

	}

	if (!error) {
		numElements--;
		cout << "Successfully removed " << tempPtr->getGameName() << " from the list." << endl;
		delete tempPtr;
	}
}


//VALIDATE VALUE IN DRIVER
template<typename T>
void GamesList<T>::modifyGame(const int& value) {
	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	if (headPtr == nullptr) { //If the list is empty.
		throw runtime_error("List Empty");
	}
	else if (value < 1 || value > size()) { //If the value input is not in the bounds of the list.
		throw runtime_error("Value Out of Bounds");
	}
	else {
		Node<T>* tempPtr;
		int secondValue = 0;
		string secondValueString = "";

		tempPtr = headPtr;

		while ((tempPtr != nullptr) && (tempPtr->getValue() != value)) {
			tempPtr = tempPtr->getNextNode();
		}

		cout << setfill('-') << setw(30) << right << "| " << "Choose Option" << setw(30) << left << " |" << endl;
		cout << "(1) Modify game name\n(2) Modify game rating\n(3) Modify whole item" << endl;
		cout << setw(73) << "" << endl;
		cout.copyfmt(defaultStream);

		cout << "[ Enter Option ]" << endl;
		cout << "-> ";
		getline(cin, secondValueString);

		cout << endl;

		if (!checkIfInteger(secondValueString)) {
			throw runtime_error("Invalid Entry");
		}
		else {
			secondValue = stoi(secondValueString);
		}

		if (!checkIfInteger(secondValueString)) {
			//Leave blank
		}
		else if (secondValue < 1 || secondValue > 3) { //Error.		|1|
			throw runtime_error("Invalid Entry");
		}
		else if (secondValue == 1) { //Modify game name.		|2|

			string newGameName = "";

			cout << "Modifying game name at value " << value << "...\n" << endl;
			cout << "[ Enter Name of Game ]" << endl;
			cout << "-> ";
			getline(cin, newGameName);

			cout << endl;

			tempPtr->setGameName(newGameName);

			cout << "Game name at " << value << " has been modified." << endl;

		}
		else if (secondValue == 2) { //Modify game rating.		|3|

			string ratingString = "";
			int rating = 0;

			cout << "Modifying game rating for " << tempPtr->getGameName() << "...\n" << endl;
			cout << "[ Enter Rating of Game ]" << endl;
			cout << "-> ";
			getline(cin, ratingString);

			cout << endl;

			if (!checkIfInteger(ratingString)) {
				throw runtime_error("Invalid Entry");
			}
			else {
				rating = stoi(ratingString);
			}

			if (!checkIfInteger(ratingString)) {
				//Leave blank
			}
			else if (rating < -100 || rating > 100) { //If the rating input is not within the bounds of the list.
				throw runtime_error("Rating Out of Bounds");
			}
			else {
				string gameName = "";
				int dataRecoveryRating = 0, dataRecoveryValue = 0;

				gameName = tempPtr->getGameName();
				dataRecoveryRating = tempPtr->getRating();
				dataRecoveryValue = tempPtr->getValue();
											
				removeFromList(tempPtr->getValue());

				try {
					insertInList(gameName, rating);
					cout << "Game rating for " << gameName << " has been modified." << endl;
				}
				catch (runtime_error e) {
					cout << "Error: " << e.what() << endl;
					cout << "Data recovery has started..." << endl;
					recoverData(gameName, dataRecoveryRating, dataRecoveryValue);
				}
			}

		}
		else { //Modify the whole item.							|4|

			string newGameName = "", ratingString = "";
			int rating = 0;

			cout << "Modifying item at value " << value << " ...\n" << endl;

			cout << "[ Enter NEW Name of Game ]" << endl;
			cout << "-> ";
			getline(cin, newGameName);

			cout << endl;

			cout << "[ Enter NEW Rating of Game ]" << endl;
			cout << "-> ";
			getline(cin, ratingString);

			cout << endl;

			if (!checkIfInteger(ratingString)) {
				throw runtime_error("Invalid Entry");
			}
			else {
				rating = stoi(ratingString);
			}

			if (!checkIfInteger(ratingString)) {
				//Leave blank
			}
			else if (rating < -100 || rating > 100) { //If the rating input is not within the bounds of the list.
				throw runtime_error("Rating Out of Bounds");
			}
			else {

				string dataRecoveryString = "";
				int dataRecoveryRating = 0, dataRecoveryValue = 0;

				dataRecoveryString = tempPtr->getGameName();
				dataRecoveryRating = tempPtr->getRating();
				dataRecoveryValue = tempPtr->getValue();

				try {
					removeFromList(tempPtr->getValue());
				}
				catch (runtime_error e) {
					cout << "Error: " << e.what() << endl;
				}

				try {
					insertInList(newGameName, rating);
					cout << "A game has been modified.\n" << endl;
				}
				catch (runtime_error e) {								
					cout << "Error: " << e.what() << endl;
					cout << "Data recovery has started..." << endl;
					recoverData(dataRecoveryString, dataRecoveryRating, dataRecoveryValue);
				}

			}

		}
	}
}



template<typename T>
void GamesList<T>::outputToFile() {
	Node<T>* tempPtr;
	string tempGameName = "";

	ofstream output_file(fileName);

	tempPtr = headPtr;

	output_file << setfill('=') << setw(48) << right << "|| " << "Mark's Games Rating List" << setw(48) << left << " ||" << endl;
	output_file << "\nScale: [-100 , 100]\n" << setfill(' ') << endl;

	tempGameName = "-" + tempPtr->getGameName() + "-";
	output_file << setw(5) << left << tempPtr->getValue() << setw(49) << tempGameName << setw(1) << right << "(" << tempPtr->getRating() << ")";
	tempGameName.clear();

	tempPtr = tempPtr->getNextNode();

	while (tempPtr != nullptr) {
		output_file << endl;

		tempGameName = "-" + tempPtr->getGameName() + "-";
		output_file << setw(5) << left << tempPtr->getValue() << setw(49) << tempGameName << setw(1) << right << "(" << tempPtr->getRating() << ")";
		tempGameName.clear();

		tempPtr = tempPtr->getNextNode();
	}

	cout << "List Output to " << fileName << endl;
	cout << "Save Successful" << endl;

	output_file.close();
}



/*
	For testing purposes only.

template<typename T>
void GamesList<T>::outputToFilePreview() {
	string tempString = "";
	Node<T>* tempPtr;

	tempPtr = headPtr;

	cout << setfill('=') << setw(48) << right << "|| " << "Mark's Games Rating List" << setw(48) << left << " ||" << endl;
	cout << "\nScale: [100 , 100]\n" << setfill(' ') << endl;
	
	
	while (tempPtr != nullptr) {

		tempString = "-" + tempPtr->getGameName() + "-";
		cout << setw(5) << left << tempPtr->getValue() << setw(50) << tempString << setw(10) << right << "(" << tempPtr->getRating() << ")" << endl;
		tempString.clear();

		tempPtr = tempPtr->getNextNode();
	}
}
*/