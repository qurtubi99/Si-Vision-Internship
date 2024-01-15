/*
 * Dummy13.h
 *
 *  Created on: Jan 15, 2024
 *      Author: Ezz_A
 */

#ifndef DUMMY13_H_
#define DUMMY13_H_

//Forward declaration, to tell to avoid circular referencing problem if I've included Dummy14.h
// and Dummy14.h included Dummy13.h
class Dummy14;

//This calss will be friend to class Dummy14

class Dummy13 {
public:
	Dummy13();
	~Dummy13();
	void display13(const Dummy14& Dummy12Obj);
};

#endif /* DUMMY13_H_ */
