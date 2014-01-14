#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef EM_STRUCT
#define EM_STRUCT

typedef struct motifs {
    short start;
    double** positionalWeightMatrix; // {{A, ... L},{C, ... L} ...};
} motif;

typedef struct sequences {
    char* sequenceContent;
    motif* allMotifs;
} sequence;

typedef struct traingingSets {
    float* backgroundProbability; // {a, c, g, t}
    short* backgroundFrequency[4];
    short lenghtOfMotif; // K
    short numberOfSequences; // N
    short lenghtOfSequences; // L
    sequence* setOfSequenes; // size of N
} trainingSet;

#endif
