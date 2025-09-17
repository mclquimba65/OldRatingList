#pragma once
#include "GamesList.h"


void displayMenu() {
	ios defaultStream(NULL); //Creates a stream buffer called defaultStream?
	defaultStream.copyfmt(cout); //defaultStream copies the format of the cout stream buffer?

	cout << setfill('-') << setw(35) << right << "| " << "MENU" << setw(34) << left << " |" << endl;
	cout.copyfmt(defaultStream); //cout copies format defaultStream?

	cout << "(1) Preview Games List\n(2) Add a game to the list\n(3) Remove a game from the list\n(4) Modify a game in the list\n(5) Quit" << endl;
	cout << endl;
}



bool isDigit(const char& charDigit) {
	bool digit = false;
	if (charDigit == '0' || charDigit == '1' || charDigit == '2' || charDigit == '3' || charDigit == '4' ||
		charDigit == '5' || charDigit == '6' || charDigit == '7' || charDigit == '8' || charDigit == '9') {

		digit = true;

	}

	return digit;
}



void verifyInteger(const string& intString) {
	string integerString = "";
	bool integer = true;

	integerString = intString;

	if ((integerString[0] == '0') && (integerString.length() > 1)) {
		integer = false;
	}
	else if ((isDigit(integerString[0])) || (integerString[0] == '-')) {

		for (int i = 1; (i < integerString.length() && integer); i++) {
			if (!isDigit(integerString[i])) {
				integer = false;
			}
		}

	}
	else {
		integer = false;
	}

	if (!integer) {
		throw runtime_error("Invalid Entry");
	}
}



void menuInputValidation(const int& menuInput) {
	if (menuInput < 1 || menuInput > 5) {
		throw runtime_error("Invalid Entry");
	}
}



void ratingValidation(const int& rating) {
	if (rating < -100 || rating > 100) {
		throw runtime_error("Invalid Entry");
	}
}



void quitInputValidation(const int& quitInput) {
	if (quitInput < 1 || quitInput > 2) {
		cout << quitInput << endl;
		throw runtime_error("Invalid Entry");
	}
}



int testStringLength(const string& str) {
	return str.length();
}



void previewList(GamesList<int>& list) {

	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout << "(1) Preview Games List\n" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout.copyfmt(defaultStream);
	cout << "\n\n" << endl;

}



void addGame(GamesList<int>& list) {
	
	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout << "(2) Add Game\n" << endl;
	cout.copyfmt(defaultStream);

	string gameName = "", ratingString = "";
	int rating = 0;

	cout << "[ Enter Name of Game ]" << endl;
	cout << "-> ";
	getline(cin, gameName);

	cout << endl;

	cout << "[ Enter Rating of Game ]" << endl;
	cout << "-> ";
	getline(cin, ratingString);

	cout << endl;

	try {
		verifyInteger(ratingString);
		rating = stoi(ratingString);
		ratingValidation(rating);
		list.insertInList(gameName, rating);
	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}

	cout << setfill('-') << setw(30) << right << "| " << "New Games List" << setw(29) << left << " |" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout.copyfmt(defaultStream);
	cout << "\n\n" << endl;

}



void removeGame(GamesList<int>& list) {

	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout << "(3) Remove Game\n" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();
	cout << endl;

	string valueString = "";
	int value = 0;

	cout << "[ Enter Value of Game ]" << endl;
	cout << "-> ";
	getline(cin, valueString);

	cout << endl;

	try {
		verifyInteger(valueString);
		value = stoi(valueString);
		list.removeFromList(value);
	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}

	cout << setfill('-') << setw(30) << right << "| " << "New Games List" << setw(29) << left << " |" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout.copyfmt(defaultStream);
	cout << "\n\n" << endl;
}



void modifyGame(GamesList<int>& list) {

	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout << "(4) Modify Game\n" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();
	
	cout << endl;

	string valueString = "";
	int value = 0;

	cout << "[ Enter Value of Game ]" << endl;
	cout << "-> ";
	getline(cin, valueString);

	cout << endl;

	try {
		verifyInteger(valueString);
		value = stoi(valueString);
		list.modifyGame(value);
	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}

	cout << setfill('-') << setw(30) << right << "| " << "New Games List" << setw(29) << left << " |" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout.copyfmt(defaultStream);
	cout << "\n\n" << endl;

}



int saveList(GamesList<int>& list) {

	ios defaultStream(NULL);
	defaultStream.copyfmt(cout);

	string optionString = "";
	int option = 0, returnValue = 0;
	bool error = false;

	cout << setfill('-') << setw(73) << left << "" << endl;
	cout << "(5) Quit\n" << endl;
	cout.copyfmt(defaultStream);

	list.previewList();
	
	cout << endl;

	do {

		cout << setfill('-') << setw(30) << right << "| " << "Finalize List" << setw(30) << left << " |" << endl;
		cout << "(1) Yes\n(2) No" << endl;
		cout.copyfmt(defaultStream);

		cout << endl;

		cout << "[ Choose Option ]" << endl;
		cout << "-> ";
		getline(cin, optionString);

		cout << endl;

		try {
			verifyInteger(optionString);
			option = stoi(optionString);
			quitInputValidation(option);

			if (option == 1) {
				list.outputToFile();
				returnValue = 1;
			}
			else {
				returnValue = 0;
			}
			
			error = false;
		}
		catch (runtime_error e) {
			cout << "Error: " << e.what() << endl;
			error = true;
		}

	} while (error);

	return returnValue;
}