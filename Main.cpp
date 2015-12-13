/*
 * Main.c
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#include <iostream>

#include "Stats.h"
#include "SignalUtility.h"
#include "Noise.h"
#include "UnitTests.h"
#include "Filters.h"
#include "DiscreteFourierTransform.h"
#include "FrequencySignalUtility.h"

//TODO: Rethink histogram, its kinda fucked...
//TODO: Add the ability to 'Unwrap the phase' (Chapter 8)
//TODO: Think about frequency domain convolution and the best way to go about it... (Chapter 9)
//TODO: Think about breaking apart the two different types of representations of Frequency Signals
//TODO: Implement the complex conjugate (Characteristics of the phase, Chapter 10)
//TODO: Add the ability to graph things in log scale (dB)
//TODO: Implement DFT via FFT

#define DATA_LENGTH 100000

int main()
{

	Signal* bandPassFilter = GenerateBandRejectFilter(500, 0.2f, 0.4f);
	Signal* shiftedBandPassFilter = SignalDeepCopy(bandPassFilter);
	SignalShiftInPlace(shiftedBandPassFilter, bandPassFilter->sampleLength / 2);

	SignalGraph(bandPassFilter);
	SignalGraph(shiftedBandPassFilter);

	//FrequencySignal* freqResponse = DFTViaCorrelation(bandPassFilter);
	//FrequencySignalGraphAmplitude(freqResponse);


	delete bandPassFilter;
	delete shiftedBandPassFilter;
	//delete freqResponse;

	/*

	//Generate low-pass filter
	Signal* testSignal = GenerateLowPassFilter(500, 0.1f);
	//SignalGraph(testSignal);

	Signal* testSignalSpectralInversion = GenerateHighPassFilter(500, 0.4f);
	//SignalSpectralInversionInPlace(testSignalSpectralInversion);
	//SignalGraph(testSignalSpectralInversion);

	//Generate frequency response for the filter
	FrequencySignal* freqResponse =	DFTViaCorrelation(testSignal);
	FrequencySignalGraphAmplitude(freqResponse);

	FrequencySignal* freqResponseSpectralInversion = DFTViaCorrelation(testSignalSpectralInversion);
	FrequencySignalGraphAmplitude(freqResponseSpectralInversion);


	//Generate step response for the filter
	//SignalSpectralInversionInPlace(testSignalSpectralInversion);
	//SignalIntegrateInPlace(testSignalSpectralInversion);
	//SignalGraph(testSignalSpectralInversion);

	delete testSignal;
	delete testSignalSpectralInversion;
	delete freqResponse;
	delete freqResponseSpectralInversion;

	*/

	//RunAllUnitTests();

	return 0;
}
