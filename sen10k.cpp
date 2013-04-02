/// \file sen10k.cpp

// 10k Temperature Sensor Library

// Copyright (C) 2013 Jonathan Lamothe <jonathan@jlamothe.net>

// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see: http://www.gnu.org/licenses/

// #INCLUDES:

#include "sen10k.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// GLOBALS:

/// \breif The lookup table for a 10k Type II thermistor.
static double table[][2] =
{
    { 1.034,    86.11 },
    { 1.070,    85.00 },
    { 1.109,    83.89 },
    { 1.149,    82.78 },
    { 1.190,    81.67 },
    { 1.234,    80.56 },
    { 1.279,    79.44 },
    { 1.326,    78.33 },
    { 1.375,    77.22 },
    { 1.427,    76.11 },
    { 1.480,    75.00 },
    { 1.536,    73.89 },
    { 1.594,    72.78 },
    { 1.655,    71.67 },
    { 1.718,    70.56 },
    { 1.785,    69.44 },
    { 1.855,    68.33 },
    { 1.927,    67.22 },
    { 2.003,    66.11 },
    { 2.082,    65.00 },
    { 2.165,    63.89 },
    { 2.252,    62.78 },
    { 2.343,    61.67 },
    { 2.438,    60.56 },
    { 2.538,    59.44 },
    { 2.642,    58.33 },
    { 2.751,    57.22 },
    { 2.865,    56.11 },
    { 2.985,    55.00 },
    { 3.111,    53.89 },
    { 3.242,    52.78 },
    { 3.380,    51.67 },
    { 3.525,    50.56 },
    { 3.679,    49.44 },
    { 3.838,    48.33 },
    { 4.006,    47.22 },
    { 4.182,    46.11 },
    { 4.367,    45.00 },
    { 4.561,    43.89 },
    { 4.766,    42.78 },
    { 4.981,    41.67 },
    { 5.207,    40.56 },
    { 5.447,    39.44 },
    { 5.697,    38.33 },
    { 5.960,    37.22 },
    { 6.238,    36.11 },
    { 6.530,    35.00 },
    { 6.838,    33.89 },
    { 7.163,    32.78 },
    { 7.505,    31.67 },
    { 7.866,    30.56 },
    { 8.251,    29.44 },
    { 8.653,    28.33 },
    { 9.078,    27.22 },
    { 9.526,    26.11 },
    { 10.000,   25.00 },
    { 10.501,   23.89 },
    { 11.030,   22.78 },
    { 11.590,   21.67 },
    { 12.182,   20.56 },
    { 12.814,   19.44 },
    { 13.478,   18.33 },
    { 14.180,   17.22 },
    { 14.925,   16.11 },
    { 15.714,   15.00 },
    { 16.550,   13.89 },
    { 17.437,   12.78 },
    { 18.378,   11.67 },
    { 19.376,   10.56 },
    { 20.446,    9.44 },
    { 21.573,    8.33 },
    { 22.770,    7.22 },
    { 24.042,    6.11 },
    { 25.395,    5.00 },
    { 26.834,    3.89 },
    { 28.365,    2.78 },
    { 29.996,    1.67 },
    { 31.732,    0.56 },
    { 33.599,   -0.56 },
    { 35.573,   -1.67 },
    { 37.676,   -2.78 },
    { 39.921,   -3.89 },
    { 42.317,   -5.00 },
    { 44.874,   -6.11 },
    { 47.606,   -7.22 },
    { 50.526,   -8.33 },
    { 53.647,   -9.44 },
    { 57.017,  -10.56 },
    { 60.592,  -11.67 },
    { 64.419,  -12.78 },
    { 68.518,  -13.89 },
    { 72.911,  -15.00 },
    { 77.620,  -16.11 },
    { 82.670,  -17.22 },
    { 88.090,  -18.33 },
    { 93.909,  -19.44 },
    { 100.218, -20.56 },
    { 106.939, -21.67 },
    { 114.165, -22.78 },
    { 121.939, -23.89 },
    { 130.306, -25.00 },
    { 139.316, -26.11 },
    { 149.024, -27.22 },
    { 159.488, -28.33 },
    { 170.775, -29.44 },
    { 183.068, -30.56 },
    { 196.227, -31.67 },
    { 210.443, -32.78 },
    { 225.809, -33.89 },
    { 242.427, -35.00 },
    { 260.410, -36.11 },
    { 279.880, -37.22 },
    { 300.974, -38.33 },
    { 323.839, -39.44 },
    NULL
};

// FUNCTION PROTOTYPES:

/// \brief Lookup a temperature based on it's resistance.
/// \param res The resistance (in kOhms).
/// \return The resulting temperature (in Celsius).
static double lookup(double res);

/// \brief Tests to see if a number is within a range.
/// \param x The number being tested.
/// \param x1 One end of the ragne.
/// \param x2 The other end of the range.
/// \return true if the number is within the range; false otherwise.
bool is_between(double x, double x1, double x2);

/// \brief Reads the resistance on an analog input.
/// \param pin The analog pin number.
/// \param res The resistance on the pull-down resistor.
/// \return The resistance.
static double get_resistance(int pin, double res);

// FUNCTION DEFINITIONS:

double read_10k(int pin, double res)
{
    return lookup(get_resistance(pin, res));
}

double lookup(double res)
{
    double **i;
    for(i = table; i[0] && i[1]; i++)
    {
        double x1 = i[0][0],
               y1 = i[0][1],
               x2 = i[1][0],
               y2 = i[1][1];
        if(is_between(res, x1, x2))
        {
            if(res == x1)
                return y1;
            if(res == x2)
                return y2;
            return (y2 - y1) / (x2 - x1) * (res - x1) + y1;
        }
    }
    return 0;
}

bool is_between(double x, double x1, double x2)
{
    return x >= min(x1, x2) && x <= max(x1, x2);
}

double get_resistance(int pin, double res)
{
    double x = analogRead(pin);
    if(x == 0)
        return 0;
    return res / x * (1023 - x);
}

// jl
