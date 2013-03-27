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

// FUNCTION PROTOTYPES:

/// \brief Lookup a temperature based on it's resistance.
/// \param res The resistance (in kOhms).
/// \return The resulting temperature (in Celsius).
static double lookup(double res);

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
    // TODO: implement lookup table
    return 0;
}

double get_resistance(int pin, double res)
{
    double x = analogRead(pin);
    if(x == 0)
        return 0;
    return res / x * (1023 - x);
}

// jl
