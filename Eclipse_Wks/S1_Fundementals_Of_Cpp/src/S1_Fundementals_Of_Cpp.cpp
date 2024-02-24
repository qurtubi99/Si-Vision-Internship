//============================================================================
// Name        : S1_Fundementals_Of_Cpp.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

// Versions of C++ C++98 >> C++3 >> C++11 >+3> C++14 >+3> C++17 >+3> C++20 >+3> C++23

/****************************************************************************************************************************************/
//0. Differnece between NULL in c and nullptr in CPP:
// 	- NULL in c is ((void*)0) so I can say x = NULL + 1; and now x = 1;
// 	- nullptr in cpp is:
//		- built in (no need to include iosteram)
//		- Can only be used with pointer (otherwise compiler error [compile time check])
//		- namespace std has nullptr_t type (I can say nullptr_t a = nullptr;)

/****************************************************************************************************************************************/
//1. Local vs Global Variables
/*
  Local Variables:
	1. Functions’ formal parameters and defined variables.
	2. Scope: Function scope/ Block scope
	3. Lifetime: Function Lifetime
   Global Variables:
	1. Variables are defined outside any block (function, class, struct).
	2. Scope: File Scope
	3. Lifetime: Whole Program
 */

/****************************************************************************************************************************************/
//2. Static Keyword:
/*
	- Static variables keep their values and are not destroyed even after they go out of scope
	- Initialized only once
	- Still Local to this function
 */
void func2() {
	static int callCount = 0;
	std::cout<<callCount++<<"\n";
}

/****************************************************************************************************************************************/
//3. L-Values vs R-Values:
/*
	- L-Values are objects that occupies some identifiable location in memory
	- R-Values are object that have no identifiable memory location
 */
int i = 10; 			// "i" has an identifiable memory location "L-value", while 10 is not "R-value"
int *ptr = &i;			// "i" can be modified
//int i = sum(10,1);	// “sum(10,1)” has no memory location, i.e. its value cannot be modified.

/****************************************************************************************************************************************/
//4. Reference:
/*
	- Reference variables don’t allocate new memory space, but share the same memory location of the RHS variable[L-value]
	- Better than pointer:
		- Differentiate between ptr to int and to array of int (syntax difference)
		- No need to check against null (less complex code)
		- No ownership problem (delete the received pointer after using it if it points to dynamically allocated space in heap or not)
 */
//const guarantee that if R-value is passed, Its temporary memory location in memory will not be destroyed till the end of the function.
int& accumlate (const int &x,const int &y) {
	static int accumlator = 0;
	accumlator += x + y;
	return accumlator;
}
//Receiving pointer [address of variable] by reference
void func4(int *&param){
	std::cout<<*param<<"\n";
}
//Receiving array of 10 elements by reference.
void foo(int (&x)[10]){
	std::cout<< "Element 5 in the passed array by reference: "<<x[4]<<"\n";
}

/****************************************************************************************************************************************/
//5. Difference between passing L & R-value to function:
/*
	L-value: just copy passed variable to function argument
		void copyString(string str);
		string testString = "Test";
		copyString(testString);
	R-value: Create a temporary variable >>  Copy its content to str >> Destroy the temporary variable
		void copyString(string str);
		copyString("Literals");

		void copyString(string& str);
		copyString("Test"); >>This will give compiler error cuz the temp memroy location will be destroyed when passed to function
							..So I must use const keyword
 */

/****************************************************************************************************************************************/
//6. new and delete Operators:
/*
	string *pointer1 = new string();
	string *pointer2 = new string[10];
	delete pointer1;
 */

/****************************************************************************************************************************************/
//7. Procedural [POP] vs Object oriented programming [OOP]:
/*
	POP:
		- App = functions.
		- Problem: data members are not specific for certain functions, and any function in any module can use it.
	OOP:
		- Solve this problem and guarantee more maintainable and optimized design
		- class == Template, no memory reserved till an object/instance is created.
		- Encapsulation: method members and data members in same class.
		- Abstraction: If APP is big, divide it in to multiple classes, then create class with instances of all required classes.
 */

/****************************************************************************************************************************************/


int main() {
	/****************************************************************************************************************************************/
	//2. Static Keyword:
	{
		std::cout<<"2. Static Keyword: \n";
		func2();
		func2();
		func2();
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//4. Reference:
	{
		std::cout<<"4. Reference accumlate calling: \n";
		int &x = accumlate(1,2);		// x is now 3
		std::cout << x << std::endl;
		x++;							// x is now 4
		std::cout << x << std::endl;

		int &y = accumlate(0,1);		// x is now 5
		std::cout << x << std::endl;
		y++;							// x is now 6
		std::cout << x << std::endl;

		//Passing pointer by reference
		std::cout<<"4. Reference func4 calling: \n";
		int z1 = 20;
		int *z2 = &z1;
		func4(z2);

		//Passing array by reference
		std::cout<<"4. Reference foo calling: \n";
		int x1[10] = {1,2,3,4,13,6};
		foo(x1);
		std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	}

	/****************************************************************************************************************************************/
	return 0;
}
