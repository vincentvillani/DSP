/*
 * FilterUnitTests.cpp
 *
 *  Created on: 14 Dec 2015
 *      Author: vincentvillani
 */


#include "FilterUnitTests.h"

#include <string>
#include <stdint.h>
#include <cmath>

#include "FrequencySignal.h"
#include "Signal.h"
#include "SignalUtility.h"
#include "FrequencySignalUtility.h"
#include "Filters.h"
#include "DiscreteFourierTransform.h"

#define PI 3.14159265359f

void GenerateCustomFilterUnitTest()
{
	uint32_t desiredFreqResponseLength = 513;

	FrequencySignal* desiredFrequencyResponse = new FrequencySignal(new Signal(new float[desiredFreqResponseLength], desiredFreqResponseLength),
			new Signal(new float[desiredFreqResponseLength], desiredFreqResponseLength), POLAR);

	//Zero out everything
	memset(desiredFrequencyResponse->realSignal->samples, 0, sizeof(float) * desiredFreqResponseLength);
	memset(desiredFrequencyResponse->imaginarySignal->samples, 0, sizeof(float) * desiredFreqResponseLength);

	//Generate a weird looking frequency response, magnitude first


	float twoPI = 2 * PI;

	for(uint32_t i = 0; i < desiredFreqResponseLength; ++i)
	{
		/*
		if(i < desiredFreqResponseLength / 2)
			desiredFrequencyResponse->realSignal->samples[i] = 1;
		else
			desiredFrequencyResponse->realSignal->samples[i] = 0;
		*/

		desiredFrequencyResponse->realSignal->samples[i] = cosf(twoPI * i * 5 / desiredFreqResponseLength) + 1.0f;
	}

	//TRY APPENDING ZEROES TO THE DESIREDFREQRESPONSE!???
	//FrequencySignalAppendZeroes(desiredFrequencyResponse, desiredFreqResponseLength);

	/*
	for(uint32_t i = 0; i < 150; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = 0.5f * cosf(twoPI * (i / 150.0f));
	}

	for(uint32_t i = 150; i < 250; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = desiredFrequencyResponse->realSignal->samples[i - 1] + 0.01f;
	}

	for(uint32_t i = 250; i < 300; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = 1.0f;
	}

	for(uint32_t i = 300; i < 350; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = 0.0f;
	}

	for(uint32_t i = 350; i < 400; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = 1.0f;
	}

	for(uint32_t i = 400; i < 512; ++i)
	{
		desiredFrequencyResponse->realSignal->samples[i] = (512 - i) / (512.0f - 400.0f);
	}
	*/

	//Graph the desired freq response (amplitude)
	//FrequencySignalGraphAmplitude(desiredFrequencyResponse);
	//FrequencySignalGraphPhase(desiredFrequencyResponse);


	//Calculate the filter kernel from the desired freq response
	Signal* customFilter = FilterGenerateCustomFilterKernel(desiredFrequencyResponse, 400);
	SignalAppendZeroes(customFilter, 1024);
	//Move the kernel to the freq domain to see its actual freq response
	FrequencySignal* filterFreq = DFTViaCorrelation(customFilter);
	//Convert it to polar coords
	FrequencySignalConvertToPolarCoordinates(filterFreq);
	//Graph it
	FrequencySignalGraphAmplitude(filterFreq);
	FrequencySignalGraphPhase(filterFreq);


	delete customFilter;
	delete filterFreq;
	delete desiredFrequencyResponse;

}
