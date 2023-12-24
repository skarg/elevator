// ***********************************************************************
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
// Filename:    elevtask.cpp
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
// ***********************************************************************

#include "main.h"
#include "elevsim.h"
#include "graphics.h"
#include <SDL2/SDL.h>  

int render(elevsim *pElevator, char ch)
{
  static int color = 0;
  static int last_tick = 0;
  int status = 0;

  status = pElevator->run(ch);

  graphics_update();

  return status;
}

int main(int argc, char **argv)
{
  elevsim the_elevator;
  int status = 0;

  SDL_Event event; /* Event structure */
  char ch = 0;
  
  graphics_init("Elevator Simulator",VIDEO_MAX_X,VIDEO_MAX_Y);
  graphics_background(BLACK);
  /* Check for events */
  for ( ; ; )
  {
    SDL_Delay(1);
    status = render(&the_elevator,ch);
   if (status == -1)
     return 0;
   ch = 0;
    //look for an event
    if (SDL_PollEvent(&event))
    {
      //an event was found
      switch(event.type)
      {
        case SDL_KEYDOWN:
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym)
          {
            case  SDLK_ESCAPE:
              return 0;
            case SDLK_0:
              ch = '0';
              break;
            case SDLK_1:
              ch = '1';
              break;
            case SDLK_2:
              ch = '2';
              break;
            case SDLK_3:
              ch = '3';
              break;
            case SDLK_4:
              ch = '4';
              break;
            case SDLK_5:
              ch = '5';
              break;
            case SDLK_6:
              ch = '6';
              break;
            case SDLK_7:
              ch = '7';
              break;
            case SDLK_8:
              ch = '8';
              break;
            case SDLK_9:
              ch = '9';
              break;
            default:
              break;
          }
          break;      
        case SDL_QUIT:
          return 0;
        default:
          break;
      }
    }
  }//end of message pump
  
  return 0;
} // end of main


