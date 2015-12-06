/*
 * Filters.h
 *
 *  Created on: 6 Dec 2015
 *      Author: vincent
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "Signal.h"

#include <stdint.h>

Signal* GenerateMovingAverageFilter(uint32_t length);


#endif /* FILTERS_H_ */
