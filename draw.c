// draw.c
#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

void draw_border( screen s, color c ) {
  int i, j;
  for (i = 0; i < 501; i++ ) {
    for (j = 0; j < 501; j++ ) {
      if ( i >= 490 || j >= 490 || i <= 10 || j <= 10 ) {
	c.red = 0;
	c.green = 0;
	c.blue = 0;
	plot (s, c, i, j);
      }
    }
  }
}

void draw_coord( screen s, color c ) {
  int i, j;
  for (i = 0; i < 501; i++ ) {
    for (j = 0; j < 501; j++) {
      if (i % 50 == 0 || j % 50 == 0 ) {
	c.red = 75;
	c.green = 75;
	c.blue = 75;
	plot (s, c, i, j);
      }
    }
  }
}

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int A, B, C, d;
  float xtest0, xtest1, ytest0, ytest1;
  int x = x0;
  int y = y0;
  xtest0 = x0;
  ytest0 = y0;
  xtest1 = x1;
  ytest1 = y1;

  float m = (ytest1 - ytest0) / (xtest1 - xtest0); // Slope
  int b = (y1 - (m * x1)); // y-intercept
  printf("Drawing a Line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
  printf("slope: %.2f and y-int: %d\n\n", m, b);


  /////////////////
  // SPECIAL CASES

  if (m == 1) { // y = x
    if ( x > x1 && y > y1) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Slope of 1 Working!\n\n");
    while (x <= x1 && y <= y1) {
      plot(s, c, x, y );
      x += 1;
      y += 1;
    }
  }

  else if (m == -1) { // y = -x
    if ( x < x1 && y < y1) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Slope of -1 Working!\n\n");
    while (x <= x1 && y >= y1) {
      plot(s, c, x, y );
      x += 1;
      y -= 1;
    }
  }

  //HORIZONTAL LINES
  else if (m == 0) { // Slope = 0
    if ( x > x1 ) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Slope of 0 Working!\n\n");
    while ( x <= x1 ) {
      plot(s, c, x, y );
      x+=1;
    }
  }

  //VERTICAL LINES
  if (x1 == x) { // Slope is Undefined (dy/dx => Undefined)
    if ( y > y1) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Undefined Slope Working!\n\n");
    while ( y <= y1 ) {
      plot(s, c, x, YRES - 1 - y);
      y+=1;
    }
  }

  //REGULAR CASES

  //OCTANTS 1 + 5;
  else if ( 0 < m && m < 1 ) { // Slope is less than 1 but greater than 0
    if ( x > x1 && y > y1) { 
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Octants 1 and 5 Working!\n\n");
    while ( x <= x1 ) {
      plot (s, c, x, y );
      A = (y1 - y);
      B = -1 * (x1 - x);
      C = b * (x1 - x);
      d = (A * x) + (B * y) + C;
      if (d > 0) {
	y += 1;
	d += (2 * B);
      }
      x += 1;
      d += (2 * A);
    }
  }

  //OCTANTS 2 + 6;
  else if ( m > 1 ) { // Slope is bigger than 1, so anything above y=x
    if ( x > x1 && y > y1) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Octants 2 and 6 Working!\n\n");
    while ( y <= y1 ) {
      plot (s, c, x, y );
      A = (y1 - y);
      B = -1 * (x1 - x);
      C = b * (x1 - x);
      d = (A * x) + (B * y) + C;
      if (d < 0) {
        x += 1;
        d += (2 * A);
      }
      y += 1;
      d += (2 * B);
    }
  }

  //OCTANTS 8 + 3;
  else if (-1 < m && m < 0) { // Slope is less than 0 but greater than -1
    if ( x > x1 && y < y1) {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Octants 8 and 4 Working!\n\n");
    while ( x <= x1 ) { 
      plot (s, c, x, y );
      A = (y1 - y);
      B = -1 * (x1 - x);
      C = b * (x1 - x);
      d = (A * x) + (B * y) + C;
      if (d < 0) {
        y -= 1;
        d -= (2 * B);
      }
      x += 1;
      d += (2 * A);
    }
  }

  //OCTANTS 7 + 3;
  else if ( m < -1 ) {// Slope is less than -1 so anything less than y=-x
    if ( x > x1 && y < y1) { 
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
    }
    //    printf("Octants 7 and 3 Working!\n\n");
    while ( y >= y1 ) {
      plot (s, c, x, y );
      A = (y1 - y);
      B = -1 * (x1 - x);
      C = b * (x1 - x);
      d = (A * x) + (B * y) + C;
      if (d > 0) {
        x += 1;
        d += (2 * A);
      }
      y -= 1;
      d -= (2 * B);
    }
  }

  //DONE

}

