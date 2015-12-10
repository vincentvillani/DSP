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

//TODO: Rethink histogram, its kinda fucked...
//TODO: Add the ability to 'Unwrap the phase' (Chapter 8)
//TODO: Think about frequency domain convolution and the best way to go about it... (Chapter 9)
//TODO: Think about breaking apart the two different types of representations of Frequency Signals
//TODO: Implement the complex conjugate (Characteristics of the phase, Chapter 10)

#define DATA_LENGTH 100000

int main()
{

	Signal* testSignal = GenerateBlackmanWindowedSincLowPassFilter(500, 0.04f);
	GraphSignal(testSignal);

	SignalIntegrateInPlace(testSignal);
	GraphSignal(testSignal);

	delete testSignal;



	//RunAllUnitTests();

	return 0;
}
