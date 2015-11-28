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

	//DFT unit tests
	DFTCorrelationUnitTest();

	std::cout << "All tests passed!" << std::endl;
}

