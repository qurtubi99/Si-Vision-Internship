/*
 * Dummy9.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#include "inc/Dummy9.h"
#include <iostream>

int Dummy9::var=0;

void Dummy9::func() {
	std::cout<<"Size of static var class: "<<sizeof(Dummy9)<<"\n";
}

