//============================================================================
// Name        : S7_Basics_Of_OOP.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : Virtual functions cont., Ansi-style
//============================================================================

#include <iostream>
#include <assert.h>

/****************************************************************************************************************************************/
//1. C++11 and above can check on all the rules when defining override functions using override keyword:
//Override rules:
//	- Func in child class should have same name.
//	- Func in the child class should have the same number of arguments and same types as well.
//	- Func in the child class should have the same const-ness (as in case of getter functions)
//	- Func in the child class should have the same return type.
//	- Func in the child class should have the same reference qualifier.
//		- Ref. qualifier: cpp feature
/*
 	 	Inside class1:
 	 		//& reference qulaifier is a cpp feature, makes  only l-value objects call this func, otherwise -> error.
			void lvalueFunc() & {
				std::cout << "lvalueFunc function of Parent1\n";
			}
			//&& reference qulaifier is a cpp feature, makes  only r-value objects call this func, otherwise -> error.
			void rvalueFunc() && {
				std::cout << "lvalueFunc function of Parent1\n";
			}
		Inside Main:
			Class1 obj;
			obj.lvalueFunc();
			obj.rvalueFunc();		//An object/(memory allocation with ID has been created), hence l-value, hence error
			Class1().lvalueFunc();	//No object/(memory allocation with ID has been created), hence r-value, hence error
			Class1().rvalueFunc();

 */
class Parent1{
public:
	virtual void print(){
		std::cout << "Print function of Parent1\n";
	}
};

class Child1 : public Parent1{
public:
	void print() override{
		std::cout << "Print function of Child1\n";
	}
};
/****************************************************************************************************************************************/
//2. Prevent overriding for level 3 inheritance using final keyword:
class Parent12{
public:
	virtual void print(){
		std::cout << "Print function of Parent1\n";
	}
};

class Child21 : public Parent1{
public:
	//final keyword will prevent overriding print function in any class that inherit from Child21 class
	void print() override final{
		std::cout << "Print function of Child21\n";
	}
};

class Child22 : public Child21{
public:
	//The next lines will give compiler error message due to final keyword
	//void print() override{
	//	std::cout << "Print function of Child22\n";
	//}
};
/****************************************************************************************************************************************/
//3. Calling virtual function in parent instead of overriden function in child:
class Parent3{
public:
	virtual void print(){
		std::cout << "Print function of Parent3\n";
	}
};

class Child3 : public Parent3{
public:
	void print() override{
		std::cout << "Print function of Child3\n";
	}
};

/****************************************************************************************************************************************/
//4. virtual destructors/functions effect when deleting parent object:

class Parent4{
private:
	int *arr;
public:
	Parent4(): arr(new int[10]){
		std::cout << "Default CTOR of Parent4 is called\n";
	}

	//Virtual destructor here makes me when I create child4 object, then destroy parent part of it
	// it will also distroy the child4 object (Inspite that the distroy function doesn't know anything about the children of parent.)
	//This makes me never change in the destroy function whatever the changes in parent class the childs changed.
	//This is also applicable to virtual functions.
	virtual ~Parent4(){
		if(arr != nullptr){
			delete[] arr;
		}
		std::cout << "Destructor of Parent4 is called\n";
	}
};

class Child4 : public Parent4{
public:
	Child4(){
		std::cout << "Default CTOR of Child4 is called\n";
	}

	~Child4(){
		std::cout << "Destructor of Child4 is called\n";
	}
};

void destroyParent4Object(Parent4 *parent){
	delete parent;
}

/****************************************************************************************************************************************/
//5. Interface classes: [Contain PVF "pure virtual functions" only]
//This is a terminolgy rule, not syntax/cpp rule
//	- Rule : Parent classes must set some rules for child classes.
//	- Rule : Constructing parent object from parent classes should be prohibited.
//	- Extra: Functions that do not make any sense in the parent class should not be implemented.
//Different terminologies of classes: [execluding special member functions]
/*
 * Interface: A class that contains PVFs only
 * Abstract : A class that provide a mix of PVFs and other member functions, serving as base classe for related classes.
 * Concrete : A child class that implement all inherited functions and represent specific objects or entities.
 */
//Interface class
class HWAccess{
private:
	bool active;
public:
	// Special member function is allowed in interface classes.
	HWAccess() : active(false){
		std::cout << "Default CTOR of HWAccess is called\n";
	}
	HWAccess(bool active) : active(active){
		std::cout << "Parametrized CTOR of HWAccess is called\n";
	}
	virtual void init() = 0;	//PVF [Has no implementation in parent]
	virtual void send() = 0;	//PVF [Has no implementation in parent]

	// Special member function is allowed in interface classes.
	virtual ~HWAccess(){
		std::cout << "Destructor of HWAccess is called\n";
	}
};

class SPI : public HWAccess{
public:
	SPI(){
		std::cout << "Default CTOR of SPI is called\n";
	}
	void init() override{
		std::cout << "init function of SPI\n";
	}

	void send() override{
		std::cout << "send function of SPI\n";
	}
	virtual ~SPI(){
		std::cout << "Destructor of SPI is called\n";
	}
};

class Uart : public HWAccess{
public:
	Uart(){
		std::cout << "Default CTOR of Uart is called\n";
	}
	void init() override{
		std::cout << "init function of Uart\n";
	}

	void send() override{
		std::cout << "send function of Uart\n";
	}
	virtual ~Uart(){
		std::cout << "Destructor of Uart is called\n";
	}
};


void processing(HWAccess *ptr){
	std::cout << "Processing function\n";
	ptr->init();
	ptr->send();
}

void destroyHWAccessObject(HWAccess *parent){
	delete parent;
}
/****************************************************************************************************************************************/
//6. Poly-moriphic objects
//Abstract class [Contians PVFs and other functions[setActive]]
class ProtocolBase6{
private:
	bool active;
public:
	// Special member function is allowed in interface classes.
	ProtocolBase6() : active(false){
		std::cout << "Default CTOR of ProtocolBase6 is called\n";
	}
	ProtocolBase6(bool active) : active(active){
		std::cout << "Parametrized CTOR of ProtocolBase6 is called\n";
	}

	void setActive(const bool active){
		this->active = active;
	}

	virtual void init() = 0;	//PVF [Has no implementation in parent]
	virtual void send() = 0;	//PVF [Has no implementation in parent]

	// Special member function is allowed in interface classes.
	virtual ~ProtocolBase6(){
		std::cout << "Destructor of ProtocolBase6 is called\n";
	}
};

//Concrete class
class SPI6 : public ProtocolBase6{
public:
	SPI6(){
		std::cout << "Default CTOR of SPI6 is called\n";
	}
	void init() override{
		std::cout << "init function of SPI6\n";
	}

	void send() override{
		std::cout << "send function of SPI6\n";
	}
	virtual ~SPI6(){
		std::cout << "Destructor of SPI6 is called\n";
	}
};

//Concrete class
class Uart6 : public ProtocolBase6{
public:
	Uart6(){
		std::cout << "Default CTOR of Uart6 is called\n";
	}
	void init() override{
		std::cout << "init function of Uart6\n";
	}

	void send() override{
		std::cout << "send function of Uart6\n";
	}
	virtual ~Uart6(){
		std::cout << "Destructor of Uart6 is called\n";
	}
};

enum ProtocolTypes{
	e_UART6,
	e_SPI6

};

class HWAccess6{
private:
	//Poly-morphic objects:
	//	Parent *ptr2Parent = new Child;	>> child object will be allocated in heap, but the pointer will point to the parent object inside it.
	//	This guarantees that the constructor is the only function here that will know info about the used protocol [child], hence it is the only
	//	function that I will need to modify in it when adding a new protocol (e.g. I2C)
	ProtocolBase6 *protocol;
public:

	HWAccess6(const ProtocolTypes id){
		std::cout << "Parameterized CTOR of HWAccess6 is called\n";
		if(id == e_UART6){
			protocol = new Uart6;
		}else{
			protocol = new SPI6;
		}

	}

	void beginProcess(){
		std::cout << "beginProcess of HWAccess6 is called\n";
		protocol->init();	// Will access the init function of the child of ProtocolBase6 (Uart6 or SPI6), since these functions are PVFs and overridden in Childs.
		protocol->send();
	}

	virtual ~HWAccess6(){
		std::cout << "Parametrized CTOR of HWAccess6 is called\n";
		delete protocol;
	}

};
/****************************************************************************************************************************************/
//7. Factory design pattern:
class ProtocolBase7{
private:
	bool active;
public:
	// Special member function is allowed in interface classes.
	ProtocolBase7() : active(false){
		std::cout << "Default CTOR of ProtocolBase7 is called\n";
	}
	ProtocolBase7(bool active) : active(active){
		std::cout << "Parametrized CTOR of ProtocolBase7 is called\n";
	}

	void setActive(const bool active){
		this->active = active;
	}

	virtual void init() = 0;	//PVF [Has no implementation in parent]
	virtual void send() = 0;	//PVF [Has no implementation in parent]

	// Special member function is allowed in interface classes.
	virtual ~ProtocolBase7(){
		std::cout << "Destructor of ProtocolBase7 is called\n";
	}
};

//Concrete class
class SPI7 : public ProtocolBase7{
public:
	SPI7(){
		std::cout << "Default CTOR of SPI7 is called\n";
	}
	void init() override{
		std::cout << "init function of SPI7\n";
	}

	void send() override{
		std::cout << "send function of SPI7\n";
	}
	virtual ~SPI7(){
		std::cout << "Destructor of SPI7 is called\n";
	}
};

//Concrete class
class Uart7 : public ProtocolBase7{
public:
	Uart7(){
		std::cout << "Default CTOR of Uart7 is called\n";
	}
	void init() override{
		std::cout << "init function of Uart7\n";
	}

	void send() override{
		std::cout << "send function of Uart7\n";
	}
	virtual ~Uart7(){
		std::cout << "Destructor of Uart7 is called\n";
	}
};

enum ProtocolTypes7{
	e_UART7,
	e_SPI7

};

class HWAccess7{
private:
	ProtocolBase7 *protocol;
	//Factory function: Creates one of several poly-morphic objects.
	//This gurantees that each function only does one functionality if there were multiple objects to be created
	//in the constructor.
	ProtocolBase7* createProtocol(const ProtocolTypes7 id){
		if(id == e_UART7){
			return new Uart7;
		}else{
			return new SPI7;
		}
	}
public:

	HWAccess7(const ProtocolTypes7 id){
		std::cout << "Parametrized CTOR of HWAccess7 is called\n";
		protocol = createProtocol(id);
	}

	void beginProcess(){
		std::cout << "beginProcess of HWAccess7 is called\n";
		protocol->init();
		protocol->send();
	}

	virtual ~HWAccess7(){
		std::cout << "Parametrized CTOR of HWAccess7 is called\n";
		delete protocol;
	}

};
/****************************************************************************************************************************************/
int main() {
	/****************************************************************************************************************************************/
	//1. C++11 and above can check on all the rules when defining override functions using override keyword:
	{
		std::cout << "1. C++11 and above can check on all the rules when defining override functions using override keyword: \n";
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//2. Prevent overriding for level 3 inheritance using final keyword (Child1 inherit from Parent1, Child2 inherit from Child1, now child2 is level 3)
	//	 which also inherit from Parent1 so Child2 is a Parent1 and can override its virtual functions.
	{
		std::cout << "2. Prevent overriding for level 3 inheritance using final keyword: \n";

	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//3. Calling virtual function in parent instead of overriden function in child:
	{
		std::cout << "3. Calling virtual function in parent instead of overriden function in child: \n";
		Child3 Child3Obj;
		Child3Obj.print();			// >> func(&object) + Late/dynamic binding since print function is virtual.
		Child3Obj.Parent3::print();
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//4. virtual destructors/functions effect when deleting parent object:
	{
		std::cout << "4. virtual destructors/functions effect when deleting parent object: \n";
		Child4 *Child4Obj = new Child4;
		destroyParent4Object(Child4Obj);		//Implicit upward casting

	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//5. Interface classes: [Contain PVF "pure virtual functions" only]
	{
		std::cout << "5. Interface classes: \n";
		//HWAccess HWAccessObj; This line will give compiler error, cuz HWAccess is an interface class.
		Uart *UartObj1 = new Uart;
		processing(UartObj1);		//Implicit upward casting
		destroyHWAccessObject(UartObj1);

	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//6. Poly-moriphic objects:
	{
		std::cout << "6. Poly-moriphic objects: \n";
		HWAccess6 HWAccess6Obj(e_SPI6);
		HWAccess6Obj.beginProcess();
	}
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//7. Factory design pattern:
	std::cout << "7. Factory design pattern: \n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/
	//8. Dynamic casting [runtime checks > execution time]
	{
		std::cout << "8. Dynamic casting [runtime checks > execution time]: \n";
		SPI7 *SPI7Obj1 = new SPI7;									//Concrete object
		ProtocolBase7 *ProtocolBase7Obj = SPI7Obj1;					//Implicit upward casting
		SPI7 *SPI7Obj2 = static_cast<SPI7*>(ProtocolBase7Obj);		//Make compile time checks but no runtime checks (still no info about v.ptr
		// , v. table, ...).
		SPI7Obj2->init();
		Uart7 *UART7Obj1 = static_cast<Uart7*>(ProtocolBase7Obj);	//This is logically incorrect and must give error & since I can't
		//get this error in compile time (V.function and V.Table still not created yet), then I can catch it in run time using dynamic cast.

		//Dynamic cast return nullptr if the casting is inappropriate.
		//Dynamic cast only works with pointers/references.
		Uart7 *UART7Obj2 = dynamic_cast<Uart7*>(ProtocolBase7Obj);
		if(UART7Obj2 == nullptr){
			//If I reached here, I must assert assert(0);
			std::cout << "Error in casting\n";
		}

		//Dynamic cast with references:
		SPI7 SPI7Obj3;									//Concrete object
		ProtocolBase7 &ProtocolBase7Obj1 = SPI7Obj3;
		try{
			Uart7 &UART7Obj3 = dynamic_cast<Uart7&>(ProtocolBase7Obj1);
		}
		catch(std::bad_cast &execution){
			//assert(0);	It is commented to prevent assertion
		}

	}

	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	/****************************************************************************************************************************************/

	return 0;
}
