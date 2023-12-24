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
// Filename:    elevsim.cpp
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This module is the main module.
//
// History:  1: 03-Oct-1996: Created file. - Steve Karg
//
//************************************************************************

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "elevsupp.h"
#include "elevsim.h"


elevsim::elevsim()
{
  #ifdef DEBUG
  printf("elevsim\n");
  #endif

  int index;
  for (index=0;index<MAX_ELEVATORS;index++)
  {
   elevator_rack[index] = NULL;
   // initialize at something other than the lobby
   last_floor[index] = TOP_FLOOR;
  }
  for (index=0;index<MAX_FLOORS;index++)
  {
   floor_passengers[index] = 0;
  }

  // initialize at something other than zero
  last_max_flow_rate =
  last_min_flow_rate = 1;

  // initialize the rest
  min_flow_rate = 0;
  max_flow_rate = 0;
  total_passengers = 0;
  min_duration = 0;
  max_duration = 0;
  // simulation parameters
  number_of_elevators = 1;
  report_option = MENU_PRINT_TO_SCREEN;
  menu_choice = MENU_BEGIN_SIMULATION;
  run_menu_choice = MENU_INVALID_CHOICE;
  floor_index = 0;
  index = 0;
  floor_num = 0;    /* floor index */
  floor_array = NULL;
  elevator_state = IDLE_STATE;
}

elevsim::~elevsim()
{
  int index;
  for (index=0;index<MAX_ELEVATORS;index++)
  {
   if (elevator_rack[index] != NULL)
    delete elevator_rack[index];
   elevator_rack[index] = NULL;
  }
}

// called often
int elevsim::run(char ch)
{
  if (run_menu_choice == MENU_INVALID_CHOICE)
  {
    menu_choice = disp_out.display_menu(ch);
    switch (menu_choice)
	{
      case MENU_BEGIN_SIMULATION:
        // clean out rack - in case simulation is run more than once
        for (index=0;index<MAX_ELEVATORS;index++)
		{
          if (elevator_rack[index] != NULL)
            delete elevator_rack[index];
          elevator_rack[index] = NULL;
		}
		run_menu_choice = MENU_PROMPT_ELEVATORS;
	    return 0;
      case MENU_PRINT_REPORTS:
		run_menu_choice = MENU_PRINT_REPORTS;
	    return 0;
      case MENU_EXIT:
		return -1;
	}
  }

  switch (run_menu_choice)
  {
    case MENU_PROMPT_ELEVATORS:
      number_of_elevators = disp_out.display_number_of_elevators_prompt(ch);
	  // request to go back to main menu
      if (number_of_elevators == 0)
		run_menu_choice = MENU_INVALID_CHOICE;
	  // valid request
	  else if (number_of_elevators != MENU_INVALID_CHOICE)
	  {
	    run_menu_choice = MENU_RUN_SIMULATION;
        disp_out.Clear_Screen();
        /* create the elevators */
        for (index=0;index<MAX_ELEVATORS;index++)
		{
          if (index < number_of_elevators)
            elevator_rack[index] = new elevator(index+1);
          else
            elevator_rack[index] = NULL;
		}
        /* set up graphics screen */
        disp_out.display_static_building(number_of_elevators);
        min_duration = 0;
        max_duration = 0;
        total_passengers = 0;
	  }
	  break;
    case MENU_RUN_SIMULATION:
	  if (ch == '9')
	  {
		run_menu_choice = MENU_INVALID_CHOICE;
	    break;
	  }
      for (index=0;index<MAX_ELEVATORS;index++)
      {
        if (elevator_rack[index] != NULL)
        {
          elevator_rack[index]->run();
          /* find the smallest duration of all elevators */
          if (min_duration == 0) // first time
            min_duration = elevator_rack[index]->current_duration();
          else if (min_duration > elevator_rack[index]->current_duration())
            min_duration = elevator_rack[index]->current_duration();

          /* find the largest duration of all elevators */
          if (max_duration == 0) // first time
            max_duration = elevator_rack[index]->current_duration();
          else if (max_duration < elevator_rack[index]->current_duration())
          max_duration = elevator_rack[index]->current_duration();

          total_passengers +=
            elevator_rack[index]->current_total_passenger_count();

          floor_num = elevator_rack[index]->current_floor();
          elevator_state = elevator_rack[index]->current_state();

          /* draw passengers entering */
          if (elevator_state == LOAD_STATE)
            disp_out.display_passenger_entry();

          /* draw passengers exiting */
          if (elevator_state == UNLOAD_STATE)
            disp_out.display_passenger_exit(floor_num);

          /* draw the elevator at the appropriate floor */
          if (floor_num != last_floor[index])
		  {
            /* clear out old floor */
            disp_out.display_dynamic_elevator(
              index,last_floor[index],FALSE);
            /* redraw new floor */
            disp_out.display_dynamic_elevator(
              index,floor_num,TRUE);
            last_floor[index] = floor_num;
		  } /* end of floor change */
		} /* end of valid elevator */
	  } /* end of elevator index loop */
      /* NOTE: since total pass is constant, max flow uses min duration
         and vice versa. */
      min_flow_rate = flow_rate_from_secs(max_duration,total_passengers);
      max_flow_rate = flow_rate_from_secs(min_duration,total_passengers);
      if (max_flow_rate != last_max_flow_rate)
	  {
        disp_out.display_passenger_per_hour(max_flow_rate);
        last_max_flow_rate = max_flow_rate;
	  }
      break;
    case MENU_PRINT_REPORTS:
      report_option = disp_out.display_print_reports_options(ch);
	  if (report_option != MENU_INVALID_CHOICE)
	  {
	    run_menu_choice = report_option;
		index = 0;
        // initialize the floor count array
        for(floor_index=0;floor_index<MAX_FLOORS;floor_index++)
		{
          floor_passengers[floor_index] = 0;
		}
        disp_out.Clear_Screen();
	  }
	  break;
    case MENU_PRINT_TO_SCREEN:
      if (index < MAX_ELEVATORS)
	  {
	    if (elevator_rack[index] != NULL)
		{
		  sreport.print_elevator_report(
		    elevator_rack[index]->current_id(),
		    elevator_rack[index]->current_total_passenger_count(),
		    elevator_rack[index]->current_duration(),
		    elevator_rack[index]->passenger_flow_rate(),
		    elevator_rack[index]->pass_on_floor_array() );
          /* summarize the data */
		  // totalize the floor breakdown
		  floor_array = elevator_rack[index]->pass_on_floor_array();
		  for(floor_index=0;floor_index<MAX_FLOORS;floor_index++)
		  {
		    floor_passengers[floor_index] += floor_array[floor_index];
		  }
		} /* end of valid elevator */
		if (ch)
		  index++;
	  }
	  else
	  {
        sreport.print_summary_report(number_of_elevators,
          total_passengers,min_duration,max_duration,
          min_flow_rate,max_flow_rate,floor_passengers);
		if (ch)
		{
          disp_out.Clear_Screen();
          run_menu_choice = MENU_INVALID_CHOICE;
		}
	  }
      break;
    case MENU_PRINT_TO_PRINTER:
      // initialize the floor count array
      for(floor_index=0;floor_index<MAX_FLOORS;floor_index++)
      {
        floor_passengers[floor_index] = 0;
      }
      for (index=0;index<MAX_ELEVATORS;index++)
      {
        if (elevator_rack[index] != NULL)
        {
          preport.print_elevator_report(
            elevator_rack[index]->current_id(),
            elevator_rack[index]->current_total_passenger_count(),
            elevator_rack[index]->current_duration(),
            elevator_rack[index]->passenger_flow_rate(),
            elevator_rack[index]->pass_on_floor_array() );
          /* summarize the data */
          // totalize the floor breakdown
          floor_array = elevator_rack[index]->pass_on_floor_array();
          for(floor_index=0;floor_index<MAX_FLOORS;floor_index++)
          {
            floor_passengers[floor_index] += floor_array[floor_index];
          }
        } /* end of valid elevator */
      } /* end of elevator loop */
      preport.print_summary_report(number_of_elevators,
        total_passengers,min_duration,max_duration,
        min_flow_rate,max_flow_rate,floor_passengers);
      break;
    default:
      break;
  }
  return 0;
} // end of run

