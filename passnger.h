//************************************************************************
//
// Copyright (c) 1996 Stephen Karg
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Filename:    passnger.h
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This class is responsible for keeping track of the 
//              destination floor.
//
// History:  1: 30-Sep-1996: Created file. - Steve Karg
//
//************************************************************************

#ifndef passengerFile
#define passengerFile

#include "main.h"

class passenger
{
  protected:
    unsigned short destination_floor;
  public:
    passenger(unsigned short); // constructor
    unsigned short destination();
};

#endif


