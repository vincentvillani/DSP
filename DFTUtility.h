/*
 * DFTUtility.h
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#ifndef DFTUTILITY_H_
#define DFTUTILITY_H_

#include "FrequencySignal.h"

void ConvertToPolarCoordinates(FrequencySignal* dft);
void ConvertToRectangularCoordinates(FrequencySignal* dft);

void DFTOutputAmplifyInPlace(FrequencySignal* dft, float amplifcationCoefficent);
void DFTOutputAdditionInPlace(FrequencySignal* dftLHS, FrequencySignal* dftRHS);



#endif /* DFTUTILITY_H_ */
