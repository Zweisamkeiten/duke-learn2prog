#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info {
  int months;
  double contribution, rate_of_return;
} retire_info;

void retirement (int startAge,      // in months
		 double initial,    // initial savings in dollars
		 retire_info working, // info about working
		 retire_info retired) // info about being retired
{
  int ageMonths = startAge;
  double balance = initial;
  int retiredAge = startAge + working.months;
  int endAge = startAge + working.months + retired.months;
  while (ageMonths < endAge) {
    printf("Age %3d month %2d you have $%.2lf\n", ageMonths / 12,
	   ageMonths % 12, balance);
    ageMonths += 1;
    double rate_of_return = ageMonths <= retiredAge ? working.rate_of_return : retired.rate_of_return;
    double contribution = ageMonths <= retiredAge ? working.contribution : retired.contribution;
    balance = balance * (1 + rate_of_return / 12) + contribution;
  }
}

int main(void) {
  retire_info working = {489, 1000, 0.045};
  retire_info retired = {384, -4000, 0.01};

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
