/*
 * DFTUtility.h
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#ifndef DFTUTILITY_H_
#define DFTUTILITY_H_

#include "DFTCorrelationOutput.h"

void ConvertToPolarCoordinates(DFTCorrelationOutput* dft);
void ConvertToRectangularCoordinates(DFTCorrelationOutput* dft);

void DFTOutputAmplifyInPlace(DFTCorrelationOutput* dft, float amplifcationCoefficent);
void DFTOutputAdditionInPlace(DFTCorrelationOutput* dftLHS, DFTCorrelationOutput* dftRHS);



#endif /* DFTUTILITY_H_ */
