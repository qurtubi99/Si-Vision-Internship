/*
 * Dummy14.h
 *
 *  Created on: Jan 15, 2024
 *      Author: Ezz_A
 */

#ifndef DUMMY14_H_
#define DUMMY14_H_

#include "Dummy13.h"

class Dummy14 {
	friend void Dummy13::display13(const Dummy14& Dummy14Obj);
private:
	int data1;
	int data2;
	int data3;
public:
	Dummy14();
	~Dummy14();
};

#endif /* DUMMY14_H_ */
