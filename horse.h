#ifndef HORSE_H
#define HORSE_H

typedef struct {
    char name[15];
    int skill; 
} Jockey;


typedef struct {
    char name[15];  
    int speed;
    int stamina;
    Jockey jockey; 
    int trackBias[3]; 
} Horse;

#endif
