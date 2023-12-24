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
// Filename:    display.cpp
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
// History:  1: 08-Oct-1996: Created file. - Steve Karg
//           2: 18-Oct-1996: Removed sync with ios. - Steve Karg
//
//************************************************************************
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "display.h"
#include "output.h" 
#include "elevsupp.h"

display_graphics::display_graphics()
{
  #ifdef DEBUG
  printf("display_graphics\n");
  #endif

  old_flow[0] = 0;
  floor_height     = ((VIDEO_MAX_Y/2)/MAX_FLOORS);
  floor_width      = (VIDEO_MAX_X/3);
  shaft_width      = (VIDEO_MAX_X/32);
  building_x_start = (VIDEO_MAX_X/3); /* left side of screen */
  building_y_start = (VIDEO_MAX_Y/6); /* top of screen */
}

void display_graphics::display_passenger_per_hour(long passperhour)
{
  char string[80];
  int text_x = {(int)((long)VIDEO_MAX_X * 100L/160L)};// quicker than /1.6
  int text_y = {(VIDEO_MAX_Y/12)};

  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(BLACK);
  disp_out.Draw_Text(text_x,text_y,old_flow);

  sprintf(string,"%010ld",passperhour);
  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(WHITE);
  disp_out.Draw_Text(text_x,text_y,string);
  strcpy(old_flow,string);
}

void display_graphics::display_static_building(int number_of_elevators)
{
  int floor_index;
  int elev_index;
  int floor_y;
  int shaft_line;
  int x_start; /* left side of screen */
  int y_start; /* top of screen */
  char string[80];
  int text_x = {(VIDEO_MAX_X/4)};
  int text_y = {0};

  x_start = building_x_start;
  y_start = building_y_start;

  disp_out.Set_Text_Size(24);
  disp_out.Set_Text_Color(LIGHTGREEN);
  sprintf(string,"ELEVATOR SIMULATION");
  disp_out.Draw_Text(text_x,text_y,string);

  disp_out.Set_Line_Color(WHITE);
  for(floor_index=0;floor_index<MAX_FLOORS;floor_index++)
  {
    /* draw the floor of the building */
	floor_y = (floor_index*floor_height) + y_start;
    disp_out.Draw_Rectangle(x_start,floor_y,floor_width,floor_height);

    /* draw the elevator shafts */
    for(elev_index=0;elev_index<number_of_elevators;elev_index++)
    {
      shaft_line = x_start + (elev_index*shaft_width) + shaft_width;
      disp_out.Draw_Line(shaft_line,floor_y,shaft_line,floor_y + shaft_width);
    } /* end of elevator loop */
  } /* end of floor loop */

  // passenger per hour heading
  text_x = (VIDEO_MAX_X/4);
  text_y = (VIDEO_MAX_Y/12);
  sprintf(string,"Passengers per hour: ");
  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(WHITE);
  disp_out.Draw_Text(text_x,text_y,string);

  // show escape sequence
  text_x = (VIDEO_MAX_X/4);
  text_y = ((MAX_FLOORS*floor_height)+y_start);// just below the building
  sprintf(string,"Press 9 to return to menu");
  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(YELLOW);
  disp_out.Draw_Text(text_x,text_y,string);

} /* end of method */


void display_graphics::display_dynamic_elevator(int elevator_num,
                                                int floor_num,
                                                int display)
{
/* note: elevator number is the elevator index
         floor number is the floor index
         display is true if you want color, false if you want clear */
  int x_start,y_start,floor_x,floor_y;
  int lobby_bottom;
  const int offset = 2;

  x_start = building_x_start;
  y_start = building_y_start;

  /* since floors are inverse with graphics, we need to find the
     bottom floor coordinates */
  lobby_bottom = ((MAX_FLOORS-1)*floor_height) + y_start;

  /* calculate the elevator top left point */
  floor_x 
	= x_start + (elevator_num*shaft_width) + offset;
  floor_y
    = lobby_bottom - (floor_num*floor_height) + offset;

  /* set the color if displaying or unset the color if not */
  if (display)
    disp_out.Set_Line_Color(CYAN);
  else
    disp_out.Set_Line_Color(BLACK);

  disp_out.Draw_Rectangle(
	  floor_x, floor_y, 
	  shaft_width - (offset * 2), floor_height - (offset * 2));
}

void display_graphics::display_passenger_exit(int floor)
{
  /* note: floor number is the floor index */
  int index;
  int x_start,y_start,floor_top,floor_bottom;
  int floor_left,floor_right;
  int center,width;
  int lobby_bottom;
  int animate;

  x_start = building_x_start;
  y_start = building_y_start;

  /* since floors are inverse with graphics, we need to find the
     bottom floor coordinates */
  lobby_bottom = ((MAX_FLOORS-1)*floor_height) + y_start;

  /* calculate the floor top and bottom */
  floor_top
    = lobby_bottom - (floor*floor_height) + 2;
  floor_bottom
    = lobby_bottom - (floor*floor_height) + floor_height - 2;

  /* calculate the floor sides */
  floor_left  = x_start + (MAX_ELEVATORS*shaft_width) + 2;
  floor_right = x_start + floor_width - 2;

  /* person animation */
  animate=15;
  for (index=0;index<animate;index++)
  {
   width  = ((floor_right-floor_left)/animate);
   center = (floor_left+(width*index)+(width/2));
   disp_out.Set_Line_Color(WHITE);
   Draw_Person(floor_bottom,floor_top,center,width);
   //disp_out.Delay(1);
   disp_out.Update_Screen();
   disp_out.Set_Line_Color(BLACK);
   Draw_Person(floor_bottom,floor_top,center,width);
  }
}

void display_graphics::Draw_Person(int bottom,int top,
                        int center,int width)
{
  int x1,x2,y1,y2;
  int height;
  int quad;
  int radius;

  height = bottom - top;
  quad = height/8;

  /* head */
  y1 = bottom-(quad*6);
  x1 = center;
  radius = quad;
  disp_out.Draw_Circle(x1,y1,radius);

  /* body */
  y1 = bottom-(quad*5);
  x1 = center;
  y2 = bottom-(quad*2);
  x2 = center;
  disp_out.Draw_Line(x1,y1,x2,y2);

  /* arms */
  y1 = bottom-(quad*4);
  x1 = center+(width/3);
  y2 = bottom-(quad*4);
  x2 = center-(width/3);
  disp_out.Draw_Line(x1,y1,x2,y2);

  /* left leg */
  y1 = bottom;
  x1 = center-(width/2);
  y2 = bottom - (quad*2);
  x2 = center;
  disp_out.Draw_Line(x1,y1,x2,y2);

  /* right leg */
  y1 = bottom;
  x1 = center+(width/2);
  y2 = bottom-(quad*2);
  x2 = center;
  disp_out.Draw_Line(x1,y1,x2,y2);
}


void display_graphics::display_passenger_entry(void)
{
  /* note: floor number is the floor index */
  int index,count;
  int x_start,y_start,floor_top,floor_bottom;
  int floor_left,floor_right;
  int center,width;
  int lobby_bottom;
  int animate;
  int floor = LOBBY_FLOOR; /* only enter on lobby floor */

  x_start = building_x_start;
  y_start = building_y_start;

  /* since floors are inverse with graphics, we need to find the
    bottom floor coordinates */
  lobby_bottom = ((MAX_FLOORS-1)*floor_height) + y_start;

  /* calculate the floor top and bottom */
  floor_top
   = lobby_bottom - (floor*floor_height) + 2;
  floor_bottom
   = lobby_bottom - (floor*floor_height) + floor_height - 2;

  /* calculate the floor sides */
  floor_left  = x_start + (MAX_ELEVATORS*shaft_width) + 2;
  floor_right = x_start + floor_width - 2;

  /* person animation */
  animate=15;
  for (count=0;count<animate;count++)
  {
   index = animate-(count+1);
   width  = ((floor_right-floor_left)/animate);
   center = (floor_left+(width*index)+(width/2));
   disp_out.Set_Line_Color(WHITE);
   Draw_Person(floor_bottom,floor_top,center,width);
   //disp_out.Delay(1);
   disp_out.Update_Screen();
   disp_out.Set_Line_Color(BLACK);
   Draw_Person(floor_bottom,floor_top,center,width);
  }
}


int display_graphics::display_menu(char ch)
{
  int choice = MENU_INVALID_CHOICE;
  int text_x = 0;
  int text_y = 0;


  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(WHITE);
  disp_out.Clear_Screen();
  disp_out.Draw_Text(text_x,text_y,
    "     Elevator Simulation"
    "\n\n"
    "1. Begin Elevator Simulation\n"
    "2. Print Report\n"
    "3. Exit\n"
    "\n\n"
    "Enter your selection: ");

  /* bounds check - is it a valid menu choice? */
  if (isdigit(ch))
  {
    switch (ch)
    {
      case '1':
        choice = MENU_BEGIN_SIMULATION;
        break;
      case '2':
        choice = MENU_PRINT_REPORTS;
        break;
      case '3':
        choice = MENU_EXIT;
        break;
      default:
        choice = MENU_INVALID_CHOICE;
        break;
    }
  } /* end of digit entered */

  return choice;
} /* end of function */

int display_graphics::display_number_of_elevators_prompt(char ch)
{
  int choice = MENU_INVALID_CHOICE;
  int text_x = 0;
  int text_y = 0;   
  char menu_text[320] = {""};

  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(WHITE);
  disp_out.Clear_Screen();
  sprintf(menu_text,
    "     Elevator Simulation"
    "\n\n"
    "Begin Elevator Simulation\n"
    "(enter 0 for main menu)\n"
    "\n"
    "Please enter the number of\n"
    "elevators you want to see [0 to %d]: ",
    MAX_ELEVATORS);
  disp_out.Draw_Text(text_x,text_y,menu_text);

  /* bounds check - is it a valid menu choice? */
  if (isdigit(ch))
  {
    choice = ch - '0';
    if ((choice < 0) || (choice > MAX_ELEVATORS))
      choice = MENU_INVALID_CHOICE;
  } /* end of digit entered */

  return choice;
}

int display_graphics::display_print_reports_options(char ch)
{
  int choice = MENU_INVALID_CHOICE;
  int text_x = 0;
  int text_y = 0;


  disp_out.Set_Text_Size(16);
  disp_out.Set_Text_Color(WHITE);
  disp_out.Clear_Screen();
  disp_out.Draw_Text(text_x,text_y,
    "     Elevator Simulation"
    "\n\n"
    "        Print Report\n"
    "1. To the printer\n"
    "2. To the screen\n"
    "3. Return to main menu\n"
    "\n\n"
    "Enter your selection: ");

  /* bounds check - is it a valid menu choice? */
  if (isdigit(ch))
  {
    switch(ch)
    {
      case '1':
        choice = MENU_PRINT_TO_PRINTER;
        break;
      case '2':
        choice = MENU_PRINT_TO_SCREEN;
        break;
      case '3':
        choice = MENU_RETURN_TO_MAIN;
        break;
      default:
        break;
    }
  } /* end of digit entered */

  return choice;
}

void display_graphics::Clear_Screen(void)
{
  disp_out.Clear_Screen();
}
