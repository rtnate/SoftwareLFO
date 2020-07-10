//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file BaseLFO.h 
//!  @brief BaseLFO Class Definition File
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

#ifndef _BASE_LFO_H_
#define _BASE_LFO_H_

#include <Arduino.h>

/**
 * @brief Base class for Software LFO's.  
 * 
 *  Utilizes a 24 bit internal counter and provides sine output by default.
 * 
 */
class BaseLFO
{
    public:
        /**
         * @brief Bit Depth of the LFO's Internal Counter
         */
        static constexpr unsigned int CounterBitDepth = 24;
        
        /**
         * @brief Number of counts (ticks) per oscillation period
         */
        static constexpr unsigned long CountsPerPeriod = (1 << CounterBitDepth);

        /**
         * @brief Construct a new BaseLFO object
         */
        BaseLFO(): tick_increment(0), counter(0){}

        /**
         * @brief Sets the increment value
         * 
         * @param value The new value (maximum value is CountsPerPeriod)
         */
        inline void setIncrementValue(uint32_t value){ tick_increment = value % CountsPerPeriod; };

        /**
         * @brief Increment the oscillator.
         * 
         * This function should be called at a constant rate in order to "run" the oscillator
         * 
         */
        inline void tick()
        {
            counter += tick_increment;
            counter %= CountsPerPeriod;
        }

        /**
         * @brief Reset the oscillators internal counter to 0
         * 
         */
        inline void reset(){ counter = 0; }

        /**
         * @brief Get the oscillators output value.
         * 
         *  This function is virtual, so it may be overriden to provide additional calculations
         * 
         *  @return uint32_t The oscillators 24 bit output value.
         */
        virtual uint32_t getValue() const;

        /**
         * @brief Gets the current counter value.
         * 
         * @return uint32_t The oscillators 24 bit counter value
         */
        uint32_t getCounter() const { return counter; };

        /**
         * @brief Get the increment value (how much the counter is incremented per tick)
         * 
         * @return uint32_t The oscillators 24 bit increment value
         */
        uint32_t getIncrementValue() const { return tick_increment; };

        /**
         * @brief Sets the oscillators internal counter to the supplied value
         * 
         * @param value The new 24 bit counter value
         */
        void setCounter(uint32_t value){ counter = value % CountsPerPeriod; };

        /**
         * @brief Check if the internal counter is more than half way
         * 
         * @return true If counter its more than halfway (wave output is positive)
         * @return false If not (wave output is negative)
         */
        bool isHalfway() const { ( counter > (CountsPerPeriod / 2) ) ? true : false; };

    protected:
        /**
         * @brief The amount the oscillator is incremented per tick
         */
        uint32_t tick_increment;

        /**
         * @brief The internal 24 bit counter
         */
        uint32_t counter;
};

#endif