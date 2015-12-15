/*
 * DFTUtility.h
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#ifndef DFTUTILITY_H_
#define DFTUTILITY_H_

#include "FrequencySignal.h"

#include <string>

FrequencySignal* FrequencySignalDeepCopy(FrequencySignal* frequencySignal);

void FrequencySignalWriteToTextFile(const std::string filename, const FrequencySignal* frequencySignal);
void FrequencySignalGraphAmplitude(FrequencySignal* frequencySignal);
void FrequencySignalGraphPhase(FrequencySignal* frequencySignal);

void FrequencySignalConvertToPolarCoordinates(FrequencySignal* dft);
void FrequencySignalConvertToRectangularCoordinates(FrequencySignal* dft);

void FrequencySignalAmplifyInPlace(FrequencySignal* dft, float amplifcationCoefficent);
void FrequencySignalAdditionInPlace(FrequencySignal* dftLHS, FrequencySignal* dftRHS);

void FrequencySignalAppendZeroes(FrequencySignal* freqSignal, uint32_t numberOfZeroes);


#endif /* DFTUTILITY_H_ */
