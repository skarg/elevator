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
// Filename:    elevsim.h
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This module is the main module.
//
// History:  1: 08-Oct-1996: Created file. - Steve Karg
//
//************************************************************************
#ifndef elevsimFILE
#define elevsimFILE

#include "elevator.h"
#include "display.h"
#include "report.h"

class elevsim
{
  private:
    int number_of_elevators;
    int report_option;
    int menu_choice;
    int run_menu_choice;
    int floor_index;
    int index;
    unsigned short floor_num;    /* floor index */
    unsigned long *floor_array;
    unsigned short elevator_state;
  protected:
    unsigned long min_flow_rate;
    unsigned long max_flow_rate;
    unsigned long last_max_flow_rate;
    unsigned long last_min_flow_rate;
    unsigned long total_passengers;
    int last_floor[MAX_ELEVATORS];
    unsigned long floor_passengers[MAX_FLOORS];
    double min_duration;
    double max_duration;
    elevator *elevator_rack[MAX_ELEVATORS];
    display_graphics disp_out;
    screen_report sreport;
    printer_report preport;
  public:
    int run(char ch);
    elevsim();
    ~elevsim();
};

#endif
