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
// Filename:    elevator.cpp
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

#include <iostream>

#include "main.h"
#include "elevator.h"


elevator::elevator(int id) // constructor
{
  #ifdef DEBUG
  cout << "elevator" << endl;
  #endif

  int idx;

  total_passenger_count = 0;
  passengers_on_board = 0;

  floor = LOBBY_FLOOR;
  direction = UP_DIRECTION;
  state = IDLE_STATE;
  elevator_id = id;
  poisson_interval.put_interval((MAX_FLOORS-1));
  total_duration = 0.0;
  for (idx=0;idx<MAX_FLOORS;idx++)
  {
	 pass_on_floor[idx] = 0;
  }
  for (idx=0;idx<MAX_PASSENGERS;idx++)
  {
	 pass[idx] = NULL;
  }
}

void elevator::run()
{
  int i;
  unsigned short dest;
  short done;
  double duration = 0;

  switch(state)
  {
    case IDLE_STATE:
      state = LOAD_STATE;
      if (direction == DOWN_DIRECTION)
      {
        direction = UP_DIRECTION;
        duration += TURN_TIME;
      }
      break;
    case LOAD_STATE:
      passengers_on_board = 0;

      for (i=0;i<MAX_PASSENGERS;i++)
      {
        done = FALSE;
        while (!done)
        {
          dest = (unsigned short)poisson_interval.next();
          if ((dest > 0) && (dest < MAX_FLOORS))
            done = TRUE;
        }
        pass[i] = new passenger(dest);
        passengers_on_board++;
        duration += LOAD_TIME;
      }
      state = UP_STATE;
      break;
    case UP_STATE:
      floor++;
      duration += FLOOR_TIME;
      for (i=0;i<MAX_PASSENGERS;i++)
      {
        // look for matching floor
        if (pass[i]->destination() == floor)
          state = STOP_STATE;
      }
      break;
    case STOP_STATE:
      state = UNLOAD_STATE;
      duration += STOP_TIME;
      break;
    case UNLOAD_STATE:
      for (i=0;i<MAX_PASSENGERS;i++)
      {
        // look for matching floor
        if (pass[i]->destination() == floor)
        {
          total_passenger_count++;
          passengers_on_board--;
          duration += LOAD_TIME;
          pass_on_floor[floor]++;
        }
      }
      if (passengers_on_board > 0)
        state = UP_STATE;
      else
      {
        // all passengers are unloaded - they can be eradicated
        for (i=0;i<MAX_PASSENGERS;i++)
        {
          delete pass[i];
          pass[i]=NULL;
        }
        state = DOWN_STATE;
        duration += TURN_TIME;
      }
      break;
    case DOWN_STATE:
      direction = DOWN_DIRECTION;
      floor--;
      duration += FLOOR_TIME;
      if (floor == LOBBY_FLOOR)
        state = IDLE_STATE;
      break;
    default:
      break;
  } /* end of switch */
  total_duration += duration;

  // can use this to put delays into actual simulation
  // return duration;
} /* end of run */

double elevator::current_duration()
{
  return total_duration;
}

unsigned long elevator::passenger_flow_rate()
{
  double flow;  // rate of passers per hour
  double hours;

  hours = total_duration/(60.0*60.0);  // secs to hour
  if (hours > 0.0)
    flow = total_passenger_count/hours;
  else
    flow = 0.0;

  return (unsigned long)flow;
}

unsigned long elevator::current_total_passenger_count()
{
  return total_passenger_count;
}

unsigned short elevator::current_passengers_on_board()
{
  return ((unsigned short)passengers_on_board);
}

unsigned short elevator::current_floor()
{
  return floor;
}

unsigned short elevator::current_direction()
{
  return direction;
}

unsigned short elevator::current_state()
{
  return state;
}

int elevator::current_id()
{
  return elevator_id;
}

// destructor
elevator::~elevator()
{
  int i;
  // all passengers are unloaded - they can be eradicated
  for (i=0;i<MAX_PASSENGERS;i++)
  {
    if (pass[i] != NULL)
    {
      delete pass[i];
      pass[i] = NULL;
    }
  }
}

unsigned long *elevator::pass_on_floor_array()
{
  return pass_on_floor;
}

