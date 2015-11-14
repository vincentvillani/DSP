/*
 * RunningStats.h
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#ifndef RUNNINGSTATS_H_
#define RUNNINGSTATS_H_

#include <cstdint>



class RunningStats
{
private:



public:

	uint32_t length;
	uint32_t sumOfSquares;
	uint32_t sum;

	RunningStats();
	virtual ~RunningStats();

	void update(float* data, uint32_t length);

};





#endif /* RUNNINGSTATS_H_ */
