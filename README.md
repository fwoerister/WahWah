# WahWah VST Plugin
## Introduction
This Plugin was developed as a part of the final submission for the lecture "DSP-Processing & Generative Music" at the Technical University Vienna. Goal of this submission was to develope a VST Plugin, that performs any kind of DSP (in this case a simple WahWah effect).  
The Effect itself uses an IIR BandPass Filter with an attached sinus oscilator on the center frequency parameter.

The plugin provides following adjustable parameters:

* control frequency
* amplitude
* center frequency
* bandwidth

The control frequency and the amplitude can be used to adjust the behaviour of the sinus oscilator, whereas center frequency and bandwidth can be used to modify the bandpass filter.

## Setup Guide

1) Clone this repository: `git clone https://github.com/fwoerister/WahWah.git`
2) Open this project in the producer and generate the JUCE library code
3) Compile this project with your cmake compatibel IDE, or use the linux makefile. The VST target generates the WahWah.so.
4) Copy the WahWah.so file into your vst plugin folder, or tell your DAW, where to look for the WahWah plugin.

## Demo
A demo of this filter can be found in the `demo/` folder!
