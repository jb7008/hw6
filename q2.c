/*
 * Programmer : Josh Booth      Date : Mar 28 , 2019
 * Instructor : Professor Hou   Class : ENGR 120 - 03
 *
 * Calculates the area of a convex polygon
 */

#include <stdio.h> /* Includes printf, scanf */
#include <stdlib.h> /* Includes abs */

#define MAX_SIZE 100 /* Max size arrays can be */

/* Get corner coordinates in arrays and returns length of arrays */
int get_corners(FILE *inp, double x_coords[], double y_coords[], int max_size);
/* Outputs array coordiantes to a file */
void output_corners(FILE *outp, double x_coords[], double y_coords[],
  int coord_size);
/* Returns enclosed area by polygon */
double polygon_area(double x_coords[], double y_coords[], int coord_size);

int
main(void)
{
  FILE *inp; /* Pointer to input file */
  FILE *outp; /* Pointer to output file */
  double x_coords[MAX_SIZE], /* X coordinates */
    y_coords[MAX_SIZE], /* Y coordinates */
    area; /* Calculates polygon area */
  int max_size = MAX_SIZE, /* Max size the array can be */
    num_of_coords; /* Numbers of coordinates */

  /* Prepares files for input or output */
  inp = fopen("q2_input.txt", "r");
  outp = fopen("q2_output.txt", "w");

  /* Get corner coordinates in arrays and returns length of arrays */
  num_of_coords = get_corners(inp, x_coords, y_coords, max_size);

  /* Closes input file */
  fclose(inp);

  /* Returns enclosed area by polygon */
  area = polygon_area(x_coords, y_coords, num_of_coords);

  /* Prints calculates area */
  printf("The area of %d points is %lf.\n", num_of_coords, area);

  /* Outputs array coordiantes to a file */
  output_corners(outp, x_coords, y_coords, num_of_coords);

  /* Closes output file */
  fclose(outp);

  return 0;
}

/* Get corner coordinates in arrays and returns length of arrays */
int
get_corners(FILE *inp, double x_coords[], double y_coords[], int max_size)
{
  double x, /* Variable to scan x coordinate into before putting it in array */
  y; /* Variable to scan y coordinate into before putting it in array */
  int input_status, /* Status value returned by scanf */
    array_length = 0; /* Current array length read */
  do
  {
    /* Scan x and y from file */
    input_status = fscanf(inp, "%lf %lf", &x, &y);
    /* Append x coordinate to x array */
    x_coords[array_length] = x;
    /* Append y coordinate to y array */
    y_coords[array_length] = y;
    /* Add one to array length */
    array_length++;
    /* Runs while EOF has been hit and MAX_SIZE hasn't been reached */
  } while(input_status != EOF && array_length < max_size);
  /* Terminates arrays */
  x_coords[array_length] = '\0';
  y_coords[array_length] = '\0';
  /* Returns array length (-1 is to remove accountance for termination char) */
  return(array_length - 1);
}

/* Outputs array coordiantes to a file */
void
output_corners(FILE *outp, double x_coords[], double y_coords[], int coord_size)
{
  /* Writes arrays to file */
  for(int i = 0; i < coord_size; i++)
  {
    fprintf(outp, "%f %f\n", x_coords[i], y_coords[i]);
  }
}

/* Returns enclosed area by polygon */
double
polygon_area(double x_coords[], double y_coords[], int coord_size)
{
  double sum = 0; /* Running sum */

  /* Formula listed in book */
  for(int i = 0; i < coord_size - 2; i++)
  {
    sum += (x_coords[i + 1] + x_coords[i]) * (y_coords[i + 1] - y_coords[i]);
  }
  /* Finishes formula */
  sum = abs(sum) * (1/2.0);

  /* Returns calculates sum */
  return (sum);
}