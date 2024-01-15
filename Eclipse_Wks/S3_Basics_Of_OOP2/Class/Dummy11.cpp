/*
 * Dummy11.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#include "inc/Dummy11.h"

Dummy11::Dummy11() {
	//Some code

}

//If I choosed the copy constructor to be private, this defination must exist
//Dummy11::Dummy11(const Dummy11 &other) {
//	//Some code
//
//}

Dummy11& Dummy11::createObject(void){
	static Dummy11 obj;	//This object is created only once [static]
	return obj;
}

int Dummy11::add(const int num1,const int num2){
	return num1 + num2;
}

