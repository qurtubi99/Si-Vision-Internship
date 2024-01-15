//============================================================================
// Name        : S3_Basics_Of_OOP2.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include "../Class/inc/Dymmy7.h"
#include "../Class/inc/Dummy8.h"
#include "../Class/inc/Dummy9.h"
#include "../Class/inc/Dummy10.h"
#include "../Class/inc/Dummy11.h"
#include "../Class/inc/Dummy12.h"
#include "../Class/inc/Dummy13.h"
#include "../Class/inc/Dummy14.h"
#include "../Class/inc/Dummy15.h"
#include "../Class/inc/Dummy16.h"




/*******************************************************************************/
/*******************************************************************************/
//1. Example1 to explain this pointer:
class Dummy{
private:
	int lastSum = 0;
public:
	int sum(int x, int y){
		lastSum += (x+y);
		return x+y;
	}

	int getLastSum() const {
		return lastSum;
	}

	void setLastSum(int lastSum = 0) {
		this->lastSum = lastSum;
	}
};


//Assembly of the next function
/*
	push    %rbp
	mov     %rsp,%rbp
	mov     %ecx,0x10(%rbp)			//Mov function parameter1 from ecx register to stack
	mov     %edx,0x18(%rbp)			//Mov function parameter2 from edx register to stack
	mov     0x10(%rbp),%edx
	mov     0x18(%rbp),%eax
	add     %edx,%eax
	pop     %rbp
	ret
 */
int sum(int x, int y){
	return x+y;
}
Dummy *ptr2DummyObj1 = nullptr;
/*******************************************************************************/
/*******************************************************************************/
//2. How can we achieve this function call? "Call chaining using -> operator"
//	object.add()->subtract()->multiply();
class Dummy2{
private:
	int num1, num2, accumulator;
public:
	Dummy2(int num1,int num2):num1(num1),num2(num2),accumulator(0){

	}

	Dummy2* add(){
		std::cout<<"Add\n";
		accumulator += (num1+num2);
		return this;
	}
	Dummy2* subtract(){
		std::cout<<"subtract\n";
		accumulator += (num1-num2);
		return this;
	}
	Dummy2* multiply(){
		std::cout<<"multiply\n";
		accumulator += (num1*num2);
		return this;
	}

	int getAccumulator() const {
		return accumulator;
	}
};

//How can we achieve this function call? "Call chaining using . operator"
//object.performAdd().performMultiply().performSubtract();
class Dummy3{
private:
	int num1, num2, accumulator;
public:
	Dummy3(int num1,int num2):num1(num1),num2(num2),accumulator(0){

	}

	Dummy3& add(){
		std::cout<<"Add\n";
		accumulator += (num1+num2);
		return *this;
	}
	Dummy3& subtract(){
		std::cout<<"subtract\n";
		accumulator += (num1-num2);
		return *this;
	}
	Dummy3& multiply(){
		std::cout<<"multiply\n";
		accumulator += (num1*num2);
		return *this;
	}

	int getAccumulator() const {
		return accumulator;
	}
};
//Notice that if I said
/*
 	Dummy3 add(){
		std::cout<<"Add\n";
		accumulator += (num1+num2);
		return *this;
	}
	Compiler wii create temp location and make shallow copy and return its address.
 */
/*******************************************************************************/
/*******************************************************************************/
//3. To assure that the size of object of a class is the size of its data members
class Dummy4{
private:
	int num1, num2;
public:
	Dummy4(){

	}

	int getNum1() const {
		return num1;
	}

	void setNum1(int num1) {
		this->num1 = num1;
	}

	int getNum2() const {
		return num2;
	}

	void setNum2(int num2) {
		this->num2 = num2;
	}
};
/*******************************************************************************/
/*******************************************************************************/
//4. Padding in calsses as in structures to make memory aligned
class Dummy5{
private:
	uint32_t firstEmpty,*arr;
public:
	Dummy5():firstEmpty(0),arr(new uint32_t[10]){

	}
	void add(const int inputNum){
		arr[firstEmpty] = inputNum;
		firstEmpty++;
	}
};
/*******************************************************************************/
/*******************************************************************************/
//5. Static members, and how all objects see its memory location
class Dummy6{
private:
	//Static members are tied to the class not to the object/instance of this class
	//	- which means it is allocated in .bss/.data from the beginning before any object creation
	//	of this class
	//The next line is a declaration(prototype), and needs defination(implementation)
	//	& without defination, linker error = undefined reference to callCount.
	static uint32_t callCount;
public:
	Dummy6(){

	}
	void getCount(){
		callCount++;
		std::cout<<"Function has been called: "<<callCount<<" times\n";
	}
};

uint32_t Dummy6::callCount = 0;		//:: is called scope resolution operator, to indicate
									//that the next member belongs to scope of class of type Dummy6
									//- I can't initialize static member during declaration

/*******************************************************************************/
/*******************************************************************************/
//6. Defining static members with different ways of defining a class:
//Differernt ways of defineing a class:
//	1. Define the class in shared file. (As all the previous example, and it worked)
//  2. Create a header file and create the class there (has the problem of redefination of the static member)
//  3. Create a header file and source file. Header file -> Declaration, source file -> Defination (More professional)

/*******************************************************************************/
/*******************************************************************************/


int main() {
	std::cout<<"starting...\n";
	/*******************************************************************************/
	/*******************************************************************************/
	//Example1 to explain this pointer:

	//Before and after function call, context switching occurs.
	//Assembly of the next line is:
	/*
		mov     $0x66,%edx					//This move l-value 1 to edx register
		mov     $0x55,%ecx					//This move l-value 2 to ecx register
		call    0x7ff6df561450 <_Z3sumii>	//Call jumbing to sum function
	 */
	sum(0x55,0x66);


	Dummy DummyObj1;
	ptr2DummyObj1 = &DummyObj1;
	//Assembly of next line:
	/*
	 	lea     -0x4(%rbp),%rax
		mov     $0x22,%r8d
		mov     $0x11,%edx
		mov     %rax,%rcx					//This is addition mov instruction
		call    0x7ff6485f2770 <_ZN5Dummy3sumEii>
	 */
	//from the previous, when calling function in class, compiler add 1 more parameter
	//	when calling function (e.g. DummyObj1.sum(XXXX,0x11, 0x22);)
	//	XXXX = value in rax register (0x9dd25ff76c) which is the same as ptr2DummyObj1
	//	So the copiler passes the address of the object = This pointer
	DummyObj1.sum(0x11, 0x22);
	/*******************************************************************************/
	/*******************************************************************************/
	//How can we achieve this function call? "Call chaining using -> operator"
	Dummy2 Dummy2Obj1(1,2);
	Dummy2Obj1.add()->subtract()->multiply();
	std::cout<<Dummy2Obj1.getAccumulator()<<"\n";
	//How can we achieve this function call? "Call chaining using . operator"
	Dummy3 Dummy3Obj1(1,2);
	Dummy3Obj1.add().subtract().multiply();
	std::cout<<Dummy3Obj1.getAccumulator()<<"\n";
	/*******************************************************************************/
	/*******************************************************************************/\
	//To assure that the size of object of a class is the size of its data members
	Dummy4 Dummy4Obj1;		//Size of this object is 8 bytes (in stack for its 2 datamembers)
	/*******************************************************************************/
	/*******************************************************************************/
	//Example to explain padding in calsses as in structures to make memory aligned
	Dummy5 Dummy5Obj1;		//Size of this object is 16 bytes = 4 [firstEmpty], + 4 [padding]
	// + 8 [arr].
	// Padding is made to make data aligned in memory.

	/*******************************************************************************/
	/*******************************************************************************/
	//Example to explain static members, and how all objects see its memory location
	Dummy6 *Dummy6Obj1 = new Dummy6();
	Dummy6Obj1->getCount();
	Dummy6Obj1->getCount();
	Dummy6Obj1->getCount();
	Dummy6Obj1->getCount();
	delete Dummy6Obj1;
	//- here even after deleteing the allocated class, the count will continue, with the
	//  Dummy6Obj2 created below
	Dummy6 Dummy6Obj2;
	Dummy6Obj2.getCount();
	Dummy6Obj2.getCount();
	Dummy6Obj2.getCount();
	/*******************************************************************************/
	/*******************************************************************************/
	//6. Problems when defining static members with different ways of defining a class:
	Dymmy7 Dummy7Obj1;
	Dummy7Obj1.getCount();
	/*******************************************************************************/
	/*******************************************************************************/
	//7. Different between size of class with static variable and non static variable
	Dummy8 Dummy8Obj1;
	Dummy9 Dummy9Obj1;
	Dummy8Obj1.func();		//4 bytes as normal
	Dummy9Obj1.func();		//1 byte, min size stored for empty class.
							// Remember, static members are stored in .data and not related to object
							// but to class itself.
	/*******************************************************************************/
	/*******************************************************************************/
	//8. Static member functions access without careating any object (reserve any memory space)
	//	- Static members has no access to this pointer, so if the class has a variable, I can't
	//		use it inside the static member function due to that.
	std::cout<<"Dummy10 add result: "<< Dummy10::add(1, 2)<<"\n";
	/*******************************************************************************/
	/*******************************************************************************/
	//9. Question:
	//		Design a class where only one object (an instance of the class) at a time can be
	//		created. In other words, only one object of this class can be used across all other
	//		classes.
	//		Dummy11 obj1;	[This okay]
	//		Dummy11 obj2;	[This gives compiler error]
	//- The applied solution using delete in Dummy11.h is called singlton design pattern
	Dummy11 &Dummy11Obj1 = Dummy11::createObject();
	std::cout<<"Dummy11 add result: "<< Dummy11Obj1.add(1, 3)<<"\n";
	//Dummy11 Dummy11Obj2;					[Gives error, since the default constructor is private]
	//Dummy11 Dummy11Obj2 =  Dummy11Obj1;	[Gives error, since the copy constructor is private/deleted]
	/*******************************************************************************/
	/*******************************************************************************/
	//10. Friend functions
	//- Note: friend functions has no access to this pointer, so we pass object by reference
	Dummy12 Dummy12Obj1;
	display(Dummy12Obj1);
	/*******************************************************************************/
	/*******************************************************************************/
	//11. Friend class: 2 approaches
	//1. Make the class friend: Not good, cuz this class can access every thing in the 1st class
	Dummy16 Dummy16Obj1;
	Dummy15 Dummy15Obj1;
	Dummy15Obj1.display15(Dummy16Obj1);
	//2. Make only the function in class 1 to be friend to class 2 [Professional]
	Dummy14 Dummy14Obj1;
	Dummy13 Dummy13Obj1;
	Dummy13Obj1.display13(Dummy14Obj1);
	/*******************************************************************************/
	/*******************************************************************************/
	return 0;
}















