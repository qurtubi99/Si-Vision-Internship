//============================================================================
// Name        : S2_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : S2
//============================================================================

#include <iostream>
#include <string.h>


/****************************************************************************************************************************************/
//1. Classes, access specifiers, Constructors(defalut, parametrized & copy), destructor, setters, getters, RVO & delegating constructors:
//	- Access Specifiers/Modifiers:
//		- Public:    Data and function members can be accessed outside the class
//		- Private:   Data and function members can not be accessed outside the class. Friend functions/classes can only access them.
//		- Protected: Data and function members can not be accessed outside the class but they can be accessed by any derived classes (inheritance)
//					 and by friend functions/classes
class MyString{
private:
	//Data members
	int size;
	char *literals;
public:
	//Method members
	//Default constructor (no i/p arguments/parameters)
	MyString(){
		std::cout << "Default constructor of MyString is called\n";

		//1. Initialize member variables
		literals = nullptr;
		size = 0;

		//2. do any setup steps necessary for the class to be used.
	}

	//Parametrized constructor takes pointer to character
	//- inputLiterals must be defined const, to delay destruction of temporary memory location allocated by the compiler for the passed
	//	R-value string till the complete execution for the parametrized constructor
	MyString(const char *inputLiterals){
		std::cout << "Parametrized constructor of MyString is called\n";
		size = strlen(inputLiterals);
		literals = new char[size + 1];			//+1 for '\0'
		memcpy(literals,inputLiterals,size);
		literals[size] = '\0';

	}

	//Copy constructor defined in this way (const and pass by reference) ; cuz the compiler define it in the same way implicitly, & I'm overriding it
	//The compiler can perform copy elision by implementing Return Value Optimization (RVO)
	//Problem:
	//	When I dynamically allocate memory in heap, then want to create a new object from object1 without defining copy constructor,
	//	the compiler will make deep copy, which will copy the content of object1 by value, even the address of the heap location.
	//	Upon destruction, the destructor of obj1 and obj2 both will deallocate same memory location >> runtime error.
	//When is the copy constructor called?
	//	- When an object is constructed based on another object of the same class
	//	- When the compiler generates a temporary object
	//	- When an object of the class is passed or returned [create temp class, copy the data in it then return it] by value.
	/*
	 	// Without RVO
		std::string f() {
		  std::string s = "Hello";
		  return s; // copy s to a temporary object
		}

		std::string t = f(); // copy the temporary object to t then destroy temp object.

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
		std::cout << "Copy constructor of MyString is called\n";
		memcpy(literals, other.literals, size);
		literals[size] = '\0';
	}

	//Since the copy constructor makes same things in parametrized constuctor, I may delegate it as follows
	/*
	 	MyString(const MyString &other): MyString(other.literals){
			cout << "Copy constructor is called\n";
		}
	 */


	void print(){
		std::cout << "Literals: " << literals << "\n";
	}

	//Getter for the size
	//A const member function promises not to modify any member variables of the class. And give error if I've returned it by reference.
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
		std::cout << "Destructor of MyString is called\n";
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}
};

MyString createSting(){
	MyString temp("123");
	return temp;
}

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
//3. Parametrized constructor with default value:
class Dummy{
private:
	int x;
public:
	//Parametrized constructor with initial value.
	Dummy(int xInput = 15){
		std::cout<<"Parametrized constructor in Dummy class.\n";
		x = xInput;
	}

	//To auto generate setters and getters:
	//>> right click on class name > source >  Generate stters and getters
	int getX() const {
		return x;
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
	Employee(int id)/*Here the default constructro of myStringObj will be called (initialized in this line)*/{
		std::cout<<"Parametrized constructor in Employee class.\n";
		if(id == 0){
			myStringObj.setLiterals("Ahmed");

			//myStringObj = "Ahmed";
			//Here the parametrized constructor of MyString is called > a temporary object of MyString is created to store "Ahmed"
			//> the default assignment operator [later] will assign this temporary object to myStringObj > destructor of temporary object occurs
			//[since the temporary object is created within the parametrized constructor of myStringObj, hence the temporary object will
			//call the destructor of myStringObj]
			//So, the destructor will be called twice (1 for temp object, 2nd for myStringObj), and to avoid this problem, I've to follow rule
			//of 3 [later in the course]

		}else{
			myStringObj.setLiterals("Mohamed");
			//myStringObj = "Mohamed";
		}
	}
	//Another implementation for the parametrized constructor to avoid calling default then parametrized constructor of myStringObj if I said:
	//myStringObj = "Mohamed" in the body of the parametrized cosntructor of Employee
	/*
		Employee(int id) : myStringObj(id == 0? "Ahmed" : "Mohamed"){
			std::cout<<"Parametrized constructor in Employee class.\n";
		}
	 */
};

/****************************************************************************************************************************************/
//5. Expicit keyword with constructors:
class Dummy2{
private:
	int x;

public:
	explicit Dummy2(int x):x(x){
		std::cout<<"Parameterized constructor in Dummy2 class.\n";
	}
};

/****************************************************************************************************************************************/
//Example to explain delegation in calsses:
class Database2{
public:
	//Delegating the parameterized constructor.
	Database2():Database2("root","hello123"){
		std::cout<<"Default constructor in Database2 class.\n";
	}

	Database2(const std::string &userName,const std::string &password){
		std::cout<<"Parameterized constructor in Database2 class.\n";
		//	2.1 Discover the server.
		DiscoverServer();
		//	2.2 Connect to server
		ConnectServer();
		//	2.3 Authentication
		Authenticate(userName,password);

	}
	~Database2(){
		std::cout<<"Destructor in Database2 class.\n";
		//Make cleanup operations (data | logic)
		//- Make opposit steps made in constructor.
	}

	void DiscoverServer(){

	}
	void ConnectServer(){

	}
	void Authenticate(const std::string &userName,const std::string &password){

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
		std::cout << executionTime.seconds << "\n";
	}
};

void func(){
	Execution_Time execution_TimeObject;
}
/****************************************************************************************************************************************/
int main() {
	/****************************************************************************************************************************************/
	//1. Classes, access specifiers, Constructors(defalut, parametrized & copy), destructor, setters, getters, RVO & delegating constructors:
	{
		std::cout<<"1. Classes, access specifiers, Constructors(defalut, parametrized & copy), destructor, setters, getters, RVO & delegating constructors: \n";
		{
			MyString teacherName("Ezz");				//Parametrized constructor is called.
			MyString studentName1;						//Default constructor is called
			MyString studentName(teacherName);			//Here copy constructor is called and make deep copy
			MyString studentName2 = studentName1;		//Here copy constructor is called and make deep copy

			teacherName.print();						//Using the print function in Mystring class.

			studentName.print();						//It should print Ezz since it is copied from teacherName object
			studentName.setLiterals("Amy");				//Modifying student name using setLiterals method

			studentName.print();						//It should print Amy
			teacherName.print();						//It should print Ezz not Amy, since both are 2 different locations

			MyString *namePtr = new MyString("ezz");	//Allocate object dynamically in heap
		}

		std::cout << "------------------\n";
		MyString numbers = createSting();
		//1. Make function call (assignment operator precedance from right to left) 			   & parametrized CTOR of temp called.
		//2. Compiler create temporary object in memory and copy in it same values in temp object. & copy CTOR called for numbers to copy
		//	 the temporary location to numbers.
		//3. Destructor of temp cuz the function ended.
		//4. Destructor of numbers.
		//If RVO [return value optimization] enabled: "Compiler depended, hence I mustn't depend on it"
		//	>> no copy CTOR called, "123" constructed directly into the storage of numbers
		//	   In another word, the compiler replaced MyString numbers = createSting(); >> MyString numbers("123");
		//	   Hence, parametrized CTOR and Destructor of numbers only will be called.
		//To disable RVO:
		//	right click on project > preferences > c/c++ build > settings > c/c++ compiler > Miscellaneous > -fno-elide-constructors


	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//2. What exactly should I do in constructors and destructors?
	std::cout<<"2. What exactly should I do in constructors and destructors?\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//3. Parametrized constructor with default value:
	{
		std::cout<<"3. Parametrized constructor with initial value: \n";
		Dummy dummyObj(10);					//10 will be the initial for x value
		Dummy dummyObj2;					//15 will be the default for x value
		std::cout<<dummyObj.getX() <<"\n";
		std::cout<<dummyObj2.getX()<<"\n";

	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//4. Initializer list with constructors:
	{
		std::cout<<"4. Initializer list with constructors: \n";
		Employee employeeObj(0);

		//1st jump to Employee(int id)
		//2nd create data members of employeeObj, which will jump to MyString() (Default constructor)
		//3rd start code of Employee(int id) "Prametrized constructor", and when we say myStringObj = "Ahmed"; it will jump to
		// MyString(const char *inputLiterals) which is the parametrized constructor.

		//In the previous, I need to call the parametrized constructor of MyString only (not default >> parametrized), so I will use member initializer list
		/* This is how the Employee constructor should be defined:
		 * Employee(int id): myStringObj(id == 1? "Ahmed" : "Mohamed") {}
		 */

		/****************************************************************************************************************************************/

		//3 Ways to construct object from a class
		//1. MyString studentName;
		//2. MyString teacherName("Ezz");	 >> This will call parametrized constructor directly.
		//3. MyString teacherName = "Ezz";   >> This will allocate temporary object with ezz, then copy it to teacherName object using copy constructor
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//5. Expicit keyword with constructors:
	{
		Dummy2 dummy2Obj(10);			//Dummy2 dummy2Obj; will give error, cuz no default constructor
		func(dummy2Obj);				//func(10); will give error message due to oblige complier not to make implicit casting
	}

	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/



	return 0;
}
