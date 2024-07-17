#ifndef BETTING_H
#define BETTING_H

#include "horse.h"
#include "race.h"

// Function prototypes
void startBetting(const Horse horses[], int odds[], int positions[]);
void winBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount);
void showBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount);
void placeBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount);
void displayOdds(const Horse horses[], int odds[]);
void calculateOdds(const Horse horses[], int odds[], int positions[], TrackCondition trackCondition);

#endif // BETTING_H
