/*
 * Histogram.h
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <stdint.h>



class Histogram
{
private:



public:

	uint32_t binNum; //The bins in the histogram
	uint32_t* bins; //An array storing the values of each of the bins
	uint32_t dataSampleNum; //The total data samples that this histogram contains
	float bucketDistance; //The value difference between each bucket

	Histogram(uint32_t binNum, float* data, uint32_t dataLength);
	Histogram(uint32_t binNum, float dataMin, float dataMax, float* data, uint32_t dataLength);
	virtual ~Histogram();

};









#endif /* HISTOGRAM_H_ */
