// draw.c

#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int m, A, B, C;
  int x = x0;
  int y = y0;
  m = (y1 - y) / (x1 - x);
  int b = (y1 - (m * x1));
  //  printf("slope: %d and y-int: %d\n", m, b);
  
  //OCTANT 1;
  if ( 0 < m < 1 ) {
    //    if ( y1 < y0 ) {
    while ( x0 <= x1 ) {
      plot (s, c, x, y );
      A = (y1 - y);
      B = -1 * (x1 - x);
      C = b * (x1 - x);
      

  
  //OCTANT 2;
  
  //OCTANT 8;
  
  //OCTANT 7;
  

}

