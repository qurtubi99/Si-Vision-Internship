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

/****************************************************************************************************************************************/
//1. Classes, access specifiers, Constructors(defalut, parametrized & copy), destructor, setters, getters, RVO & delegating constructors:
//	- Access Specifiers/Modifiers:
//		- Public: Data and function members can be accessed outside the class
//		- Private: Data and function members can not to be accessed outside the class. Friend functions and class can only access them.
//		- Protected: Data and function members are can not be accessed outside the class but they can be accessed by any derived classes (inheritance)
class MyString{
private:
	//Data members
	int size;
	char *literals;
public:
	//Method members
	//Default constructor (no i/p arguments/parameters)
	MyString(){
		cout << "Default constructor of MyString is called\n";

		//1. Initialize member variables
		literals = nullptr;
		size = 0;

		//2. do any setup steps necessary for the class to be used.
	}

	//Parametrized constructor takes pointer to character
	//- inputLiterals must be defined const, to delay destruction of temporary memory location allocated by the compiler for the passed
	//	R-value string till the complete implementation for the parametrized constructor
	MyString(const char *inputLiterals){
		cout << "Parametrized constructor of MyString is called\n";
		size = strlen(inputLiterals);
		literals = new char[size + 1];			//+1 for '\0'
		memcpy(literals,inputLiterals,size);
		literals[size] = '\0';

	}

	//Copy constructor defined in this way (const and pass by reference) ; cuz the compiler define it in the same way
	//The compiler can perform copy elision by implementing Return Value Optimization (RVO)
	// When is the copy constructor called?
	//	- When an object of the class is returned by value. [create temp class, copy the data in it then return it]
	//	- When an object of the class is passed (to a function) by value as an argument
	//	- When an object is constructed based on another object of the same class
	//	- When the compiler generates a temporary object
	/*
	 	// Without RVO
		std::string f() {
		  std::string s = "Hello";
		  return s; // copy s to a temporary object
		}

		std::string t = f(); // copy the temporary object to t

		// With RVO
		std::string f() {
		  std::string s = "Hello";
		  return s; // no copy, s is constructed directly into the storage of the return value
		}

		std::string t = f(); // no copy, t is initialized from the return value

	 */
	//copy constructor takes MyString object by reference
	MyString(const MyString &other):
		size(other.size),
		literals(new char[size + 1])
	{
		cout << "Copy constructor of MyString is called\n";
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
	//const after getSize() gureantees that the data member I return must be read only, and give error, if I've returned it by reference
	//	or modified it in the getter function.
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
	//- called when stack-allocated objects go out of scope or when delete is called on heap-allocated objects.
	~MyString(){
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}
};

/****************************************************************************************************************************************/
//2. What exactly should I do in constructors and destructors?
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

/****************************************************************************************************************************************/
//3. Parametrized constructor with initial value:
class Dummy{
private:
	int x;
public:
	//Parametrized constructor with initial value.
	Dummy(int xInput = 15){
		cout<<"Parametrized constructor in Dummy class.\n";
		x = xInput;
	}
};

/****************************************************************************************************************************************/
//4. Initializer list with constructors:

class Employee{
private:
	MyString myStringObj;
public:

	/*Default constuctor rules:
		– Constructors must have the same name as the class
		– Constructors have no return type (not even void)
		– Constructors can be overloaded. [1. Default constructor 2. Parametrized constructor 3. Copy constructor...]
		– Constructors can take default arguments
		– If it’s not defined, then compiler will implicitly define a default one.
	 */
	Employee(){

	}

	//Parametrized constructor
	//	- If the id parameter was received by reference (int &id), it should have been defined
	//		as constant incase the employee object was defined with passing R-value id (e.g. Employee employee(5);)
	Employee(int id){
		cout<<"Parametrized constructor in Employee class.\n";
		if(id == 0){
			myStringObj = "Ahmed";
		}else{
			myStringObj = "Mohamed";
		}
	}
};

/****************************************************************************************************************************************/
//5. Expicit keyword with constructors:

class Dummy2{
private:
	int x;

public:
	explicit Dummy2(int x):x(x){
		cout<<"Parametrized constructor in Dummy2 class.\n";
	}
};

/****************************************************************************************************************************************/
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
		cout<<"Default constructor in Database2 class.\n";
	}

	Database2(const string &userName,const string &password){
		cout<<"Parametrized constructor in Database2 class.\n";
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
		cout<<"Destructor in Database2 class.\n";
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

/****************************************************************************************************************************************/
// Interview Question: One line used to calculate the execution time of a function

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
/****************************************************************************************************************************************/
int main() {
	/****************************************************************************************************************************************/
	MyString teacherName("Ezz");				//Parametrized constructor is called.
	MyString studentName1;						//Default constructor is called
	MyString studentName(teacherName);			//Here copy constructor is called and make deep copy

	teacherName.print();						//Using the print function in Mystring class.

	studentName.print();						//It should print Ezz since it is copied from teacherName object
	studentName.setLiterals("Amy");				//Modifying student name using setLiterals method

	studentName.print();						//It should print Amy
	teacherName.print();						//It should print Ezz not Amy, since both are 2 different locations

	MyString *namePtr = new MyString("ezz");	//Allocate object dynamically in heap

	/****************************************************************************************************************************************/
	//3. Parametrized constructor with initial value:
	Dummy dummyObj(10);			//If I haven't sent 10 to initialize x, initial value (15) in parametrized constructor will be taken

	/****************************************************************************************************************************************/
	//4. Initializer list with constructors:
	Employee employeeObj(0);

	//1st jump to Employee(int id)
	//2nd create data members of employeeObj, which will jump to MyString() (Default constructor)
	//3rd start code of Employee(int id) "Default constructor", and when we say myStringObj = "Ahmed"; it will jump to
	// MyString(const char *inputLiterals) which is the parametrized constructor.

	//In the previous, I need to call the parametrized constructor only (not default >> parametrized), so I will use member initializer list
	/* This is how the Employee constructor should be defined:
	 * Employee(int id): myStringObj(id == 1? "Ahmed" : "Mohamed") {}
	 */

	/*In general, to convert the mystring data members to be init using member init list default/parametrized constructors look like that:
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
	/****************************************************************************************************************************************/

	//3 Ways to construct object from a class
	//1. MyString studentName;
	//2. MyString teacherName("Ezz");	 >> This will call parametrized constructor directly.
	//3. MyString teacherName = "Ezz";   >> This will allocate temporary object with ezz, then copy it to teacherName object using copy constructor

	/****************************************************************************************************************************************/
	//5. Expicit keyword with constructors:
	Dummy2 dummy2Obj(10);			//Dummy2 dummy2Obj; will give error, cuz no default constructor
	func(dummy2Obj);				//func(10); will give error message due to oblige complier not to make implicit casting

	/****************************************************************************************************************************************/



	return 0;
}
