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
// Filename:    elevsupp.cpp
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This module contains supplemental functions.
//
// History:  1: 12-Oct-1996: Created file. - Steve Karg
//
//************************************************************************

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "main.h"
#include "elevsupp.h"

unsigned long flow_rate_from_secs(double secs,unsigned long pass)
{
  double flow;
  double hours;

  hours = secs/(60.0*60.0);  // secs to hour
  if (hours > 0.0)
    flow = (double)pass/hours;
  else
    flow = 0.0;

  return (unsigned long)flow;
}


#ifndef  CLOCKS_PER_SEC                   /* CLOCKS_PER_SEC is ANSI/ISO */
 #define CLOCKS_PER_SEC CLK_TCK
#endif

void delay(unsigned short msec)
{
      clock_t t0;
      unsigned long diff = 0L;

      for (t0 = clock(); diff < (unsigned long)msec; )
      {
            diff  = (unsigned long)(clock() - t0);
            diff *= 1000L;
            diff /= CLOCKS_PER_SEC;
      }
}

