/*
 * Convolution.cpp
 *
 *  Created on: 2 Dec 2015
 *      Author: vincent
 */

#include "Convolution.h"

#include <cstring>

Signal* TimeDomainConvolutionReduced(Signal* inputSignal, Signal* impulseResponse)
{
	uint32_t firstValidIndex = impulseResponse->sampleLength - 1;
	//uint32_t lastValidIndex = inputSignal->sampleLength - firstValidIndex;
	uint32_t lengthOfOutputSignal = (inputSignal->sampleLength + impulseResponse->sampleLength - 1) - (firstValidIndex * 2);

	float* outputSamples = new float[lengthOfOutputSignal];
	memset(outputSamples, 0, sizeof(float) * lengthOfOutputSignal);

	uint32_t outputIndex;

	//Do all the calculations for the first few input, note less than or equal too!
	//Only does the necessary calculations for these first few output indexes
	for(uint32_t inputSignalIndex = 0; inputSignalIndex < firstValidIndex; ++inputSignalIndex)
	{
		//Reset the output index
		outputIndex = 0;

		for(uint32_t impulseIndex = firstValidIndex - inputSignalIndex; impulseIndex < impulseResponse->sampleLength; ++impulseIndex)
		{
			outputSamples[outputIndex] += (inputSignal->samples[inputSignalIndex] * impulseResponse->samples[impulseIndex]);
			outputIndex++;
		}
	}


	//Carry on the normal convolution process
	for(outputIndex = 0; outputIndex < lengthOfOutputSignal; ++outputIndex)
	{
		for(uint32_t impulseIndex = 0; impulseIndex < impulseResponse->sampleLength; ++impulseIndex)
		{
			outputSamples[outputIndex + impulseIndex] += (inputSignal->samples[outputIndex + firstValidIndex] * impulseResponse->samples[impulseIndex]);
		}
	}

	Signal* signal = new Signal(outputSamples, lengthOfOutputSignal);

	return signal;

}


Signal* TimeDomainConvolution(Signal* inputSignal, Signal* impulseResponse)
{
	uint32_t lengthOfOutputSignal = inputSignal->sampleLength + impulseResponse->sampleLength - 1;

	float* outputSamples = new float[lengthOfOutputSignal];
	memset(outputSamples, 0, sizeof(float) * lengthOfOutputSignal);


	for(uint32_t outputIndex = 0; outputIndex < inputSignal->sampleLength; ++outputIndex)
	{
		for(uint32_t impulseIndex = 0; impulseIndex < impulseResponse->sampleLength; ++impulseIndex)
		{
			outputSamples[outputIndex + impulseIndex] += (inputSignal->samples[outputIndex] * impulseResponse->samples[impulseIndex]);
		}
	}

	return new Signal(outputSamples, lengthOfOutputSignal);
}


/*
FrequencySignal* FrequencyDomainConvolution(FrequencySignal* inputDFT, FrequencySignal* impulseResponse)
{

	FrequencySignal* tempImpulseResponse = impulseResponse;
	bool tempImpulseResponseUsed = false; //I don't want to change the passed in impulse response

	//Ensure both the representations are the same, change the impulse response
	if(inputDFT->type != impulseResponse->type)
	{
		tempImpulseResponseUsed = true;

		if(inputDFT->type == RECTANGULAR)
			tempImpulseResponse = FrequencySignalConvertToRectangularCoordinates(impulseResponse);
		else
			tempImpulseResponse = FrequencySignalConvertToPolarCoordinates(impulseResponse);
	}


	FrequencySignal* result = ;



	return result;
}
*/
