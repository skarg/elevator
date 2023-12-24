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
// Filename:    main.h   
//
// Programmer:  Steve Karg
// Module:      Elevator Simulation    
//
// Technical
// Description: This file contains literals used in the main
//              program.
//
// History:  1: 30-Sep-1996: Created file. - Steve Karg
//
//************************************************************************

#ifndef mainFile
#define mainFile

/* for debugging */
//#define DEBUG

#define TRUE  (1)
#define FALSE (0)

// elevator state machine
#define IDLE_STATE (0)
#define LOAD_STATE (1)
#define UP_STATE (2)
#define STOP_STATE (3)
#define UNLOAD_STATE (4)
#define DOWN_STATE (5)

// elevator capacity
#define MAX_PASSENGERS (20)
// maximum number of elevator cars
#define MAX_ELEVATORS (4)

// stats for a 10 story building
#define LOBBY_FLOOR (0)
#define TOP_FLOOR (9)
#define MAX_FLOORS (10)

#define UP_DIRECTION (1)
#define DOWN_DIRECTION (2)

// time to move on floor at the maximum speed
#define FLOOR_TIME (1.45)
// time needed to decelerate, open and close the doors, and accelerate
#define STOP_TIME (7.19)
// time needed for stopped car to change directions
#define TURN_TIME (1.0)
// mean time for 1 passenger to enter or exit the car
#define LOAD_TIME (1.0)

// menu literals
#define MENU_INVALID_CHOICE   (-1)
#define MENU_BEGIN_SIMULATION (1)
#define MENU_PRINT_REPORTS    (2)
#define MENU_EXIT             (3)
#define MENU_PRINT_TO_SCREEN  (4)
#define MENU_PRINT_TO_PRINTER (5)
#define MENU_RETURN_TO_MAIN   (6)
#define MENU_RUN_SIMULATION   (7)
#define MENU_PROMPT_ELEVATORS (8)

#define VIDEO_MAX_X 640
#define VIDEO_MAX_Y 480

#endif
