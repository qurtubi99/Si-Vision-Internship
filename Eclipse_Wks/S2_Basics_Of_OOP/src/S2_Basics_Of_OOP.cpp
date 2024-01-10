//============================================================================
// Name        : S2_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : S2
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

/**********************************************************************************************/
//One line used to calculate the execution time of a function

struct Time {
	int hours, minutes, seconds;
};

// returns the current time
Time getTimeNow(){
	//Assume there is a logic that calculate the current time
	Time timeNow;
	return timeNow;
}

// returns the elapsed time in seconds between two time formats
int elapsedTime(Time lhs, Time rhs){
	return (rhs.seconds - lhs.seconds);
}

class Execution_Time{
private:
	Time startTime,endTime,executionTime;
public:
	Execution_Time(){
		startTime = getTimeNow();
	}

	~Execution_Time(){
		endTime = getTimeNow();
		executionTime.seconds = elapsedTime(endTime, startTime);
		cout << executionTime.seconds << endl;
	}
};

void func(){
	Execution_Time execution_TimeObject;
}
/**********************************************************************************************/
//Example on class with Constructors(defalut, parametrized & copy), destructor, setters and getters:

class MyString{
	//Data members
private:
	int size;
	char *literals;
	//Method members
public:
	//Default constructor (no i/p arguments/parameters)
	MyString(){
		cout << "Default constructor of MyString is called\n";

		//1. Initialize member variables
		literals = nullptr;
		size = 0;

		//2. do any setup steps necessary for the class to be used.
	}

	//Parametrized constructor
	//- inputLiterals must be defined const, to delay destruction of temporary memory location
	//	allocated by the compiler for the passed string till the complete implementation for
	//	the parametrized constructor
	MyString(const char *inputLiterals){
		cout << "Parametrized constructor of MyString is called\n";
		size = strlen(inputLiterals);
		literals = new char[size + 1];			//+1 for '\0'
		memcpy(literals,inputLiterals,size);
		literals[size] = '\0';

	}

	//I must define the copy constructor in this way (const and pass by reference) ; cuz the compiler define it in the same way
	MyString(const MyString &other):
		size(other.size),
		literals(new char[size + 1])
	{
		cout << "Copy constructor is called\n";
		memcpy(literals, other.literals, size);
		literals[size] = '\0';
	}
	//Since the copy constructor makes same things in parametrized constuctor, I may delegate it as follows
	/*
	 	MyString(const MyString &other): MyString(other.literals)
		{
			cout << "Copy constructor is called\n";
		}
	 */


	void print(){
		cout << "Literals: " << literals << endl;
	}

	//Getter for the size
	//const after getSize() gureantees that the data member I return must be read only, and give error, if
	// I've returned it by reference.
	int getSize() const{
		return size;
	}

	//Setter for literals
	void setLiterals(const char *inputLiterals){
		int newSize = strlen(inputLiterals);
		if(newSize > size){
			//Through exception
			//return error
		}else{
			memcpy(literals,inputLiterals,size);
		}
	}

	//Destructor
	//- Deallocate object from memory location
	//- called when stack-allocated objects go out of scope & when delete is called on heap-allocated objects.
	~MyString(){
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}
};
/**********************************************************************************************/
//Example to expalin what should I do in constructors and destrucors.
class Database{
public:
	Database(){
		//1. Initialize member variables
		//2. do any setup steps necessary for the class to be used
		//	2.1 Discover the server.
		//	2.2 Connect to server
		//	2.3 Authentication
	}

	~Database(){
		//Make cleanup operations (data | logic)
		//- Make opposit steps made in constructor.
	}
};

/**********************************************************************************************/
//Example to explain the initial value of constructor parameters:

class Dummy{
private:
	int x;
public:
	//Parametrized constructor with initial value.
	Dummy(int xInput = 15){
		x = xInput;
	}
};

/**********************************************************************************************/
//Exaple to expalin the need of initializer list:

class Employee{
private:
	MyString myStringObj;
public:
	//Parametrized constructor
	//- If the id parameter was received by reference (int &id), it should have beed defined
	//	as constant incase the employee object was defined with passing R-value id (e.g. Employee employee(5);)
	Employee(int id){
		if(id == 0){
			myStringObj = "Ahmed";
		}else{
			myStringObj = "Mohamed";
		}
	}
};

/**********************************************************************************************/
//Exaple to explain the used of expicit keyword with constructors:

class Dummy2{
private:
	int x;

public:
	explicit Dummy2(int x):x(x){

	}
};

/**********************************************************************************************/
//Example to explain delegation in calsses:

class Database2{
public:
	//Delegating the parametrized constructor.
	Database2():Database2("root","hello123"){
		//1. Initialize member variables
		//2. do any setup steps necessary for the class to be used
		//	2.1 Discover the server.
		//	2.2 Connect to server
		//	2.3 Authentication
	}

	Database2(const string &userName,const string &password){
		//1. Initialize member variables
		//2. do any setup steps necessary for the class to be used
		//	2.1 Discover the server.
		DiscoverServer();
		//	2.2 Connect to server
		ConnectServer();
		//	2.3 Authentication
		Authenticate(userName,password);

	}
	~Database2(){
		//Make cleanup operations (data | logic)
		//- Make opposit steps made in constructor.
	}

	void DiscoverServer(){

	}
	void ConnectServer(){

	}
	void Authenticate(const string &userName,const string &password){

	}
};

void func(Dummy2 dummy2Obj){

}

int main() {
	MyString teacherName("Ezz");				//Parametrized constructor is called.
	MyString studentName1;						//Default constructor is called
	MyString studentName(teacherName);			//Here copy constructor is called and make deep copy

	teacherName.print();						//Using the print function in Mystring class.

	studentName.print();						//It should print Ezz since it is copied from teacherName object
	studentName.setLiterals("Amy");				//Modifying student name using setLiterals method

	studentName.print();						//It should print Amy
	teacherName.print();						//It should print Ezz not Amy, since both are 2 different locations

	MyString *namePtr = new MyString("ezz");	//Allocate object dynamically in heap

	Dummy dummyObj(10);							//If I haven't sent 10 to initialize x,
	//	initial value (15) in parametrized constructor will be taken

	Employee employeeObj(0);
	//1st jump to Employee(int id)
	//2nd create data members of Employee class, which will jump to MyString() (Default constructor)
	//3rd start code of Employee(int id), and when we say myStringObj = "Ahmed"; it will jump to MyString(const char *inputLiterals)
	//	which is the parametrized constructor.

	//In the previous, I need to call the parametrized constructor only, so I will use member initializer list
	/* This is how the Employee constructor should be defined:
	 * Employee(int id): myStringObj(id == 1? "Ahmed" : "Mohamed") {}
	 */

	/*In general, to convert the mystring data members to be init using member init list:
	 * MyString():
	 * 	literals(nullptr),
	 * 	size(0)
	 * {}
	 * MyString(const char *inputLiterals):
	 * 	size(strlen(inputLiterals)),
	 *  literals(new char[size + 1])
	 * {
	 * 		memcpy(literals,inputLiterals,size);
	 * 		literals[size] = '\0';
	 * }
	 *
	 */


	//3 Ways to construct object from a class
	//1. MyString studentName;
	//2. MyString teacherName("Ezz");
	//3. MyString teacherName = "Ezz";

	Dummy2 dummy2Obj(10);			//Dummy2 dummy2Obj; will give error, cuz no default constructor
	func(dummy2Obj);				//func(10); will give error message due to oblige complier not to make implicit casting



	return 0;
}
