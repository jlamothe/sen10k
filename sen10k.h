// -*- mode: c++ -*-

/// \file sen10k.h

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

#ifndef SEN10K_H
#define SEN10K_H

/// \brief Reads a temperature form a 10K Type II sensor.
/// \param pin The analog pin being read from.
/// \param res The value (in kOhms of the pull down resistor).
/// \return The temperature (in Celsius).
double read_10k(int pin, double res);

#endif  // SEN10K_H

// jl
