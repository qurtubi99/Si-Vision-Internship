//============================================================================
// Name        : S8_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include "../Classes/Test6.h"

class Parent{
private:

public:

	Parent(){
		std::cout << "Default CTOR of Parent is called\n";
	}
	Parent(bool active){
		std::cout << "Parametrized CTOR of Parent is called\n";
	}

	virtual ~Parent(){
		std::cout << "Destructor of Parent is called\n";
	}
};

class Child : public Parent{
public:
	Child(){
		std::cout << "Default CTOR of Child is called\n";
	}

	virtual ~Child(){
		std::cout << "Destructor of Child is called\n";
	}
};
/****************************************************************************************************************************************/
//1. Templates:
//	What are the problems solved by templates?
//	Problem1: Several functions with same implementation in case of function overloading
//	Problem2: Overloaded function is not extendible easily.
template <typename Type1,typename Type2,typename ReturnType>	//T template value, R return value

ReturnType add(Type1 obj1,const Type2 obj2){
	return obj1 + obj2;
}

class Dummy1{
public:
	int num = 20;
	int operator+(const Dummy1 &other){
		return num + other.num;
	}
};
/****************************************************************************************************************************************/
//2. Default return type in templates:
template <typename Type21,typename Type22,typename ReturnType2 = float>	//T template value, R return value

ReturnType2 add2(Type21 obj1,const Type22 obj2){
	return obj1 + obj2;
}
/****************************************************************************************************************************************/
//3. Question:
//3. Question[1]:
template <typename T>
void func(T x){
	std::cout << "Template\n";

}
void func(int x){
	std::cout << "Non-Template\n";
}

//3. Question[2]:
template <typename T>
void func1(T x){
	std::cout << "value - Template\n";

}
template <typename T>
void func1(T &x){
	std::cout << "Refernce - Template\n";
}
/****************************************************************************************************************************************/
//4. Templates in OOP:
class Container4{
private:
	int *arr;
	int size;
	int emptyLocation;
public:
	Container4(const int size) : arr(new int[size]), size(size),emptyLocation(0){

	}
	void addElement(const int num){
		arr[emptyLocation] = num;
		emptyLocation ++;
	}
	virtual ~Container4(){
		if(arr != nullptr){
			delete []arr;
		}
	}
};

//templated class
template <class Type>
class Container41{
private:
	Type *arr;
	int size;
	int emptyLocation;
public:
	Container41(const int size);
	void addElement(const Type& num);
	virtual ~Container41(){
		if(arr != nullptr){
			delete []arr;
		}
	}
};

template <typename Type>
Container41<Type>::Container41(const int size) : arr(new Type[size]), size(size),emptyLocation(0){

}

template <typename Type>
void Container41<Type>::addElement(const Type& num){
	arr[emptyLocation] = num;
	emptyLocation ++;
}
/****************************************************************************************************************************************/
//5. How compiler deals with templates?
/*
	When the compiler sees:
		template <typename Type>
		void func(Type x){

		}
	and in the main finds:
	func<int>(10);
	the compiler will define func with integer prototype:
		void func(int x){

		}
	and repeat same process for every new type.
	If another function call uses int as Type, then the compiler will use the function it has defined before.
	These defined functions will be part of the final executable.
 */

/****************************************************************************************************************************************/
int main() {
	/****************************************************************************************************************************************/
	//1. Templates:
	{
		std::cout << "1. Templates: \n";

		//If I didn't specify the return type in the function definition & prototype, hence I've to call the function in this way to tell the compiler.
		int resultI;
		resultI = add<int,int,int>(10,10);			 					//<int[input1],int[input2],int[return]>
		std::cout << resultI << "\n";

		float num1 = 20.1;
		float num2 = 20.2;
		float resultF;
		resultF = add<float,float,float>(num1,num2);					//<float[input1],float[input2],float[return]>
		std::cout << resultF << "\n";

		std::string str1 = "Hi ";
		std::string str2 = "ezz";
		std::string resultS;
		resultS = add<std::string,std::string,std::string>(str1,str2);	//same but for strings
		std::cout << resultS << "\n";


		Dummy1 obj1,obj2;
		int dummyAdd = add<Dummy1,Dummy1,int>(obj1,obj2);				//obj1.operator+(obj2) >> operator+(&obj1,obj2);
		std::cout << dummyAdd << "\n";
		//1st argument mustn't be const in add function when dealing with operator overloading in classes as in Dummy1, since this pointer is a non const.
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//2. Default return type in templates:
	{
		std::cout << "2. Default return type in templates: \n";
		//If I'm convinced with the default return type, I can call the function without specifying the types of the i/p and the return parameter
		//Otherwise, I will need to specify it.
		float resultI;
		resultI = add2(10,10.3f);
		resultI = add2(10,10.3f);
		std::cout << resultI << "\n";
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//3. Question:
	std::cout << "3. Question[1]: \n";
	func(10);	//Function overloading >> exact match (non template printed.)

	std::cout << "3. Question[2]: \n";
	int x=10;
	//func1(x)	//This will give error message cuz x is L-value, hence can match both functions
	func1(10);	//R-value, hence will only match 2nd function
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//4. Templates in OOP:
	Container4 Container4Obj1(10);

	Container4Obj1.addElement(10);
	Container4Obj1.addElement(20);
	Container4Obj1.addElement(30);
	Container4Obj1.addElement(40);

	//Problem:
	//If instead of sending intergers, I want to send strings, I will need to modify arr and addElement.
	//But, if I want both, then I will have to dublicate same class.
	//Solution:
	//Define template classes.
	Container41<int> Container41Obj1(10);		//Here Type will be int.
	Container41Obj1.addElement(10);
	Container41Obj1.addElement(20);

	Container41<float> Container41Obj2(10);		//Here Type will be float.
	Container41Obj2.addElement(20.1);
	Container41Obj2.addElement(20.2);

	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//5. How compiler deals with templates?

	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//6. How to use templates when classes defiend in a different file?
	//Problem:
	//	When I define the class prototype in .h and functions' definations in .cpp. In the main file, to create an object/instance of this
	//	class i will include its .h file. But since .h file conatins prototypes only, when the compiler finds the templated functions, It will
	//	try to regenerate it but it can't cuz it will not find the implementation of the function. Hence, compiler will leave it to the linker to
	//	resolve it, but as we know, there is no function defination with the specified type in the main, and the compiler is the only one who
	//	can generate the function with the required file, so I will have error [Linker error].
	//Solution:
	//	When dealing with template classes, I create everything in header file as in Test6 class
	Test6<int> Test6Obj1(10);


	return 0;
}
















