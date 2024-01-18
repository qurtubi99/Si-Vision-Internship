//============================================================================
// Name        : S4_Basics_Of_OOP3.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>

/*******************************************************************************/
/*******************************************************************************/
//1. Function overloading:
//- Allows the creation of multiple functions with the same name, so long as they have different parameters.
//- Rules:
//	1. If the overloaded functions have the same number of arguments, they must have different types
//	2. Overloaded functions can have different number of arguments
//	3. Default values do not make a function unique
//		int add(int x = 10){...}
//		add(5); and add(); both will call the add function, the default value 10, doesn't indicate
//		that a different function will be called (e.g. if I have defined int add(int y){...} I will get error
//		cuz this will not be considered as overloading.)
int addOperands(int num1, int num2) {
	return num1 + num2;
}
std::string addOperands(std::string str1, std::string str2) {
	return str1 + "---" + str2;
}
/*******************************************************************************/
/*******************************************************************************/
//2. How the c++ deals with function overloading?
//	1. C++ tries to find an exact match. This is the case where  the actual argument exactly matches the parameter
//		type of one of the overloaded functions.
void print(char *value){
	std::cout<<"print char: "<<*value<<"\n";
}
void print(int value){
	std::cout<<"print int: "<<value<<"\n";
}
//	2. If no exact match is found, C++ tries to find a match through promotion (Implicit Casting).
void print2(char *value){
	std::cout<<"print2 char: "<<*value<<"\n";
}
void print2(int value){
	std::cout<<"print2 int: "<<value<<"\n";
}
//	3. If no promotion is possible, C++ tries to find a match through standard conversion.
//		1. Any numeric type will match any other numeric type.
//		2. Enum will match any numeric type.
//		3. Zero will match a pointer type and numeric type (e.g. 0 to char*, or 0 to float).
//		4. A pointer will match a void pointer
void print3(char *value){
	std::cout<<"print3 char: "<<*value<<"\n";
}
void print3(int value){
	std::cout<<"print3 int: "<<value<<"\n";
}
enum Dummy {
	FIRST,
	SECOND
};
//	4. If no matches are found, C++ tries to find a match through user-defined conversion
/*******************************************************************************/
/*******************************************************************************/
//3. How the compiler deals with function overloading and diffrentiate between functions with same name?
//	 (Name Mangling – Under the hood)
//	- Name mangling "modification" is the encoding of function and variable names into unique names so that linkers can separate common names in the language.
//	- All function names, either overloaded or not, are changed by the compiler.
//	- Name mangling is not limited to functions. It is done for classes and structures as well.
//	- Compilers use the arguments’ types to generate a unique name for each function.
/*******************************************************************************/
/*******************************************************************************/
/*4. Will this code compile?
 * 	1. 5.5 and 4.5 are double, hence 2 functions will match both availiable numeric types (int and float) -> error
  		- Solution is to make static casting: addOperands(static_cast<float>5.5, static_cast<float>4.5);
   	int addOperands(int x, int y) {
		return x+y;
	}
	float addOperands(float x, float y) {
		return x+y;
	}
	addOperands(5.5, 4.5);

	2. x here is r-value, hence can be passed to int x or int &x hence error
		void func(int x) {}
		void func(int& y) {}
		int x = 10;
		func(x);
	3. 1 is l-value, hence it can only be passed to int x -> yes will compile
		void func(int x) {}
		void func(int& y) {}
		func(1);


 */
/*******************************************************************************/
/*******************************************************************************/
//5. Operator overloading: using operators with objects instead of using setters ang getters:
//	- Compiler has built-in functions are available for primitive types only
//	- int z = x + y; -> compiler replace it with int z = operator+(x,y);
// 	where: int operator+(int x, int y) {return x+y;}
//	- Rules:
//		1. All operators can be overloaded except: conditional (?:), sizeof, scope (::), member selector (.)..
//		2. At least one of the operands in an overloaded operator must be a user-defined type.
//		3. It is not possible to change the number of operands an operator supports.
//		4. All operators keep their default precedence and associativity.
class MyString{
	//Data members
private:
	int size;
	char *literals;
	//Method members
public:
	//Default constructor (no i/p arguments/parameters)
	MyString(){
		std::cout << "Default constructor of MyString is called\n";

		//1. Initialize member variables
		literals = nullptr;
		size = 0;

		//2. do any setup steps necessary for the class to be used.
	}

	//Parametrized constructor
	//- inputLiterals must be defined const, to delay destruction of temporary memory location
	//	allocated by the compiler for the passed l-value string till the complete implementation for
	//	the parametrized constructor
	MyString(const char *inputLiterals){
		std::cout << "Parametrized constructor of MyString is called\n";
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
		std::cout << "Copy constructor is called\n";
		memcpy(literals, other.literals, size);
		literals[size] = '\0';
	}
	//Since the copy constructor makes same things in parametrized constuctor, I may delegate it as follows
	/*
	 	MyString(const MyString &other): MyString(other.literals)
		{
			std::cout << "Copy constructor is called\n";
		}
	 */


	void print(){
		std::cout<<"Literals from print method in MyString: " << literals << std::endl;
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

	//Destructor
	//- Deallocate object from memory location
	//- called when stack-allocated objects go out of scope & when delete is called on heap-allocated objects.
	~MyString(){
		std::cout << "Destructor of MyString is called\n";
		//Make cleanup operations (data | logic)
		delete []literals;			//De-allocate the used heap locations throughout the object lifetime
		size = 0;
	}

	/*******************************************************************************/
	/*******************************************************************************/
	//5. Operator overloading: using operators with objects instead of using setters ang getters:
	//Since this pointer is sent by default upon this funciton call from main, hence #of parameters are 2
	MyString operator+(const MyString &other){
		std::cout<<"operator+ of MyString is called\n";
		char *newLiterals = new char [size + other.size + 1];
		memcpy(newLiterals,literals,size);						//hello [size = 5]
		memcpy(&newLiterals[5],other.literals,other.size);		//world [size = 5]
		newLiterals[size+other.size] = '\0';					//null terminator

		//Parametrized constructor will be called.
		MyString newObject(newLiterals);

		delete[] newLiterals;
		return newObject;	//Here I return object by value, hence copy constructor will be called if ROV disabled
		//Here the newObject destructor must be called
	}
	/*******************************************************************************/
	/*******************************************************************************/
	//6. Another example on operator overloading:
	MyString operator+(const uint8_t &age){
		std::cout<<"operator+ of MyString is called\n";
		char *newLiterals = new char[size + 1 + 1];

		memcpy(newLiterals,literals,size);
		newLiterals[size] = age;
		newLiterals[size+1] = '\0';

		MyString newObject(newLiterals);
		delete[] newLiterals;
		std::cout<<"Copy & dectructor of newObject will be called\n";
		return newObject;
	}
	/*******************************************************************************/
	/*******************************************************************************/
	//10. Input/Output Operators Overloading
	friend std::ostream& operator<<(std::ostream &out,const MyString &other);
	/*******************************************************************************/
	/*******************************************************************************/

};


/*******************************************************************************/
/*******************************************************************************/
//7. Overloading operators for operands of different types: Database and Dummy2 classes
class Dummy1;
class Dummy2;

class Dummy1{
private:
	int num=20;
	friend operator+(const Dummy1 &Dummy1Obj1,const Dummy2 &Dummy2Obj1);
};

class Dummy2{
private:
	int num=40;
	friend operator+(const Dummy1 &Dummy1Obj1,const Dummy2 &Dummy2Obj1);
};

int operator+(const Dummy1 &Dummy1Obj1,const Dummy2 &Dummy2Obj1){
	return Dummy1Obj1.num + Dummy2Obj1.num;
}

/*******************************************************************************/
/*******************************************************************************/
//8. Empty arithmetic operators:
//	- zero arguments means I will change the sign of one of the data members.
//	- cout << -Dummy() << +Dummy(); here compiler will create temporary object, change its sign and print it, then destroy it.
class Dummy3 {
	int num = 10;
public:
	std::string operator+(float x) {
		return std::to_string(num + x);
	}
	int operator+(std::string x) {
		return num + stoi(x);
	}
	int operator-() {
		return -num;
	}
	int operator+() {
		return +num;
	}
};
/*******************************************************************************/
/*******************************************************************************/
//9. Will this code compil?:
class Container2;
class Container1 {
public:
	Container1() {}
	Container1(int x) : num(x) {}
private:
	int num = 10;
	friend int operator+(const Container1& c1,
			const Container2& c2);
};
class Container2 {
private:
	int num = 20;
	friend int operator+(const Container1& c1,
			const Container2& c2);
};
int operator+(const Container1& c1,
		const Container2& c2) {
	return c1.num + c2.num;
}

//The next method definations will give errors cuz both take same input arguments, hence compiler will be confused
//class Dummy1 {
//	int num = 10;
//public:
//	int operator+(int x) {
//		return num + x;
//	}
//	string operator+(int x) {
//		return to_string(x+num);
//	}
//};
//main(){
//string str = Dummy1() + "test";
//int number = Dummy1() + 20;}
/*******************************************************************************/
/*******************************************************************************/
//10. Input/Output Operators Overloading
//[Example 1]
std::ostream& operator<<(std::ostream &out,const MyString &other){
	out<<other.literals;	//The array of characters/pointer "literals" is a primitave data type that is defined in one of the operator<<
	// functions (cout.operator<<(const char* other))
	return out;				//To be able to make call chaining (e.g. cout<<x<<x+2<<"hello";)
}
//[Example 2]
class MyList{
private:
	int *arr;
	int size;
	int index = 0;
public:
	MyList(int size):
		arr(new int(size)),
		size(size) {
		std::cout<<"Parametrized constructor of MyList is called\n";
	}
	//1st input is this pointer by default
	MyList& operator<<(MyList &other){
		std::cout<<other.size;
		return other;
	}
	~MyList(){
		std::cout<<"Destructor of MyList is called\n";
	}
};

/*******************************************************************************/
/*******************************************************************************/



int main() {
	/*******************************************************************************/
	/*******************************************************************************/
	//1. Function overloading
	std::cout << addOperands(10,10) << std::endl;
	std::cout << addOperands("First","Second") << std::endl;
	/*******************************************************************************/
	/*******************************************************************************/
	//2. How the c++ deals with function overloading?
	//	1. C++ tries to find an exact match. This is the case where  the actual argument exactly matches the parameter
	//		type of one of the overloaded functions.
	print(0);	 //0 exactly match int
	//	2. If no exact match is found, C++ tries to find a match through promotion (Implicit Casting).
	//		Char, unsigned char and short -> int
	//		Unsigned short				  -> int or unsigned
	//		Float 						  -> double
	//		Enum 						  -> int
	print2('a'); //Char->int after implicit casting by the compiler
	//	3. If no promotion is possible, C++ tries to find a match through standard conversion.
	//		Any numeric type will match any other numeric type
	//		Enum will match any numeric type.
	//		Zero will match a pointer type and numeric type (e.g. 0 to char*, or 0 to float)
	//		A pointer will match a void pointer.
	print3(10.5f);
	print3(FIRST);
	//	4. If no matches are found, C++ tries to find a match through user-defined conversion
	/*******************************************************************************/
	/*******************************************************************************/
	//3. How the compiler deals with function overloading and diffrentiate between functions with same name?
	//	- To see the symbols (name/ID given by the compiler to each function, variable, ) in object file,  type the following in ubunto terminal/cmd:
	//		$ nm S4_Basics_Of_OOP3.o | grep print
	//		nm	 -> will show all symbols in the given object file
	//		|	 -> will pass o/p of the 1st command (nm S4_Basics_Of_OOP3.o) to 2nd one (grep print).
	//		grep -> used to find all symbols with name print
	/*	O/p of the previous instruction:
	 	000000000000008d T _Z5printPc
		00000000000000df T _Z5printi
		0000000000000129 T _Z6print2Pc
		000000000000017b T _Z6print2i
		00000000000001c5 T _Z6print3Pc
		0000000000000217 T _Z6print3i
		The compiler added _z# and (i or Pc) to original symbol name to diffrentiate between names of overloaded functions.
	 */
	/*******************************************************************************/
	/*******************************************************************************/
	//5. Operator overloading: using operators with objects instead of using setters ang getters:
	{
		std::cout<<"5. Operator overloading: using operators with objects: \n";
		MyString hello("hello");				//Parametrized constructor called better than MyString hello = "hello"; to avoid calling copy constructor for temp object, then parametrized constructor
		MyString world(" world");				//Parametrized constructor called
		//hello + world >> hello.operator+(world) [literals(hello) + literals(world)]
		MyString helloworld(hello + world);		//operator+ called. Then copy constructor upon return from operator+ if ROV disabled
		helloworld.print();
	}
	//To disable ROV optimization Right-click on project > select Properties > Go to C/C++ Build > Settings > Tool Settings > GCC C++ Compiler > Miscellaneous (or Clang C++ Compiler if you are using Clang).
	//	>In the Other flags field, add -fno-elide-constructors at the end of the existing flags
	/*******************************************************************************/
	/*******************************************************************************/
	//6. Another example on operator overloading:
	{
		std::cout<<"6. Another example on operator overloading: \n";
		MyString name("Ezz");
		uint8_t age = 97;
		MyString combined = name + age; 	//>>name.operator+(age); Here 97 is the askii of a
		combined.print();
	}
	/*******************************************************************************/
	/*******************************************************************************/
	//7. Overloading operators for operands of different types: Database and Dummy2 classes
	{
		std::cout<<"7. Overloading operators for operands of different types: \n";
		Dummy1 Dummy1Obj1;
		Dummy2 Dummy2Obj1;
		std::cout<<Dummy1Obj1+Dummy2Obj1<<"\n";

	}
	/*******************************************************************************/
	/*******************************************************************************/
	//8. Empty arithmetic operators:
	{
		std::cout<<"8. Empty arithmetic operators: \n";
		std::cout<<-Dummy3()<<"\n"<<+Dummy3()<<"\n";
	}
	/*******************************************************************************/
	/*******************************************************************************/
	//9. Will this code compil?:
	{
		std::cout<<"9. Will this code compil?: \n";
		Container1 c1 = Container1() + Container2();
		Container1 c2 = 200 + Container2();
		//Container1 c3 = Container1() + 30; This wil give error, cuz Container2 has no parametrized constructor.
		std::cout<<Container1() + Container2()<<"\n";
		std::cout<<200 + Container2()<<"\n";
	}
	/*******************************************************************************/
	/*******************************************************************************/
	//10. Input/Output Operators Overloading
	/*
	 * Here the compiler will do the following:
	 * 	1. Find exact match XX
	 * 	2. Try implicit casting XX
	 * 	3. Try standard conversions XX
	 * 	4. Try to find a match using user-defined conversion [worked]
	 */
	//Example 1:
	{
		std::cout<<"10. Input/Output Operators Overloading:[Example 1] \n";
		MyString Name("Ezz");
		std::cout<<Name<<"24\n";		//cout.operator<<(name)
	}
	//Example 2:
	{
		std::cout<<"10. Input/Output Operators Overloading:[Example 2] \n";
		MyList list(10),list2(15);
		list << list << list2 ;
		std::cout<<"\n";
	}
	/*******************************************************************************/
	/*******************************************************************************/
	return 0;
}













