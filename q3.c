/*
 * Programmer : Josh Booth      Date : Mar 28 , 2019
 * Instructor : Professor Hou   Class : ENGR 120 - 03
 *
 * Reads coordinates from file and calculates center of gravity
 */

#include <stdio.h> /* Includes printf, scanf */

#define MAX_SIZE 100 /* Max number of coordinates */
#define INPUT_FILE "q3_input.txt" /* Input data file */
#define OUTPUT_FILE "q3_output.txt" /* Output data file */
/* When arrays needs 3 spaces to hold x y and z coordinates */
#define XYZ_COORDS 3
#define X_LOC 0 /* x location in array */
#define Y_LOC 1 /* y location in array */
#define Z_LOC 2 /* z location in array */

/* Gets number of coordinates, coordiantes, and mass of each coordinate from
 file */
int fget_point_mass(FILE *inp, int max_n, int coords[][XYZ_COORDS], int mass[]);
/* Calculates the center of gravity */
void center_grav(int coords[][XYZ_COORDS], int mass[], int n,
  double center_of_gravity[]);
/* Prints calculations and writes to file */
void fwrite_point_mass(FILE *outp, int coords[][XYZ_COORDS], int mass[], int n,
  double center_of_gravity[]);

int
main(void)
{
  FILE *inp; /* Pointer for input file */
  FILE *outp; /* Pointer for output file */

  int coords[MAX_SIZE][XYZ_COORDS], /* 2D array to hold coordiantes */
    mass[MAX_SIZE], /* Array to hold the respective mass of the coordinates */
    loc_nums, /* Number of location arrays */
    max_n = MAX_SIZE; /* Max possible size of n */
  double center_of_gravity[XYZ_COORDS]; /* x, y, z calculations for center of
    gravity */

  inp = fopen(INPUT_FILE, "r"); /* Opens input file */
  outp = fopen(OUTPUT_FILE, "w"); /* Opens output file */

  /* Gets number of coordinates, coordiantes, and mass of each coordinate from
  file */
  loc_nums = fget_point_mass(inp, max_n, coords, mass);
  /* Calculates the center of gravity */
  center_grav(coords, mass, loc_nums, center_of_gravity);
  /* Prints calculations and writes to file */
  fwrite_point_mass(outp, coords, mass, loc_nums, center_of_gravity);

  fclose(inp); /* Closes input file */
  fclose(outp); /* Closes output file */

  return 0;
}


/* Gets number of coordinates, coordiantes, and mass of each coordinate from
  file */
int fget_point_mass(FILE *inp, int max_n, int coords[][XYZ_COORDS], int mass[])
{
  int x, /* Temporary x coordinate */
    y, /* Temporary y coordinate */
    z, /* Temporary z coordinate */
    m, /* Temporary mass holder */
    n; /* Number of locations read */

  /* Get n */
  fscanf(inp, "%d", &n);
  /* Reads x, y, z, and mass and puts into respective matricies */
  for(int i = 0; i < n && fscanf(inp, "%d %d %d %d", &x, &y, &z, &m) != EOF;
    i++)
  {
    coords[i][X_LOC] = x; /* Location 0 in array is for x coordinate */
    coords[i][Y_LOC] = y; /* Location 1 in array is for y coordinate */
    coords[i][Z_LOC] = z; /* Location 2 in array is for z coordinate */
    mass[i] = m;
  }
  return (n); /* Returns number of locations */
}

/* Calculates the center of gravity */
void
center_grav(int coords[][XYZ_COORDS], int mass[], int n,
  double center_of_gravity[])
{
  double mass_sum = 0, /* Sum of all read masses */
    running_total = 0; /* Running total for each calculation */

  /* Finds the total mass sum */
  for(int i = 0; i < n; i++)
  {
    mass_sum += mass[i];
  }
  /* Finds center of mass for x coordinate */
  for(int i = 0; i < n; i++)
  {
    /* Multiplies all respective masses with the x coordinate and adds to the
      running sum */
    running_total += mass[i] * coords[i][X_LOC];
  }
  /* Sets the y calulation as running_total */
  center_of_gravity[X_LOC] = running_total;
  running_total = 0; /* Resets running total */

  /* Finds center of mass for y coordinate */
  for(int i = 0; i < n; i++)
  {
    /* Multiplies all respective masses with the y coordinate and adds to the
      running sum */
    running_total += mass[i] * coords[i][Y_LOC];
  }

  /* Sets the x calulation as running_total */
  center_of_gravity[Y_LOC] = running_total;
  running_total = 0; /* Resets running total */

  /* Finds center of mass for y coordinate */
  for(int i = 0; i < n; i++)
  {
    /* Multiplies all respective masses with the z coordinate and adds to the
      running sum */
    running_total += mass[i] * coords[i][Z_LOC];
  }
  /* Sets the z calulation as running_total */
  center_of_gravity[Z_LOC] = running_total;
  running_total = 0; /* Resets running total */

  /* Divides each final calculation by the sum of the masses */
  for(int i = 0; i < XYZ_COORDS; i++)
  {
    center_of_gravity[i] *= (1.0 / mass_sum);
  }

}

  /* Prints calculations and writes to file */
void
fwrite_point_mass(FILE *outp, int coords[][XYZ_COORDS], int mass[], int n,
  double center_of_gravity[])
{
  /* First prints out all the data */
  printf("======================\n");
  printf("Center of mass: (%lf %lf %lf)\n", center_of_gravity[X_LOC], 
    center_of_gravity[Y_LOC],  center_of_gravity[Z_LOC]);
  printf("Location:\n");
  /* Prints out all coordinates */
  for(int i = 0; i < n; i++)
  {
      printf("%lf %lf %lf\n", (double)coords[i][X_LOC], 
        (double)coords[i][Y_LOC], (double)coords[i][Z_LOC]);
  }
  /* Prints out all masses */
  printf("Mass:\n");
  for(int i = 0; i < n; i++)
  {
    printf("%lf\n", (double)mass[i]);
  }
  /* Prints number of location read */
  printf("n: %d\n", n);

  /* Then writes output to file */
  fprintf(outp, "======================\n");
  fprintf(outp, "Center of mass: (%lf %lf %lf)\n", center_of_gravity[X_LOC],
    center_of_gravity[Y_LOC],  center_of_gravity[Z_LOC]);
  fprintf(outp, "Location:\n");
  /* Writes all coordinates */
  for(int i = 0; i < n; i++)
  {
      fprintf(outp, "%lf %lf %lf\n", (double)coords[i][X_LOC],
        (double)coords[i][Y_LOC], (double)coords[i][Z_LOC]);
  }
  fprintf(outp, "Mass:\n");
  /* Writes all masses */
  for(int i = 0; i < n; i++)
  {
    fprintf(outp, "%lf\n", (double)mass[i]);
  }
  /* Prints number of location read */
  fprintf(outp, "n: %d\n", n);
}
