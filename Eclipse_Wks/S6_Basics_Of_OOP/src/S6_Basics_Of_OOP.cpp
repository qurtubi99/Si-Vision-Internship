//============================================================================
// Name        : S6_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>

/****************************************************************************************************************************************/
//1. Changing an inherited member’s access level by [using] keyword
//	 What is the problem solved by using keyword?
//	 ....
class Base {
protected:
	void print() {
		std::cout << "Print function called\n";
	}
public:
	Base(){
		std::cout << "Default constructor of Base is called\n";
	}

	~Base(){
		std::cout << "Destructor of Base is called\n";
	}
};

class Child1 : public Base {
public:
	//Change the access level of the function print from protected to public in Child1 class
	using Base::print;

	Child1(){
		std::cout << "Default constructor of Child1 is called\n";
	}

	~Child1(){
		std::cout << "Destructor of Child1 is called\n";
	}

};

class Child2 : public Child1 {
public:
	//print will be public since it was public in child1
	Child2(){
		std::cout << "Default constructor of Child2 is called\n";
	}

	~Child2(){
		std::cout << "Destructor of Child2 is called\n";
	}
};

/****************************************************************************************************************************************/
//2. Multiple inheritance (child inherit from 2 parents or more) [not preferred due to Diamod problem]
#define TEAM_LEADER 10
#define MANAGER		20
class Base1 {
protected:
	int role;
public:
	Base1() : role(0){
		std::cout << "Default constructor of Base1 is called\n";
	}

	Base1(const int role) : role(role){
		std::cout << "Default constructor of Base1 is called\n";
	}

	~Base1(){
		std::cout << "Destructor of Base1 is called\n";
	}
};
//Parent1 inherit from Base1 class
class Parent1 : public Base1 {
public:
	Parent1():Base1(TEAM_LEADER){
		std::cout << "Default constructor of Parent1 is called\n";
	}

	~Parent1(){
		std::cout << "Destructor of Parent1 is called\n";
	}
};

//Parent2 inherit from Base1 class
class Parent2 : public Base1{
public:
	Parent2():Base1(MANAGER){
		std::cout << "Default constructor of Parent2 is called\n";
	}

	~Parent2(){
		std::cout << "Destructor of Parent2 is called\n";
	}

};


class Child : public Parent1,public Parent2 {
public:
	//Inherit from Parent1 and Parent2
	Child(){
		std::cout << "Default constructor of Child is called\n";
	}

	void print(){
		std::cout << "Print function in child class\n";
		std::cout << "Role in Parent1 class: " << Parent1::role << "\n";
		std::cout << "Role in Parent2 class: " << Parent2::role << "\n";
		// if I didn't use scope resolution operator, I will get error [Diamod problem]
	}

	~Child(){
		std::cout << "Destructor of Child is called\n";
	}
};
/****************************************************************************************************************************************/
//3. Static casting:[case1 impilicit upward casting by the compiler]
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

	//Destructor
	~MyString(){
		std::cout << "Destructor of MyString is called\n";
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}
};

//If the parent has user-defined special member function, create them also for the child to avoid lossing degree of freedom when
//creating object of this child class
class MyStringImproved : public MyString{
private:
	int *ptr;
public:
	//Method members
	MyStringImproved() : ptr(new int){
		std::cout << "Default constructor of MyStringImproved is called\n";
	}

	//Parametrized constructor takes pointer to character
	MyStringImproved(const char *inputLiterals) : MyString(inputLiterals),ptr(new int){
		std::cout << "Parametrized constructor of MyStringImproved is called\n";
	}

	//- copy constructor takes MyString object by reference
	//- If I didn't delegate any of MyString constructors, hence compiler will call default one
	//- Copy constructor of MyString takes MyString object, but I passed to it MyStringImproved object
	//	so the compiler made implicit upward casting (child > parent) from MyStringImproved to MyString
	//	cuz child is a parent [after inheritance].
	//- Downward casting (parent > child)
	MyStringImproved(const MyStringImproved &other) : MyString(other),ptr(new int){
		std::cout << "Copy constructor of MyStringImproved is called\n";
		memcpy(ptr,other.ptr,sizeof(int));
	}

	~MyStringImproved(){
		std::cout << "Destructor of MyStringImproved is called\n";
		if(ptr != NULL){
			delete ptr;
		}
	}

};
/****************************************************************************************************************************************/
//4. Static casting:[case2 explicit upward]
class Parent3{
private:
	int parentNum;
public:
	Parent3() : parentNum(10){
		std::cout << "Default constructor of Parent3 is called\n";
	}

	void print(){
		std::cout << "Parent3 is here\n";
	}

	~Parent3(){
		std::cout << "Destructor of Parent3 is called\n";
	}
};

class Child3 : public Parent3{
public:
	Child3(){
		std::cout << "Default constructor of Child3 is called\n";
	}

	void print(){
		std::cout <<"Child3 is here\n";
	}

	~Child3(){
		std::cout << "Destructor of Child3 is called\n";
	}
};
/****************************************************************************************************************************************/
//5. Static casting [case3 explicit downward]:
enum ClassId{	//enum ClassId [In c]== enum class ClassId [In cpp], but in cpp, I wil have to say ClassId::e_Class11 instead of Class11
	e_Class11,
	e_Class22
};

class Base11{
private:
	//This is not the best solution, cuz the parent now knows info about childs.
	ClassId classId;
public:
	Base11(ClassId classId) : classId(classId){

	}

	ClassId getClassId() const {
		return classId;
	}
};

class Class22 : public Base11{
public:

	Class22() : Base11(e_Class22){
		std::cout << "Default constructor of Class22 is called\n";
	}

	void executeClass22Task(){
		std::cout <<"Class22 – executeClass22Task function\n";
	}

	~Class22(){
		std::cout << "Destructor of Class22 is called\n";
	}
};

class Class11 : public Base11{
public:
	Class11() : Base11(e_Class11){
		std::cout << "Default constructor of Class11 is called\n";
	}

	void executeClass11Task(){
		std::cout <<"Class11 – executeClass11Task function\n";
	}

	~Class11(){
		std::cout << "Destructor of Class11 is called\n";
	}
};

class Container1{
private:
	//Since Class11 is a Base11 class, and Class22 is a Base11 class, hence I can point to it using ptr to Base11.
	// this is one of the use cases of inheritance.
	Base11 **ptrToObjectAddress;
	int size;
	int i;
public:
	Container1(const int size) : ptrToObjectAddress(new Base11*[size]),size(size),i(0){
		std::cout << "Default constructor of Container1 is called\n";
	}

	void addElement(Base11 *ptrToObject){
		std::cout <<"addElement function in Container1 class\n";
		if(i == size)
		{
			return;
		}
		ptrToObjectAddress[i] = ptrToObject;
		i++;
	}

	void executeFunction(){
		std::cout <<"executeFunction function in Container1 class\n";

		for(int j=0;j<i;j++){
			if(ptrToObjectAddress[j]->getClassId() == e_Class11){
				//Downward casting (parent -> child)
				static_cast<Class11*>(ptrToObjectAddress[j])->executeClass11Task() ;
			}else if(ptrToObjectAddress[j]->getClassId() == e_Class22){
				//Downward casting (parent -> child)
				static_cast<Class22*>(ptrToObjectAddress[j])->executeClass22Task() ;
			}else{
				//Through error
			}

		}
	}

	~Container1(){
		std::cout << "Destructor of Container1 is called\n";
	}
};
/****************************************************************************************************************************************/
//6. Tricky question[1]:
class Base6 {
protected:
	std::string name = "Base6\n";
public:
	std::string getName() { return name; };
};
class Child6 : public Base6 {
protected:
	std::string name = "Child6\n";
};


class Base62 {
protected:
	std::string name = "Base62";
public:
	std::string getName() {
		return name;
	};
};
class Child62 : public Base62 {
protected:
	std::string name = "Child62";
public:
	std::string getName() {
		return name;
	};
};

//6. Tricky question[3]:
class Base63 {
public:
	std::string getName() {
		return "Base63";
	};
};
class Child63 : public Base63 {
public:
	std::string getName() {
		return "Child63";
	};
};
/****************************************************************************************************************************************/
//7. Virtual function: repeat example in [5] to illustrate what virtual has solved

class Base7{
public:
	Base7(){

	}
	//This will enable me to have a reference to executeClass function in child class when upward casting happens.
	virtual void executeClass(){
		std::cout <<"Base7 – executeClass function in base7 class\n";
	}

};

class Class72 : public Base7{
public:

	Class72(){
		std::cout << "Default constructor of Class72 is called\n";
	}

	void executeClass(){
		std::cout <<"Class72 – executeClass function in Class72 class\n";
	}

	~Class72(){
		std::cout << "Destructor of Class72 is called\n";
	}
};

class Class71 : public Base7{
public:
	Class71(){
		std::cout << "Default constructor of Class71 is called\n";
	}

	void executeClass(){
		std::cout <<"Class71 – executeClass function in Class71 class\n";
	}

	~Class71(){
		std::cout << "Destructor of Class71 is called\n";
	}
};

class Container7{
private:
	Base7 **ptrToObjectAddress;
	int size;
	int i;
public:
	Container7(const int size) : ptrToObjectAddress(new Base7*[size]),size(size),i(0){
		std::cout << "Default constructor of Container7 is called\n";
	}

	//Implicit upward casting [child -> Base7]
	void addElement(Base7 *ptrToObject){
		std::cout <<"addElement function in Container7 class\n";
		if(i == size)
		{
			return;
		}
		ptrToObjectAddress[i] = ptrToObject;
		i++;
	}

	void executeFunction(){
		std::cout <<"executeFunction function in Container7 class\n";

		for(int j=0;j<i;j++){
			ptrToObjectAddress[j]->executeClass();
		}
	}

	~Container7(){
		std::cout << "Destructor of Container7 is called\n";
	}
};
/****************************************************************************************************************************************/


int main() {
	/****************************************************************************************************************************************/
	//1. Changing an inherited member’s access level by [using] keyword
	{
		std::cout << "1. Changing an inherited member’s access level by [using] keyword: \n";
		Child1 child1Obj1;
		Child2 child2Obj1;
		//Allocation of child1Obj1 >> Constructor of base > child1
		//Allocation of child2Obj1 >> Constructor of base > child1 > child2

		child1Obj1.print();
		child2Obj1.print();
		//Deallocation of child1Obj1 >> Destructor of child1 > base
		//Deallocation of child2Obj1 >> Destructor of child2 > child1 > base
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//2. Multiple inheritance (child inherit from 2 parents or more) [not preferred due to Diamod problem]
	{
		std::cout << "2. Multiple inheritance (child inherit from 2 parents or more) [not preferred]: \n";
		Child childObj1;
		childObj1.print();
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//3. Static casting:[case1 impilicit upward casting by the compiler]
	{
		std::cout << "3. Static casting [case1 impilicit upward casting by the compiler]: \n";
		MyString myStringObj1("Ali Nasr");
		MyString myStringObj2(myStringObj1);
		MyStringImproved myStringImprovedObj1("Ahmed");
		MyStringImproved myStringImprovedObj2(myStringImprovedObj1);
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//4. Static casting:[case2 explicit upward]
	{
		std::cout << "4. Static casting [case2 expilicit upward]: \n";
		Child3 child3Obj1;
		child3Obj1.print();										//Child is here.

		//- Compiler make implicit upward casting [Child3 -> Parent3] and shallow copy for parent3 part in child3Obj1 to  parent3Obj1
		//- Here, the copy constructor will be implemented implicitly by the compiler.
		Parent3 parent3Obj1(child3Obj1);
		parent3Obj1.print();									//Hence will print parent is here.

		//Expilcit upward casting [Child3 -> Parent3] and shallow copy for parent3 part in child3Obj1 to  parent3Obj1
		Child3 child3Obj2;
		static_cast<Parent3>(child3Obj2).print();				//Hence will print parent is here.


	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//5. Static casting [case3 explicit downward]:
	{
		/*****************************Better method**************************/
		std::cout << "5. Static casting [case3 expilicit downward]: \n";
		Container1 c(10);		//The # of pointers to objects in heap = 10
		Class11 *c1 = new Class11;
		Class22 *c2 = new Class22;

		c.addElement(c1);		//Upward implicit casting made by compiler from Class11 -> Base11
		c.addElement(c2);		//Upward implicit casting made by compiler from Class22 -> Base11

		c.executeFunction();

		delete c1;				//Destruction of c1 object memory location in heap
		delete c2;              //Destruction of c2 object memory location in heap
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//6. Tricky question[1]:
	{
		std::cout << "6. Tricky question[1]: \n";
		Child6 c;
		std::cout << c.getName() << "\n";	//will print Base6 or child6?


		//6. Tricky question[2]:
		std::cout << "6. Tricky question[2]: \n";
		Child62 c62;
		std::cout << c62.getName() << "\n";	//will print Base62 or child62?
		//How to force it to print Base62?
		//Method1 using explicity upward casting
		std::cout << static_cast<Base62>(c62).getName() << "\n";
		//Method2 using scope resolution operator
		std::cout << (c62).Base62::getName() << "\n\n";

		//6. Tricky question[3]:
		std::cout << "6. Tricky question[3]: \n";
		Child63 c63;
		std::cout << c63.getName() << "\n";			//will print Base63 or child63?
		Base63& refBase = c63;						//Implicit upward castin by the compiler
		std::cout << refBase.getName() << "\n";     //will print Base63 or child63?
		Base63* ptrBase = &c63;						//Implicit upward castin by the compiler
		std::cout << ptrBase->getName() << "\n";    //will print Base63 or child63?
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//7. Virtual function: repeat example in [5] to illustrate what virtual has solved
	{
		std::cout << "7. Virtual function: repeat example in [5] to illustrate what virtual has solved: \n";
		Container7 c7(10);		//The # of pointers to objects in heap = 10
		Class71 *c71 = new Class71;
		Class72 *c72 = new Class72;

		c7.addElement(c71);		//Upward implicit casting made by compiler from Class71 -> Base7
		c7.addElement(c72);		//Upward implicit casting made by compiler from Class72 -> Base7

		//There is a runtime check to know the upward casting [child -> Base7] happended from which child [Class71 or Class72]
		//This is called runtime polymorphism (virtual function)
		c7.executeFunction();

		delete c71;				//Destruction of c71 object memory location in heap
		delete c72;              //Destruction of c72 object memory location in heap

		//Compile time polymorphism: 1. parametric polymorphism(function templates "cpp concept") 2. Ad-hoc polymorphism(function overloading "name mangling")

		//Runtime polymorphism works with reference/pointers only:
		//	- In runtime when an object of the base task is created upon creation of one of its childs, a virtual pointer will be created
		//	  in the scope of the parent.
		//	- The virtual pointer points to heap location (virtual table) that contains the addresses of all the functions that overwrite the virtual function in the parent class.
		//If I used virtual and did't overwrite this function in child >> error.
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	return 0;
}
