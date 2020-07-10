//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file SoftwareLFO.cpp 
//!  @brief Implentation for SoftwareLFO functions (including BaseLFO and BaseDeluxeLFO)
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

#include "SoftwareLFO.h"

uint32_t BaseLFO::getValue() const
{
    uint32_t c = counter;
    auto sinetable = EightBitWaveforms::sine;
    uint32_t val = c >> 16;
    uint32_t i = c & 0xFFFF;
    uint32_t x = sinetable[val];
    uint32_t y = sinetable[val + 1];
    y = y - x;
    y = y * i;
    x = x << 16;
    x = x + y;
    return x;
}

uint32_t BaseDeluxeLFO::getValue() const
{
    uint32_t c = counter;
    auto table = wavetable;
    uint32_t val = c >> 16;
    if (val > 255) Serial.println("Val Overflow");
    uint32_t i = c & 0xFFFF;
    uint32_t x = table[val];
    uint32_t y = table[val + 1];
    y = y - x;
    y = y * i;
    x = x << 16;
    x = x + y;
    //uint32_t v = x * (uint32_t)magnitude;
    //v = v / 0xFFFF;
    return x;
}

void BaseDeluxeLFO::setWaveform(LFOWaveform waveform)
{
    switch(waveform)
    {
        case LFOWaveform::Triangle:
            wavetable = EightBitWaveforms::triangle;
            return;
        case LFOWaveform::Square:
            wavetable = EightBitWaveforms::square;
            return;
        case LFOWaveform::Sawtooth:
            wavetable = EightBitWaveforms::sawtooth;
            return;
        case LFOWaveform::AsymmetricSine:
            wavetable = EightBitWaveforms::asymSine;
            return;
        case LFOWaveform::InvertedAsymmetricSine:
            wavetable = EightBitWaveforms::invertedAsymSine;
            return;
        case LFOWaveform::CompoundSine:
            wavetable = EightBitWaveforms::compoundSine;
            return;
        default:
            wavetable = EightBitWaveforms::sine;
            return;
    }
}
