//============================================================================
// Name        : S5_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <string.h>

/****************************************************************************************************************************************/
//1. Assignment operator (difference between it and the copy constructor) & Rule of 3
//Rule of 3: "This rule is only a programmer-guide rule."
//	- Comiler by default generate default destructor, copy constructor and assignment operator,
//	  so if I have defined any of these, hence most probably I make dynamic allocation in my code,
//	  hence I should define the rest to avoid errors from shallow copy.
class MyString{
private:
	//Data members
	int size;
	char *literals;
public:
	//Method members
	MyString(){
		std::cout << "Default constructor of MyString is called\n";

		literals = nullptr;
		size = 0;
	}

	//Parametrized constructor takes pointer to character
	MyString(const char *inputLiterals){
		std::cout << "Parametrized constructor of MyString is called\n";
		size = strlen(inputLiterals);
		literals = new char[size + 1];
		memcpy(literals,inputLiterals,size);
		literals[size] = '\0';
	}

	//copy constructor takes MyString object by reference
	MyString(const MyString &other): MyString(other.literals){
		std::cout << "Copy constructor of MyString is called\n";
	}

	void print(){
		std::cout << "Literals: " << literals << "\n";
	}

	//Getter for the size
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

	//Assignment operator
	MyString& operator=(const MyString &other){
		std::cout<<"Assignment Operator= in Mystring class called\n";
		if(literals != nullptr){
			delete []literals;
		}
		size = other.size;
		literals = new char [size+1];
		memcpy(literals,other.literals,size);
		literals[size]='\0';
		return *this;
	}

	//Destructor
	~MyString(){
		std::cout << "Destructor of MyString is called\n\n";
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}
};
/****************************************************************************************************************************************/
//2.Inheritance: Can access public and protected directly inside child class scope
class Parent{
private:
	int privateNum;
protected:
	int protectedNum;
public:
	int publicNum;
	Parent():privateNum(10),protectedNum(20),publicNum(30){
		std::cout << "Default constructor of Parent is called\n";
	}

	//To be able to access private members in the class that inherit from me.
	void setPrivateNum(int privateNum) {
		std::cout << "setPrivateNum in Parent is called\n";
		this->privateNum = privateNum;
	}

	int getPrivateNum() const {
		return privateNum;
	}

	~Parent(){
		std::cout << "Destructor of Parent is called\n\n";
	}
};

//Child is a Parent (only access to public and protected members)
//Child class (child/derived) inherit from Parent class (Parent/Base)
class Child : public Parent{
public:
	Child(){
		std::cout << "Default constructor of Child is called\n";
	}
	void print(){
		std::cout << "Protected data member: " << protectedNum<<"\n";
		std::cout << "Public data member   : " << publicNum<<"\n";
		std::cout << "Private data member  : " << getPrivateNum() << "\n";
	}
	~Child(){
		std::cout << "Destructor of Child is called\n\n";
	}
};
/****************************************************************************************************************************************/
//3.Delegation in inheritance (not exactly but same concept):
class Employee{
private:
	int age;
public:
	Employee():age(0){
		std::cout << "Default constructor of Employee is called\n";
	}
	Employee(const int age):age(age){
		std::cout << "Parametrized constructor of Employee is called\n";
	}
	~Employee(){
		std::cout << "Destructor of Employee is called\n\n";
	}
};

class TeamLeader:public Employee{
public:
	//The compiler does the following >> TeamLeader():Employee(){}
	TeamLeader(){
		std::cout << "Default constructor of TeamLeader is called\n";
	}

	//Delegation to call parametrized constructor instead of default
	TeamLeader(const int age):Employee(age){
		std::cout << "Parametrized constructor of TeamLeader is called\n";
	}

	~TeamLeader(){
		std::cout << "Destructor of TeamLeader is called\n\n";
	}
};
/****************************************************************************************************************************************/
//5. Function overridding (redifination) in inheritance: child class override function in parent class
class Employee2{
private:
	int age;
public:
	Employee2():age(0){
		std::cout << "Default constructor of Employee2 is called\n";
	}
	Employee2(const int age):age(age){
		std::cout << "Parametrized constructor of Employee2 is called\n";
	}
	void signIn(){
		std::cout << "sigIn in Empolyee2 class " << age << "\n";
	}

	int getAge() const {
		return age;
	}

	~Employee2(){
		std::cout << "Destructor of Employee2 is called\n\n";
	}
};

class TeamLeader2: public Employee2{
public:
	//The compiler does the following >> TeamLeader2():Employee(){}
	TeamLeader2(){
		std::cout << "Default constructor of TeamLeader2 is called\n";
	}

	//Delegation to call parametrized constructor instead of default
	TeamLeader2(const int age):Employee2(age){
		std::cout << "Parametrized constructor of TeamLeader2 is called\n";
	}
	void signIn(){
		Employee2::signIn();	//To implement same thing in parent signIn function
		std::cout << "sigIn in TeamLeader2 class " << getAge() << "\n";
	}

	~TeamLeader2(){
		std::cout << "Destructor of TeamLeader2 is called\n\n";
	}
};
/****************************************************************************************************************************************/

int main() {
	/****************************************************************************************************************************************/
	//1. Assignment operator (difference between it and the copy constructor) & Rule of 3
	{
		std::cout<<"1. Assignment operator (difference between it and the copy constructor)\n";
		MyString MyStringObj1("Ahmed");
		MyString MyStringObj2("Mohamed");
		MyString MyStringObj3(MyStringObj2);	 		 //Copy constructor will create new location for literals in memory (heap)
		MyStringObj3.print();
		MyStringObj3 = MyStringObj2 = MyStringObj1;		 //Assignment operator will replace Ahmed with Mohamed, and I've already created heap loacation for MyStringObj2
		// 1st Obj1>obj2 then obj2>obj1
		MyStringObj1.print();
		MyStringObj2.print();
		MyStringObj3.print();
	}
	/****************************************************************************************************************************************/
	//2.Inheritance: Can access public and protected directly inside child class scope
	{
		std::cout<< "2.Inheritance:\n";
		Child ChildObj1;
		//Now ChildObj1 created 3 memory locations for the 3 data members it inherit from parent.
		//Default constructor of Parent > create its data members (and member init list),
		//then Default constructor of Child > create its data members (and member init list),
		ChildObj1.print();	           //Print the data members of ChildObj1
		ChildObj1.setPrivateNum(100);
		ChildObj1.print();	           //Print the data members of ChildObj1
	}								   //Destructor of child then parent
	/****************************************************************************************************************************************/
	//3.Delegation in inheritance (not exactly but same concept):
	{
		std::cout<< "3.Delegation in inheritance (not exactly but same concept):\n";
		TeamLeader TeamLeaderObj1(50);
	}
	/****************************************************************************************************************************************/
	//4. Inheritance access specifiers:
	/*
	 * Public   : All members in parent are inherited with same access specifier
	 * Protected: public in parent will be protected in child
	 * Private  : All members in parent will be privaete in child.
	 */
	/****************************************************************************************************************************************/
	//5. Function overridding (redifination) in inheritance: child class override function in parent class
	{
		TeamLeader2 TeamLeader2Obj1;
		TeamLeader2Obj1.signIn();
	}
	/****************************************************************************************************************************************/
	return 0;
}
