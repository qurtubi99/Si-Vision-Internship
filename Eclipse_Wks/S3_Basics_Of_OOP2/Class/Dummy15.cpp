/*
 * Dummy15.cpp
 *
 *  Created on: Jan 15, 2024
 *      Author: Ezz_A
 */

#include "inc/Dummy15.h"
#include "inc/Dummy16.h"
#include <iostream>

Dummy15::Dummy15() {
	// TODO Auto-generated constructor stub

}

Dummy15::~Dummy15() {
	// TODO Auto-generated destructor stub
}

void Dummy15::display15(const Dummy16& Dummy16Obj){
	std::cout<<"From Dummy15 class which is friend to Dummy16 class:\n";
	std::cout<<"Data1: "<<Dummy16Obj.data1<<"\n";
	std::cout<<"Data2: "<<Dummy16Obj.data2<<"\n";
	std::cout<<"Data3: "<<Dummy16Obj.data3<<"\n";
}
