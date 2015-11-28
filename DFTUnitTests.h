/*
 * DFTUnitTests.h
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#ifndef DFTUNITTESTS_H_
#define DFTUNITTESTS_H_


void DFTCorrelationUnitTest();
void DFTCorrelationRoundTripTest(); //Test doing a DFT and inverse DFT, see if we get the same result we started with
void DFTCorrelationRoundTripTestWithPolarCoords(); //Same as above but the Inverse DFT function is passed an output in polar coordinates


#endif /* DFTUNITTESTS_H_ */
