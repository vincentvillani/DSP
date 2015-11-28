/*
 * Signal.h
 *
 *  Created on: 24 Nov 2015
 *      Author: vincent
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <stdint.h>

class Signal
{

public:
	//Signal();
	Signal(float* data, uint32_t dataLength);
	virtual ~Signal();

	//Update the signal to now include the new passed in data
	void update(float* data, uint32_t dataLength);

	uint32_t sampleLength;
	float* samples;
};

#endif /* SIGNAL_H_ */
