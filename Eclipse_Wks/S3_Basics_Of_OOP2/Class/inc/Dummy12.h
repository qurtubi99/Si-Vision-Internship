/*
 * Dummy12.h
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#ifndef DUMMY12_H_
#define DUMMY12_H_

class Dummy12 {
	friend void display(Dummy12& Dummy12Obj);
private:
	int data1;
	int data2;
	int data3;
protected:
	int data4;
public:
	Dummy12();	//Constructor
};

//This will be a friend function to class Dummy12
void display(Dummy12& Dummy12Obj);

#endif /* DUMMY12_H_ */
