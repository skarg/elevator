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
// Filename:    display.h
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This class is responsible for the user display.
//              The graphics include the passenger count per hour, the
//              static building with elevator shafts and floors, the
//              dynamic elevators traveling up and down the shafts, and
//              the passengers entering and exiting the elevators.
//              The text display includes the menu.
//
// History:  1: 30-Sep-1996: Created file. - Steve Karg
//
//************************************************************************

#ifndef displayFile
#define displayFile

#include "main.h"
#include "output.h"

class display_graphics
{
  protected:
    screen_output disp_out;
    char old_flow[80];    /* var for checking change of state */
    int floor_height;     /* size of each floor */
    int floor_width;      /* width of building */
    int shaft_width;      /* elevator shaft size */
    int building_x_start; /* left side of screen */
    int building_y_start; /* top of screen */

  public:
    display_graphics(void);
    void display_passenger_per_hour(long passperhour);
    void display_static_building(int number_of_elevators);
    void display_dynamic_elevator(int elevator_num,int floor_num,
                                  int display);
    void display_passenger_entry(void);
    void display_passenger_exit(int floor);

    void Draw_Person(int bottom,int top,int center,int width);
    void Clear_Screen();

    int display_menu(char ch);
    int display_number_of_elevators_prompt(char ch);
    int display_print_reports_options(char ch);
};

#endif


