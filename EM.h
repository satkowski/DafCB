#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef EM_STRUCT
#define EM_STRUCT

typedef struct sequences {
    char* sequenceContent;
    short motifStart;
} sequence;

typedef struct traingingSets {
    float* backgroundProbability; // {a, c, g, t}
    float* positionalWeightMatrix; // {{A, ... L},{C, ... L} ...}
    short lenghtOfMotif; // K
    short numberOfSequences; // N
    short lenghtOfSequences; // L
    sequence* setOfSequenes; // size of N
} trainingSet;

#endif
