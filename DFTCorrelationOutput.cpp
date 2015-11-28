/*
 * DFTCorrelationOutput.cpp
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#include "DFTCorrelationOutput.h"

#include <stddef.h>

DFTCorrelationOutput::DFTCorrelationOutput()
{
	realSignal = NULL;
	imaginarySignal = NULL;
}

DFTCorrelationOutput::~DFTCorrelationOutput()
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

