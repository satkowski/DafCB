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
    short backgroundProbability[4]; // {a, c, g, t}
    short lenghtOfMotif; // K
    short numberOfSequences; // N
    short lenghtOfSequences; // L
    sequence* setOfSequenes;
} trainingSet;

#endif
