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
// Filename:    elevator.h
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This class is responsible for keeping track of the current
//              floor position, the direction and state of operation, and
//              the number of passengers aboard and their destination.
//
// History:  1: 30-Sep-1996: Created file. - Steve Karg
//
//************************************************************************

#ifndef elevatorFile
#define elevatorFile

#include "main.h"
#include "passnger.h"
#include "poisson.h"

class elevator
{
  protected:
    unsigned long total_passenger_count;
    unsigned long  passengers_on_board;
    unsigned short floor;
    unsigned short direction;
    unsigned short state;
    int elevator_id;
    unsigned long pass_on_floor[MAX_FLOORS];
    passenger *pass[MAX_PASSENGERS];
    Poisson poisson_interval;
    double total_duration;
  public:
    elevator(int);  // constructor
    ~elevator(); // destructor
    void run();
    unsigned long current_total_passenger_count();
    unsigned short current_passengers_on_board();
    unsigned short current_floor();
    unsigned short current_direction();
    unsigned short current_state();
    int current_id();
    double current_duration();
    unsigned long passenger_flow_rate();
    unsigned long *pass_on_floor_array();
};

#endif


