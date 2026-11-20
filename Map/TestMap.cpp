#include "Employee.h"
#include "Book.h"						// Defines class Employee
#include "Map.h"														// Defines template Map<Key, Value>
#include <iostream>

typedef unsigned int ID;
typedef std::string Title;
typedef Map<ID, Employee> Database; 									// Database of employees
typedef Map<Title,Book> Library;
using namespace std;


void addEmployees(Database& database);
void modifyEmployees(Database& database);
void addBooks(Library& library);
void modifyBooks(Library& library);
void testBooks();
void additionalTests(Database& database);

int main() {
	Database database;
	addEmployees(database);

	Database newDatabase = database;									// Make a copy of database
	newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));	// Add fourth employee
	modifyEmployees(newDatabase);
	cout << "Original database:" << endl << database << endl;
	cout << "Modified database:" << endl << newDatabase << endl;

	database = newDatabase;												// Update original database

	cout << "Database after the assignment:" << endl << database << endl;

	testBooks();
	std::cout<<"\n";
	additionalTests(database);
};

void addEmployees(Database& database) {
	database.add(761028073, Employee("Jan Kowalski", "salesman", 28)); 	// Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));	// Add second employee
	database.add(730505129, Employee("Anna Zaradna", "secretary", 32));	// Add third employee
}

void modifyEmployees(Database& database) {
	Employee* employeePtr;

	employeePtr = database.find(510212881);								// Find employee using its ID
	employeePtr->position = "salesman";									// Modify the position of employee
	
	employeePtr = database.find(761028073);								// Find employee using its ID
	employeePtr->age = 29;												// Modify the age of employee
}

void additionalTests(Database& database) {
	try {
		database.add(730505129, Employee("Anna Zaradna", "secretary", 32));
	}catch (DuplicateKey) {
		std::cout<<"Duplicate key error: caught\n";
	}
	Employee* employeePtr;
	employeePtr = database.find(10);
	if (employeePtr == nullptr) {
		std::cout<<"Nullptr for find (key that is not in database): caught";
	}

}
void addBooks(Library& library) {
	library.add("Fullfilled",Book("Brian Williams","Drama",500,borrowed));
	library.add("Less than ever",Book("Brian Collins","Horror",68,bookshelf));
	library.add("Brothers karazmkow",Book("Elie James","Historic",20,borrowed));
}
void modifyBooks(Library& library) {
	Book* libraryPtr;
	libraryPtr = library.find("Fullfilled");								// Find employee using its ID
	libraryPtr->category = "Banger";									// Modify the position of employee

	libraryPtr = library.find("Less than ever");								// Find employee using its ID
	libraryPtr->pages = 290;
	libraryPtr->status = borrowed;
}
void testBooks() {
	Library library;
	addBooks(library);

	Library newLibrary = library;									// Make a copy of database
	newLibrary.add("Horizon", Book("Ewa Polanska", "Epic", 430, bookshelf));	// Add fourth employee
	modifyBooks(newLibrary);

	cout << "Original library:" << endl << library << endl;
	cout << "Modified library:" << endl << newLibrary << endl;

	library = newLibrary;												// Update original database

	cout << "Library after the assignment:" << endl << library << endl;
}

