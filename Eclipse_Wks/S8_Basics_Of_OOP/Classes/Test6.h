/*
 * Test6.h
 *
 *  Created on: Jan 31, 2024
 *      Author: Ezz_A
 */

#ifndef TEST6_H_
#define TEST6_H_

template<typename Type>
class Test6 {
private:
	Type num;
public:
	Test6();
	Test6(Type x) : num(x){

	}
	void addElement(const Type& num){
		std::cout << "num int Test6 class" << num << "\n";
	}
	virtual ~Test6(){

	}
};



#endif /* TEST6_H_ */
