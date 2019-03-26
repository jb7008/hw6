/*
 * Programmer : Josh Booth      Date : Mar 28 , 2019
 * Instructor : Professor Hou   Class : ENGR 120 - 03
 *
 * Merges two arrays
 */

#include <stdio.h> /* Includes printf, scanf */

#define MAX_LENGTH 100 /* Max length of output array */
#define INPUT_FILE "q11_input.txt" /* Name of input file */

/* Gets the two arrays from input file */
void get_arrays(FILE *inp, double array1[], double array2[]);
/* Merges array1 and array2 */
void merge_arrays(double array1[], double array2[], double combined[]);
/* Prints combined matrix */
void print_combined(double combined[]);

int
main(void)
{
  FILE *inp; /* Pointer for input file */

  double array1[MAX_LENGTH / 2], /* Sets array 1 to be half of max length */
    array2[MAX_LENGTH / 2], /* Sets array 2 to be half of max length */
    combined[MAX_LENGTH]; /* Array that holds combined array1 and array2 */

  inp = fopen(INPUT_FILE, "r"); /* Gets input file handle */

  get_arrays(inp, array1, array2); /* Gets the two arrays from input file */

  merge_arrays(array1, array2, combined); /* Merges array1 and array2 */

  print_combined(combined); /* Prints merged array */

  fclose(inp); /* Closes input file */

  return 0;
}

/* Gets the two arrays from input file */
void
get_arrays(FILE *inp, double array1[], double array2[])
{
  int i = 0, /* Interator for going through filling arrays */
    reading_larger = 1; /* Flag for while reading in larger numbers than the 
      previous */
  fscanf(inp, "%lf ", &array1[i++]); /* Reads the first number */
  while(reading_larger) /* While reading larger numbers */
  {
    fscanf(inp, "%lf ", &array1[i]); /* Read in number */
    if(array1[i] < array1[i - 1]) /* If smaller than previous */
    {
      reading_larger = 0; /* Turn off flag */
    }
    else /* If not smaller, increment */
    {
      i++; 
    }

  }
  array2[0] = array1[i]; /* Assignments first element of newline (smaller 
    element) to the first value of array2 */
  array1[i] = '\0'; /* Ends the first array with a NULL */
  i = 1; /* Skips zero b/c already accounted for with previous assignment */
  while(fscanf(inp, "%lf ", &array2[i]) != EOF) /* Reads to EOF */
  {
    i++; /* Moves to next array element */
  }
  array2[i] = '\0'; /* Terminates array2 */
}


/* Merges array1 and array2 */
void
merge_arrays(double array1[], double array2[], double combined[])
{
  int array1_ended = 0, /* Flag for if array1 has ended */
    array2_ended = 0, /* Flag for if array2 has ended */
    array1_i = 0, /* Iterator for array1 */
    array2_i = 0, /* Iterator for array2 */
    combined_i = 0; /* Iterator for combined array */

  /* While neither array iterator has reached the end of the array */
  while(array1_ended == 0 || array2_ended == 0)
  {
    /* If array1 has terminated and array2 has not */
    if(array1[array1_i] == 0 && array2[array2_i] != 0)
    {
      array1_ended = 1; /* Mark flag array1 has ended */

      /* Add the rest of array2 to combined */
      combined[combined_i++] = array2[array2_i++];
    }
    /* Else if array2 has terminated and array1 has not */
    else if(array2[array2_i] == 0 && array1[array1_i] != 0)
    {
      array2_ended = 1; /* Mark flag array2 has ended */

        /* Add the rest of array1 to combined */
      combined[combined_i++] = array1[array1_i++];
    }
    else /* If neither array has terminated */
    {
      /* Puts smaller value in the combined array then increments combined and
        that array's incrementer */
      if(array1[array1_i] < array2[array2_i])
      {
        combined[combined_i++] = array1[array1_i++];
      }
      else if(array2[array2_i] < array1[array1_i])
      {
        combined[combined_i++] = array2[array2_i++];
      }
      else{ /* If the two values are equal */
        combined[combined_i++] = array1[array1_i++];
        array2_i++; /* Increments last array */
      }
    }
  }
}


/* Prints combined matrix */
void
print_combined(double combined[])
{
  /* Prints all values in array */
  for(int i = 0; combined[i]; i++)
  {
    printf("%.0lf ", combined[i]);
  }
  printf("\n"); /* Prints newline for formatting */
}