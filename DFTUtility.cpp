/*
 * DFTUtility.cpp
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#include "DFTUtility.h"

#include <stdint.h>
#include <cmath>

#define PI 3.14159265359f

void ConvertToPolarCoordinates(DFTCorrelationOutput* dft)
{
	if(dft->type == POLAR)
		return;

	dft->type = POLAR;

	float realTemp;
	float imagTemp;

	//
	for(uint32_t i = 0; i < dft->realSignal->sampleLength; ++i)
	{
		realTemp = dft->realSignal->samples[i];
		imagTemp = dft->imaginarySignal->samples[i];

		//Calculate magnitude
		dft->realSignal->samples[i] = sqrtf(realTemp * realTemp + imagTemp * imagTemp);

		//Calculate phase
		//Are we going to divide by zero?
		if(realTemp != 0.0f)
		{
			dft->imaginarySignal->samples[i] = atan( imagTemp / realTemp);
		}
		else //We are, test the imaginary part to see if it should be negative or positive
		{
			if(dft->imaginarySignal->samples[i] < 0.0f)
				dft->imaginarySignal->samples[i] = -(PI / 2.0f);
			else
				dft->imaginarySignal->samples[i] = (PI / 2.0f);
		}

		//Make sure the phase runs from PI to -PI, instead of PI/2 to -(PI/2)
		//If both real and imag are negative subtract 180deg or PI
		if(realTemp < 0.0f && imagTemp < 0.0f)
		{
			dft->imaginarySignal->samples[i] -= PI;
		}
		else if(realTemp < 0.0f && imagTemp >= 0.0f)
		{
			dft->imaginarySignal->samples[i] += PI;
		}
	}
}


void ConvertToRectangularCoordinates(DFTCorrelationOutput* dft)
{
	if(dft->type == RECTANGULAR)
		return;

	dft->type = RECTANGULAR;


	float magTemp;
	float phaseTemp;

	for(uint32_t i = 0; i < dft->realSignal->sampleLength; ++i)
	{
		magTemp = dft->realSignal->samples[i];
		phaseTemp = dft->imaginarySignal->samples[i];

		dft->realSignal->samples[i] = magTemp * cosf(phaseTemp);
		dft->imaginarySignal->samples[i] = magTemp * sinf(phaseTemp);
	}
}
