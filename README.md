# SoftwareLFO
An Arduino-style Software LFO Library
## Usage
### Basics
There are two main LFO classes provided by the library.  SoftwareLFO provides a basic sine wave. DeluxeLFO also provides switchable waveforms.  

In order to use the LFO, one must create a function that calls tick() on the LFO at a consistant rate.  This tick rate can then be used to creaet an LFO using the class template.  

For example to create a 1 Hz LFO:  
``` 
#define TICK_RATE 1000 /* LFO will tick every 1000 milliseconds */
#define OUTPUT_PIN 6 /* Analog Output Pin */
SoftwareLFO<TICK_RATE> LFO;
unsigned long timer = 0;

void setup()
{
    //Set the output pin to output
    pinMode(OUTPUT_PIN, OUTPUT);
    //Set the LFO frequency to 1 Hz
    LFO.setFrequency(1.0f);
}

void loop()
{
    unsigned long now = millis();
    if (now - timer > TICK_RATE)
    {
        timer = now;
        lfo.tick();
        unsigned long oscillatorValue = lfo.getValue();
        //Since LFO output is 24 bits and Analog Write is 10 bits
        //We must right shift the value by 24 - 10 = 14 bits
        oscillatorValue = oscillatorValue >> 14;
        analogWrite(OUTPUT_PIN, oscillatorValue);
    }
}
```

### Waveform Selection
If we want to use the additional waveforms, instead of `SoftwareLFO<TICK_RATE> LFO` we can do `DeluxeSoftwareLFO<TICK_RATE> LFO`.  Then to change output to a sawtooth wave just call `LFO.setWaveform(Sawtooth)`.

The current available waveforms are:  
- Sine
- Triangle
- Square
- Sawtooth
- AsymmetricSine
- InvertedAsymmetricSine
- CompoundSine
