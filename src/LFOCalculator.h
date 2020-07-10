//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file LFOCalculator.h 
//!  @brief LFOCalculator class definition
//!
//!  @author Nate Taylor 
//!
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

#ifndef _LFO_CALCULATOR_H_
#define _LFO_CALCULATOR_H_

#include "BaseLFO.h"

/**
 * @brief Class providing LFO period and frequency calculations based 
 *        on the supplied tick rate
 * 
 * @tparam TICK_RATE_MS - The tick rate in milliseconds (period bewteen tick() calls)
 */
template <unsigned long TICK_RATE_MS>
class LFOCalculator
{
    public:
        /**
         * @brief Amount of milliseconds in a second
         */
        static constexpr unsigned long MillisecondsPerSecond = 1000;

        /**
         * @brief Oscillator Tick Rate in milliseconds
         */
        static constexpr unsigned long TickRate = TICK_RATE_MS;

        /**
         * @brief Multiplier For Calculating Oscillator Increment Value
         */
        static constexpr float FreqToCountMultiplier =  (static_cast<float>(BaseLFO::CountsPerPeriod) * static_cast<float>(TickRate)) / 
                                                        (static_cast<float>(MillisecondsPerSecond));
        
        /**
         * @brief Maximum Supported Frequency
         */
        static constexpr float MaxFrequency = BaseLFO::CountsPerPeriod / (FreqToCountMultiplier * 2);

        /**
         * @brief Minimum Supported Frequency
         */
        static constexpr float MinFrequency =   static_cast<float>(MillisecondsPerSecond) / 
                                                (static_cast<float>(TickRate) * static_cast<float>(BaseLFO::CountsPerPeriod));

        /**
         * @brief Maximum Supported Period
         */
        static constexpr float MaxPeriod = 1.f / MinFrequency;

        /**
         * @brief Minimum Supported Period
         */
        static constexpr float MinPeriod = 1.f / MaxFrequency;

        /**
         * @brief Get the Increment Value For The Provided Period
         * 
         * @param periodSeconds The desired period in seconds
         * @return uint32_t The increment value
         */
        inline static uint32_t getIncrementValueForPeriod(float periodSeconds)
        {
            if (periodSeconds > MaxPeriod) periodSeconds = MaxPeriod;
            if (periodSeconds < MinPeriod) periodSeconds = MinPeriod;
            float countIncrement= periodSeconds * FreqToCountMultiplier;
            return static_cast<uint32_t>(countIncrement);
        }

        /**
         * @brief Get the Increment Value For The Provided Frequency
         * 
         * @param freqHertz The desired frequency
         * @return uint32_t The increment value
         */
        inline static uint32_t getIncrementValueForFrequency(float freqHertz)
        {
            if (freqHertz > MaxFrequency) freqHertz = MaxFrequency;
            if (freqHertz < MinFrequency) freqHertz = MinFrequency;
            //Now Setting Frequency Only Performs a Single Floating Point Multiply
            float countIncrement= freqHertz * FreqToCountMultiplier;
            return static_cast<uint32_t>(countIncrement);
        }
};
#endif