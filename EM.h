#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef EM_STRUCT
#define EM_STRUCT

typedef struct sequences {
    char* sequenceContent;
    short* numberOfLetter; // {a, c, g, t}
    short motifStart;
} sequence;

typedef struct traingingSets {
    float* backgroundProbability; // {a, c, g, t}
    short lenghtOfMotif; // K
    short numberOfSequences; // N
    short lenghtOfSequences; // L
    sequence* setOfSequenes;
} trainingSet;

#endif
