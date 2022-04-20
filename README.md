# Project Name: HW 2 Resampling
**Name: Carson Hansen**


**Description**
 This program will take a .wav file and will take a single-channel WAV file at any sample rate s and produce a WAV file containing the same signal at a sample rate of s/2. This is achieved by using a FIR filter with a transition band of 5% of the maximum input frequency. 
**How it went**
How it went The project started off well but quickly got confusing when it came to the implementation of the FIR filter. I struggled fully understand how I would implement the FIR filter with the coefficients. But, I was able to get it to work and filter samples by reducing their sample rate by 50%.

**What needs to be done**
This program does everything that is required. It generates a new WAV file that has s/2 samples of the original sample. A WAV with a sample size of 877056 with a sample rate of 44100 will have a sample size of 438528 and a sample rate of 22050 when it is run through the filter.


**To build this program**
To be able to build this program, you will need to install the following to get the program to run. Once these are installed, you will want to create the .exe by typing 'make'. Once the makefile has been created, you can run the program like a normal .exe and will need to pass the WAV as an argument to get an altered WAV file.

*Installs the sfml library that is used:*
**sudo apt-get install libsfml-dev** 

*Installs the g++ compiler that is used to compile the program:*
**sudo apt-get install g++**
