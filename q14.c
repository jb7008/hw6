/*
 * Programmer : Josh Booth      Date : Mar 28 , 2019
 * Instructor : Professor Hou   Class : ENGR 120 - 03
 *
 * Evaluates a polynomial
 */

#include <stdio.h> /* Includes printf, scanf */
#include <math.h> /* Inclues pow */

#define MAX_COEFF 8 /* Maximum number of coefficients */

/* Gets the coefficients of a x^degreep polynomial */
void get_poly(double coeff[], int* degreep);
/* Evaluates the polynomial at x */
double eval_poly(const double coeff[], int degree, double x);

int
main(void)
{
  int degreep; /* Degree of the polynomial */
  double coeff[MAX_COEFF], /* Holds the coefficients for each term */
    x, /* X values to evaluated the polynomial at */
    poly_value; /* Values of the evaluated polynomial */

  /* Gets the coefficients in array */
  get_poly(coeff, &degreep);

  /* Gets the x value */
  printf("Enter x: ");
  scanf("%lf", &x);

  /* Evaluates the polynomial at x */
  poly_value = eval_poly(coeff, degreep, x);

  /* Displays the results */
  printf("Value: %lf\n", poly_value);

  return 0;
}

/* Gets the coefficients of a x^degreep polynomial */
void
get_poly(double coeff[], int* degreep)
{
  /* Gets the degree of the polynomial */
  printf("Enter the degree [1,8]: ");
  scanf("%d", degreep);

  /* Gets the coefficients */
  /* 1 is added for the x^0 element */
  for(int i = *degreep + 1; i > 0; i--)
  {
    /* i - 1 is used to account for the x^0 element */
    printf("Enter A[%d]: ", i - 1);
    scanf("%lf", &coeff[i - 1]);
  }
}

/* Evaluates the polynomial at x */
double
eval_poly(const double coeff[], int degree, double x)
{
  double running_total = 0; /* Running total value */

  /* Runs through all degrees */
  for(int i = 0; i <= degree; i++)
  {
    /* Takes x to the i power and multiplies it by the coefficient */
    running_total += (coeff[i] * pow(x, i));
  }

  return running_total; /* Returns the running total */
}