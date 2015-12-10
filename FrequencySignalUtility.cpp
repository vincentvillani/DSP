/*
 * DFTUtility.cpp
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#include "FrequencySignalUtility.h"

#include <stdint.h>
#include <cmath>
#include <iostream>
#include <cstring>

#define PI 3.14159265359f


static uint32_t tempFreqSignalNumber = 0;


FrequencySignal* FrequencySignalDeepCopy(FrequencySignal* frequencySignal)
{
	uint32_t signalLength = frequencySignal->realSignal->sampleLength;

	FrequencySignal* result = new FrequencySignal(new Signal(new float[signalLength], signalLength), new Signal(new float[signalLength], signalLength), frequencySignal->type);

	//Copy the values across
	memcpy(result->realSignal->samples, frequencySignal->realSignal->samples, sizeof(float) * signalLength);
	memcpy(result->imaginarySignal->samples, frequencySignal->imaginarySignal->samples, sizeof(float) * signalLength);

	return result;
}


void FrequencySignalWriteToTextFile(const std::string filename, const FrequencySignal* frequencySignal)
{
	FILE* signalFile = fopen(filename.c_str(), "w");

	if(signalFile == NULL)
		return;


	//Calculate the number of samples taken in the signal
	float doubleFrequencySamples = frequencySignal->realSignal->sampleLength * 2.0f;
	float frequencyValue;

	uint32_t i = 0;

	for(; i < frequencySignal->realSignal->sampleLength - 1; ++i)
	{
		frequencyValue = i / doubleFrequencySamples;
		fprintf(signalFile, "%f %f %f\n", frequencyValue, frequencySignal->realSignal->samples[i], frequencySignal->imaginarySignal->samples[i]);
	}

	//print last line to the text file without the newline
	frequencyValue = i / doubleFrequencySamples;
	fprintf(signalFile, "%f %f %f\n", frequencyValue, frequencySignal->realSignal->samples[i], frequencySignal->imaginarySignal->samples[i]);


	fclose(signalFile);
}



void FrequencySignalGraphAmplitude(FrequencySignal* frequencySignal)
{
	FrequencySignal* signalCopy = frequencySignal;

	//If the passed signal is not in polar form, make a copy and convert it to polar coordinates
	if(signalCopy->type != POLAR)
	{
		signalCopy = FrequencySignalDeepCopy(frequencySignal);
		FrequencySignalConvertToPolarCoordinates(signalCopy);
	}

	char filenameBuffer[50];
	sprintf(filenameBuffer, "TempFrequencySignal%u.txt", tempFreqSignalNumber);
	tempFreqSignalNumber++;

	FrequencySignalWriteToTextFile(filenameBuffer, signalCopy);

	FILE* gnuplot;
	gnuplot = popen("gnuplot -persist", "w"); //Linux
	//gnuplot = popen("/usr/local/bin/gnuplot -persist", "w"); //OSX

	if (gnuplot == NULL)
		return;

	fprintf(gnuplot, "set xrange[0 : 0.5]\n");
	fprintf(gnuplot, "set offset graph 0.01, 0.01, 0.01, 0.01\n");
	fprintf(gnuplot, "set samples %u\n", signalCopy->realSignal->sampleLength);
	fprintf(gnuplot, "plot \"%s\" using 1:2 title 'Frequency Amplitude' with points pointtype 5 \n", filenameBuffer);

	if(signalCopy != frequencySignal)
	{
		delete signalCopy;
	}
}


void FrequencySignalGraphPhase(FrequencySignal* frequencySignal)
{
	FrequencySignal* signalCopy = frequencySignal;

	//If the passed signal is not in polar form, make a copy and convert it to polar coordinates
	if(signalCopy->type != POLAR)
	{
		signalCopy = FrequencySignalDeepCopy(frequencySignal);
		FrequencySignalConvertToPolarCoordinates(signalCopy);
	}

	char filenameBuffer[50];
	sprintf(filenameBuffer, "TempFrequencySignal%u.txt", tempFreqSignalNumber);
	tempFreqSignalNumber++;

	FrequencySignalWriteToTextFile(filenameBuffer, signalCopy);

	FILE* gnuplot;
	gnuplot = popen("gnuplot -persist", "w"); //Linux
	//gnuplot = popen("/usr/local/bin/gnuplot -persist", "w"); //OSX

	if (gnuplot == NULL)
		return;

	fprintf(gnuplot, "set xrange[0 : 0.5]\n");
	fprintf(gnuplot, "set offset graph 0.01, 0.01, 0.01, 0.01\n");
	fprintf(gnuplot, "set samples %u\n", signalCopy->realSignal->sampleLength);
	fprintf(gnuplot, "plot \"%s\" using 1:3 title 'Frequency Phase' with points pointtype 5 \n", filenameBuffer);

	if(signalCopy != frequencySignal)
	{
		delete signalCopy;
	}
}



void FrequencySignalConvertToPolarCoordinates(FrequencySignal* dft)
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


void FrequencySignalConvertToRectangularCoordinates(FrequencySignal* dft)
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



void FrequencySignalOutputAmplifyInPlace(FrequencySignal* dft, float amplifcationCoefficent)
{

	uint32_t signalLength = dft->realSignal->sampleLength;

	if(dft->type == POLAR)
	{
		for(uint32_t i = 0; i < signalLength; ++i)
		{
			//Only modify the magnitude values, phase stays unchanged
			dft->realSignal->samples[i] *= amplifcationCoefficent;
		}
	}
	else
	{
		for(uint32_t i = 0; i < signalLength; ++i)
		{
			dft->realSignal->samples[i] *= amplifcationCoefficent;
			dft->imaginarySignal->samples[i] *= amplifcationCoefficent;
		}
	}
}



void FrequencySignalOutputAdditionInPlace(FrequencySignal* dftLHS, FrequencySignal* dftRHS)
{
	if(dftLHS->realSignal->sampleLength != dftRHS->realSignal->sampleLength)
	{
		std::cerr << "Tried to add two signals that are not the same length" << std::endl;
		exit(1);
	}

	//Make sure both are in rectangular form before adding them together
	if(dftLHS->type != RECTANGULAR || dftRHS->type != RECTANGULAR)
	{
		std::cerr << "Ensure Signals in the frequency domain are represented in rectangular form before being added" << std::endl;
		exit(1);
	}

	uint32_t sampleLength = dftLHS->realSignal->sampleLength;

	for(uint32_t i = 0; i < sampleLength; ++i)
	{
		dftLHS->realSignal->samples[i] += dftRHS->realSignal->samples[i];
		dftLHS->imaginarySignal->samples[i] += dftRHS->imaginarySignal->samples[i];
	}
}

