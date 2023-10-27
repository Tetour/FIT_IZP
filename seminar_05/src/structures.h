#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <limits.h>

#define DATES_LEN 3


typedef struct {
    int year;
    int month;
    int day;
    int temperature;
} Date;

void  structures();
int   printDates(Date dates[DATES_LEN]);
int   isDateValid(Date date);
float getAverageTemperature(Date dates[DATES_LEN], int datesLen);


#endif // STRUCTURES_H