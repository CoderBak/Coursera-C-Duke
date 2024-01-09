#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
    int months;
    double contribution;
    double rate_of_return;
};
typedef struct _retire_info retire_info;

double update(double current, retire_info info) {
    return current * (1 + info.rate_of_return) + info.contribution;
}

void printInfo(double current, int months) {
    int month = months % 12;
    int year = months / 12;
    printf("Age %3d month %2d you have $%.2lf\n", year, month, current);
}

double process(int startAge, retire_info info, double initial) {
    double cur = initial;
    for(int age = startAge; age < startAge + info.months; age += 1) {
        printInfo(cur, age);
        cur = update(cur, info);
    }
    return cur;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
    // startAge: in months
    // initial: initial savings in dollars
    // working: info about working
    // retired: info about being retired
    double newInit = process(startAge, working, initial);
    process(startAge + working.months, retired, newInit);
}

int main(void) {
    retire_info working, retired;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045 / 12;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01 / 12;
    retirement(327, 21345, working, retired);
    return 0;
}
