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
// Filename:    output.cpp
//
// Programmer:  Steve Karg
//
// Module:      Elevator Simulation
//
// Technical
// Description: This class is responsible for maintaining the commands
//              for output to the screen or printer.
//
// History:  1: 12-Oct-1996: Created file. - Steve Karg
//
//************************************************************************

#include <stdio.h>
#include "main.h"
#include "graphics.h"
#include "output.h"

output::output() /* constructor */
{
  line_size = 1;
  line_color = WHITE;
  text_size = 1;
  text_color = RED;
}

output::~output()
{

}

void output::Delay(long ticks)
{
  graphics_delay(ticks);
}

void output::Update_Screen(void)
{
  graphics_update();
}

void output::Set_Text_Size(int size)
{
  text_size = size;
}

void output::Set_Text_Color(COLORS color)
{
  text_color = color;
}

void output::Set_Line_Size(int size)
{
  line_size = size;
}

void output::Set_Line_Color(COLORS color)
{
  line_color = color;
}

screen_output::screen_output() /* constructor */
{
  line_size = 1;
  line_color = WHITE;
  text_size = 10;
  text_color = BLACK;
}

screen_output::~screen_output() /* destructor */
{
}

void screen_output::Clear_Screen(void)
{
  graphics_background(BLACK);
}

void screen_output::Draw_Text(int text_x,int text_y,char *string)
{
  graphics_text(
    text_size, 
	text_color, 
	TEXT_JUSTIFY_LEFT,
	text_x, 
	text_y, 
	string);
}

void screen_output::Draw_Line(int x1,int y1,int x2,int y2)
{
  graphics_line(line_color, x1, y1, x2, y2);
}

void screen_output::Draw_Circle(int center_x,int center_y,int radius)
{
  graphics_circle(line_color, center_x, center_y, radius);
}

void screen_output::Draw_Rectangle(int left,int top,int right,int bottom)
{
  graphics_rectangle(line_color, false, left, top, right, bottom);
}


