/*
 * Window.h
 *
 *  Created on: 13 Dec 2015
 *      Author: vincent
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdint.h>

#include "Signal.h"

Signal* WindowGenerateHammingWindow(uint32_t length);
Signal* WindowGenerateBlackmanWindow(uint32_t length);



#endif /* WINDOW_H_ */
