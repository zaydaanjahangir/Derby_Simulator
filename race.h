
#ifndef RACE_H
#define RACE_H
#include "horse.h"

#define NUM_HORSES 6
#define NUM_SIMULATIONS 1000000
#define FINISH_LINE 100

typedef enum {
    DRY,
    WET,
    MUDDY
} TrackCondition;


void simulateRace(Horse horses[], int positions[], int horseIndices[]);
void displayResults(const Horse horses[], const int positions[]);
void resetPositions(int positions[]);

#endif 