#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "horse.h"
#include "race.h"
#include "betting.h"
#include "sequences.h"

#define NUM_HORSES 6 
#define NUM_SIMULATIONS 1000


Horse horses[NUM_HORSES] = {   
    {"Thunderbolt", 8, 10, {"Johnny J.", 7}}, // 26
    {"Whirlwind", 8, 10, {"Mickey P.", 7}},   // 28
    {"Eclipse", 8, 10, {"Laura H.", 7}},       // 24
    {"Comet", 8, 10, {"John S.", 7}},         // 23
    {"Volcano", 8, 10, {"Hiton H.", 7}},       // 22
    {"Monsoon", 8, 10, {"Mike M.", 7}}        // 26
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
        startBetting(horses, odds, positions);  
    } else {displayResults(horses, positions);}
   
    return 0;
}
