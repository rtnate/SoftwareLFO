//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file SoftwareLFO.h 
//!  @brief SoftwareLFO Library Definition
//!
//!  @author Nate Taylor 

//!  Contact: nate@rtelectronix.com
//!  @copyright (C) 2020  Nate Taylor - All Rights Reserved.
//
//      |-----------------------------------------------------------------------------------------|
//      |                                                                                         |
//      |                    MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                          |
//      |                    MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                          |
//      |                   MMMMMMMMM    MMMMMMMMMM       NNNNNMNNN                               |
//      |                   MMMMMMMM:    MMMMMMMMMM       NNNNNNNN                                |
//      |                  MMMMMMMMMMMMMMMMMMMMMMM       NNNNNNNNN                                |
//      |                 MMMMMMMMMMMMMMMMMMMMMM         NNNNNNNN                                 |
//      |                 MMMMMMMM     MMMMMMM          NNNNNNNN                                  |
//      |                MMMMMMMMM    MMMMMMMM         NNNNNNNNN                                  |
//      |                MMMMMMMM     MMMMMMM          NNNNNNNN                                   |
//      |               MMMMMMMM     MMMMMMM          NNNNNNNNN                                   |
//      |                           MMMMMMMM        NNNNNNNNNN                                    |
//      |                          MMMMMMMMM       NNNNNNNNNNN                                    |
//      |                          MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                |
//      |                        MMMMMMM      E L E C T R O N I X         MMMMMM                  |
//      |                         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM                    |
//      |                                                                                         |
//      |-----------------------------------------------------------------------------------------|
//
//      |-----------------------------------------------------------------------------------------|
//      |                                                                                         |
//      |      [MIT License]                                                                      |
//      |                                                                                         |
//      |      Copyright (c) 2020 Nathaniel Taylor                                                |
//      |                                                                                         |
//      |      Permission is hereby granted, free of charge, to any person obtaining a copy       |
//      |      of this software and associated documentation files (the "Software"), to deal      |
//      |      in the Software without restriction, including without limitation the rights       |
//      |      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell          |
//      |      copies of the Software, and to permit persons to whom the Software is              |
//      |      furnished to do so, subject to the following conditions:                           |
//      |                                                                                         |
//      |      The above copyright notice and this permission notice shall be included in all     |
//      |      copies or substantial portions of the Software.                                    |
//      |                                                                                         |
//      |      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR         |
//      |      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,           |
//      |      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE        |
//      |      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER             |
//      |      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,      |
//      |      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE      |
//      |      SOFTWARE.                                                                          |
//      |                                                                                         |
//      |-----------------------------------------------------------------------------------------|
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _SOFTWARE_LFO_H_
#define _SOFTWARE_LFO_H_

#include <Arduino.h>
#include "Waveforms/EightBitWaveforms.h"
#include "BaseLFO.h"
#include "LFOCalculator.h"
#include "BaseDeluxeLFO.h"

/**
 * @brief Template SoftwareLFO class with period and frequency calculation.
 * 
 * Supply the tick rate to create a basic sine-wave Software LFO
 * 
 * @tparam TICK_RATE_MS - The tick rate in milliseconds (milliseconds between calls to tick())
 */
template <unsigned long TICK_RATE_MS>
class SoftwareLFO: public BaseLFO, public LFOCalculator<TICK_RATE_MS>
{
    public:
        inline void setPeriod(float periodSeconds)
        {
            setIncrementValue(this->getIncrementValueForPeriod(periodSeconds));
        }

        inline void setFrequency(float freqHertz)
        {
            setIncrementValue(this->getIncrementValueForFrequency(freqHertz));
        }
};

/**
 * @brief Template DeluxeSoftwareLFO class with period and frequency calculation. 
 * 
 * Supply the tick rate to create a full-featured Software LFO
 * 
 * @tparam TICK_RATE_MS - The tick rate in milliseconds (milliseconds between calls to tick())
 */
template <unsigned long TICK_RATE_MS>
class DeluxeSoftwareLFO: public BaseDeluxeLFO, public LFOCalculator<TICK_RATE_MS>
{
    public:
        inline void setPeriod(float periodSeconds)
        {
            setIncrementValue(this->getIncrementValueForPeriod(periodSeconds));
        }

        inline void setFrequency(float freqHertz)
        {
            setIncrementValue(this->getIncrementValueForFrequency(freqHertz));
        }
};


#endif