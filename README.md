# pchip

## Overview 

The 'pchip' is a C++ implementation that employs Piecewise Cubic Hermite Interpolating Polynomial (PCHIP) interpolation to compute plasma gradients based on temperature/electron density profiles.   
The solver reads plasma gradient data (the file name is in the input file) from a text file and interpolates the values over a given range of input parameters.   
The interpolation is used to model plasma behavior where there is a gradient. The gradient angle is also included in the code.  

## Features

- **Reading Plasma Data**: the program reads the plasma gradient data form a text file through the input file.  
- **Piecewise Cubic Hermite Interpolation**: PCHIP is used to perform **non-oscillatory, monotonicity-preseving** interpolation for plasma gradient.  
- **Pellet incidence angle**: the angle of plasma gradient is also included through the input file.  

## Requirements

- C++11 standardof higher.
- a input file which contains gradient angle and plasma data file name.
- a plasma data file.

## Installation 

This code is only used for testing the functionality, and it will be integrated into the official code `PELOTON`. You can still dowonload and play with it.

1. **Clone the repository**:
   ```bash
   git clone https://github.com/ChaoZhang173/pchip.git
   ```

2. **Compile the code**:
   ```bash
   make
   ```
3. **Run the code**:
   ```bash
   ./test -i inputfile
   ```

## Usage

### Example Usage in `test.cpp`

The `test.cpp` gives an example on how to use the `pchip` class.

### Important Notes

1. **Input Format**: the input file should contain 2 lines: 1st line for plasma gradient direction angle (cosine); 2nd line for name of plasma data file.
2. **Plasma Data File**: the plasma data file should have the following structure:
  ```
  position    Te    ne
  ```
  One line represents one point, by default it should have 5 points (in other words, 5 lines). However, users can modify it as needed, just remember to select points within the range for interpolation.  
  There are example files in this repository. 
