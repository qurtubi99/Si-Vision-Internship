/*
 * Dummy11.h
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#ifndef DUMMY11_H_
#define DUMMY11_H_

class Dummy11 {
private:
	Dummy11();									//It is private so that if I created any object of this class, it gives compile time error
	//Dummy11(const Dummy11 &other);			//It is private so that if I tried to copy the only created object, it gives compile time error
	Dummy11(const Dummy11 &other) = delete;		//This is a better solution, to avoid misunderstanding by other developers when find it private
												//	as the solution in the previous line
public:
	static Dummy11& createObject(void);
	int add(const int num1,const int num2);
};

#endif /* DUMMY11_H_ */
