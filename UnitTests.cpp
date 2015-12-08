/*
 * UnitTests.cpp
 *
 *  Created on: 24 Nov 2015
 *      Author: vincent
 */

#include <iostream>

#include "UnitTests.h"
#include "SignalUnitTests.h"
#include "DFTUnitTests.h"


void RunAllUnitTests()
{
	//Signal unit tests
	Signal_UpdateUnitTest();
	Signal_ConvolutionUnitTest();
	Signal_IntegrationUnitTest();
	Signal_DerivativeUnitTest();
	Signal_IntegrationAndDerivativeRoundTripUnitTest();

	//DFT unit tests
	DFTCorrelationUnitTest();
	DFTCorrelationRoundTripTest();
	DFTCorrelationRoundTripTestWithPolarCoords();

	std::cout << "All tests passed!" << std::endl;
}

