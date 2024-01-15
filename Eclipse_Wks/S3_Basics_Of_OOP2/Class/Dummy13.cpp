/*
 * Dummy13.cpp
 *
 *  Created on: Jan 15, 2024
 *      Author: Ezz_A
 */
#include <iostream>

#include "inc/Dummy14.h"

Dummy13::Dummy13() {
	// TODO Auto-generated constructor stub

}

Dummy13::~Dummy13() {
	// TODO Auto-generated destructor stub
}

void Dummy13::display13(const Dummy14& Dummy14Obj){
	std::cout<<"From display13 function in Dummy13 class which is friend to Dummy14 class:\n";
	std::cout<<"Data1: "<<Dummy14Obj.data1<<"\n";
	std::cout<<"Data2: "<<Dummy14Obj.data2<<"\n";
	std::cout<<"Data3: "<<Dummy14Obj.data3<<"\n";

}
