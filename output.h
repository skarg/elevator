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
// Filename:    output.h
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

#ifndef outputFile
#define outputFile

#include "main.h"
#include "graphics.h"

class output
{
  protected:
   int line_size;
   COLORS line_color;
   int text_size;
   COLORS text_color;
  public:
   output(); /* constructor */
   virtual ~output(); /* destructor */
   virtual void Draw_Text(int text_x,int text_y,char *string) = 0;
   virtual void Draw_Line(int x1,int y1,int x2,int y2) = 0;
   virtual void Draw_Circle(int center_x,int center_y,int radius) = 0;
   virtual void Draw_Rectangle(int left,int top,int right,int bottom) = 0;
   void Set_Text_Size(int size);
   void Set_Text_Color(COLORS color);
   void Set_Line_Size(int size);
   void Set_Line_Color(COLORS color);
   virtual void Clear_Screen(void) = 0;
   void Delay(long ticks);
   void Update_Screen(void);
};

class screen_output : public output
{
  public:
    screen_output();
    ~screen_output();
    void Draw_Text(int text_x,int text_y,char *string);
    void Draw_Line(int x1,int y1,int x2,int y2);
    void Draw_Circle(int center_x,int center_y,int radius);
    void Draw_Rectangle(int left,int top,int right,int bottom);
    void Clear_Screen(void);
};

class printer_output : public output
{
  public:
    printer_output();
    ~printer_output();
    void Draw_Text();
    void Draw_Line();
    void Draw_Circle();
    void Draw_Rectangle();
    void Clear_Screen(void);
};

#endif
