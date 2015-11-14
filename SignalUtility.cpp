/*
 * SignalUtility.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */


#include "SignalUtility.h"


float SignalToNoiseRatio(const Histogram* histogram)
{
	return Mean(histogram) / StandardDeviation(histogram);
}


float SignalToNoiseRatio(const RunningStats* runningStat)
{
	return Mean(runningStat) / StandardDeviation(runningStat);
}



float CoefficientOfVariation(const Histogram* histogram)
{
	return (StandardDeviation(histogram) / Mean(histogram) ) * 100.0f;
}


float CoefficientOfVariation(const RunningStats* runningStat)
{
	return (StandardDeviation(runningStat) / Mean(runningStat) ) * 100.0f;
}
