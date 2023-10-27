#include "structures.h"


void structures() {

    Date date_1 = {.year = 1995, .month = 9, .day = 22, .temperature = 18};
    Date date_2 = {.year = 1995, .month = 9, .day = 23, .temperature = 21};
    Date date_3 = {.year = 1995, .month = 9, .day = 24, .temperature = 25};

    Date dates[DATES_LEN];
    dates[0] = date_1;
    dates[1] = date_2;
    dates[2] = date_3;

    int datesLen = (int)(sizeof(dates)/sizeof(dates[0]));
    printf("%f\n", getAverageTemperature(dates, datesLen));
}

int printDates(Date dates[DATES_LEN]) {

    printf("year: %d\n", dates->year);
    printf("month: %d\n", dates->month);
    printf("day: %d\n", dates->day);
    printf("temperature: %d\n", dates->temperature);

    return 0;
}

/**
 * @return 1 if date is valid, 0 if date is invalid
 */
int isDateValid(Date date) {
    int retVal = 0;
    
    // TODO: add different length of months and gap year days
    if (date.year >= 0 && date.year <= INT_MAX && date.month >= 0 && date.month <= 12 && date.day >= 0 && date.day <= 31) {
        retVal = 1;
    }

    return retVal;
}

float getAverageTemperature(Date dates[DATES_LEN], int datesLen) {
    int totalTemperature = 0;
    int i = 0;

    while (i < datesLen) {
        totalTemperature += dates->temperature;
        i++;
    }
    
    float averageTemperature = (float)totalTemperature / (float)i;

    return averageTemperature;
}
