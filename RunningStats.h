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
	float sumOfSquares;
	float sum;

	RunningStats();
	RunningStats(float* data, uint32_t dataLength);
	virtual ~RunningStats();

	void update(float* data, uint32_t length);

};





#endif /* RUNNINGSTATS_H_ */
