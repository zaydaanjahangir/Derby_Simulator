#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "horse.h"
#include "race.h"
#include "betting.h"
#include "sequences.h"

#define NUM_HORSES 6 
#define NUM_SIMULATIONS 1000000


Horse horses[NUM_HORSES] = {   
    {"Thunderbolt", 8, 10, {"Johnny J.", 7}, 0, 1, 0}, // 26
    {"Whirlwind", 8, 10, {"Mickey P.", 7}, -1, 0, 1},  // 28
    {"Eclipse", 8, 10, {"Laura H.", 7}, -1, -1, 1},    // 24
    {"Comet", 8, 10, {"John S.", 7}, 1, 0, -1},         // 23
    {"Volcano", 8, 10, {"Hiton H.", 7}, 0, 0, 1},       // 22
    {"Monsoon", 8, 10, {"Mike M.", 10}, 1, 1, -1}        // 26
};

int main() {
    int isBetting;
    int positions[NUM_HORSES] = {0};    
    int odds[NUM_HORSES];           
    int horseIndices[NUM_HORSES];
    for (int i = 0; i < NUM_HORSES; i++) {
        horseIndices[i] = i; 
    }

    startSequence(&isBetting);
    if(isBetting == 3){
        simulationSequence(positions, horseIndices, horses);
        return 0;
    }
    simulateRace(horses, positions, horseIndices);    
    
    if (isBetting) {        
        srand(time(NULL));  
        printf("\n");
        TrackCondition trackCondition = rand() % 3;
        calculateOdds(horses, odds, positions, trackCondition); 

        // for loop helps debug the dynamic odds calculation

        // for (int i = 0; i < NUM_HORSES; i++) {              
        //     printf("%d. %s: %d:1\n", i + 1, horses[i].name, odds[i]);
        // }
        // return 0;

        startBetting(horses, odds, positions);  
    } else {displayResults(horses, positions);}
   
    return 0;
}
