/*
 * DFTCorrelationOutput.cpp
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#include "FrequencySignal.h"

#include <stddef.h>

FrequencySignal::FrequencySignal()
{
	realSignal = NULL;
	imaginarySignal = NULL;
	type = RECTANGULAR;
}

FrequencySignal::FrequencySignal(Signal* real, Signal* imaginary, DFTOutputDataType dataType)
{
	realSignal = real;
	imaginarySignal = imaginary;
	type = dataType;
}


FrequencySignal::~FrequencySignal()
{
	if(realSignal != NULL)
	{
		delete realSignal;
		realSignal = NULL;
	}

	if(imaginarySignal != NULL)
	{
		delete imaginarySignal;
		imaginarySignal = NULL;
	}
}

