/*
 * Dymmy7.h
 *
 *  Created on: Jan 12, 2024
 *      Author: Ezz_A
 */

#ifndef DYMMY7_H_
#define DYMMY7_H_



class Dymmy7 {
private:
	static int callCount;
public:
	Dymmy7();						//Constructor prototype
	~Dymmy7();						//Destructor prototype
	Dymmy7(const Dymmy7 &other);	//Copy constructor prototype

	void getCount(void);
};

#endif /* DYMMY7_H_ */
