/*
 * DFTCorrelationOutput.h
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#ifndef DFTCORRELATIONOUTPUT_H_
#define DFTCORRELATIONOUTPUT_H_

#include "Signal.h"

enum DFTOutputDataType
{
	RECTANGULAR,
	POLAR
};

class FrequencySignal
{
public:
	FrequencySignal(Signal* real, Signal* imaginary, DFTOutputDataType type);
	virtual ~FrequencySignal();

	//If type is polar coordinates, real = magnitude, imaginary = phase
	Signal* realSignal;
	Signal* imaginarySignal;
	DFTOutputDataType type;

};

#endif /* DFTCORRELATIONOUTPUT_H_ */
