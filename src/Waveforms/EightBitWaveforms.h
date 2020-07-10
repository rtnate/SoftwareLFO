//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file EightBitWaveforms.h 
//!  @brief Definitions for 8-bit LFO waveforms
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
#ifndef _EIGHT_BIT_SINEWAVE_H_
#define _EIGHT_BIT_SINEWAVE_H_

#include <Arduino.h>

/**
 * @brief Available LFO waveform selections 
 *        as supplied by the EightBitWaveforms class
 */
enum class LFOWaveform
{
    Sine = 0,
    Triangle,
    Square,
    Sawtooth,
    AsymmetricSine,
    InvertedAsymmetricSine,
    //DistoredSine, (Not Supported Yet)
    CompoundSine,
    N_WAVEFORMS
};

/**
 * @brief Static class providing eight bit lookup tables for various waveforms
 * 
 */
class EightBitWaveforms
{
    public:
        EightBitWaveforms() = delete; //!< Unconstructable class

        /**
         * @brief Size of a waveform table.  
         * 
         * Waveform tables all have one extra value (257 instead of 256)
         * in order to facilitate faster linear interpolation
         * 
         */
        static constexpr unsigned int TableSize = 257;


        /**
         * @brief The sine table 
         * 
         */
        static const uint8_t sine[TableSize];

        /**
         * @brief The triangle table 
         * 
         */
        static const uint8_t triangle[TableSize];

        /**
         * @brief The square table 
         * 
         */
        static const uint8_t square[TableSize];

        /**
         * @brief The Sawtooth table 
         * 
         */
        static const uint8_t sawtooth[TableSize];

        /**
         * @brief The AsymmetricSine table 
         * 
         */
        static const uint8_t asymSine[TableSize];

        /**
         * @brief The InvertedAsymmetricSine table 
         * 
         */
        static const uint8_t invertedAsymSine[TableSize];

        /**
         * @brief The CompoundSine table 
         * 
         */
        static const uint8_t compoundSine[TableSize];

        /**
         * @brief Get the 8 bit sine value
         * 
         * @param index - The 8 bit lookup index 
         * @return uint8_t The sine value
         */
        static uint8_t getSine(uint8_t index){ return sine[index]; };
};

#endif
