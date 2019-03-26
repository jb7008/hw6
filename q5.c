/*
 * Programmer : Josh Booth      Date : Mar 28 , 2019
 * Instructor : Professor Hou   Class : ENGR 120 - 03
 *
 * Barcode calculator
 */

#include <stdio.h> /* Includes printf, scanf */

#define BARCODE_DIGITS 12 /* Number of digits in a barcode */
#define CHECK_DIGIT_LOCATION 11
#define INPUT_FILE "q5_input.txt" /* Name of input file */

/* Reads barcode from file */
int read_barcode(FILE *inp, int barcode[]);
/* Finds the check digit for the passed barcode */
int calc_check_digit(int barcode[]);

int
main(void)
{
  FILE *inp; /* Pointer for input file */

  inp = fopen(INPUT_FILE, "r"); /* Handle for input file */

  int barcode[12], /* Array for storing barcode + check digit */
    calculation, /* Check digit calculation */
    check_digit, /* Stores check digit */
    calc_last_digit;

  while(read_barcode(inp, barcode)) /* While barcordes can be read */
  {
    calculation = calc_check_digit(barcode); /* Calculates check digit */
    calc_last_digit = calculation % 10; /* Gets last digit of calculation */
    check_digit = barcode[CHECK_DIGIT_LOCATION]; /* Stores check digit */
    if(check_digit == 0 && calc_last_digit == 0)
    {
      printf("valid\n");
    }
    else if(10 - calc_last_digit == check_digit)
    {
      printf("valid\n");
    }
    else
    {
      printf("digit %d does not match 0\n", 10 - calc_last_digit);
    }
  }

  fclose(inp);

  return 0;
}

/* Reads barcode from file */
int read_barcode(FILE *inp, int barcode[])
{
  /* Reads each digit into barcode array */
  for(int i = 0; i < BARCODE_DIGITS; i++) 
  {
    /* If there isn't anything left to read */
    if(fscanf(inp, "%d", &barcode[i]) == EOF) 
    {
      return 0;
    }
    /* Prints the read barcode with a space between each digit */
    printf("%d ", barcode[i]);
  }
  return 1; /* Returns if a barcode was successfully read */
}


/* Finds the check digit for the passed barcode */
int
calc_check_digit(int barcode[])
{
  int sum = 0; /* Running sum */

  /* Adds all odd numbered digits in barcode except check digit */
  for(int i = 0; i < BARCODE_DIGITS - 1; i += 2)
  {
    sum += barcode[i];
  }
  sum *= 3; /* Multiplies odd numbered addition by 3 */

  /* Adds all even numbered digits in barcode except check digit */
  for(int i = 1; i < BARCODE_DIGITS - 1 ; i += 2)
  {
    sum += barcode[i];
  }
  return(sum);
}