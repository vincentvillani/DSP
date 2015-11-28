/*
 * DFTCorrelationOutput.h
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#ifndef DFTCORRELATIONOUTPUT_H_
#define DFTCORRELATIONOUTPUT_H_

#include "Signal.h"

class DFTCorrelationOutput
{
public:
	DFTCorrelationOutput();
	DFTCorrelationOutput(Signal* real, Signal* imaginary);
	virtual ~DFTCorrelationOutput();

	Signal* realSignal;
	Signal* imaginarySignal;
};

#endif /* DFTCORRELATIONOUTPUT_H_ */
