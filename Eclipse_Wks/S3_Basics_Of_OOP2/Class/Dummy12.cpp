/*
 * Dummy12.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#include "inc/Dummy12.h"
#include <iostream>

Dummy12::Dummy12():
	data1(10),
	data2(20),
	data3(30)
{
	// TODO Auto-generated constructor stub

}

void display(Dummy12& Dummy12Obj){
	std::cout<<"From display function in dummy12 object:\n";
	std::cout<<"Data1: "<<Dummy12Obj.data1<<"\n";
	std::cout<<"Data2: "<<Dummy12Obj.data2<<"\n";
	std::cout<<"Data3: "<<Dummy12Obj.data3<<"\n";

}

