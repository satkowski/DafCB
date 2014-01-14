#include "EM.h"
#include "EM1.h"

void positionalWeightMatrix(trainingSet* actualSet) {
    short c1, c2;
    short* lenghtOfMotif = &(actualSet->lenghtOfMotif);
    short test = 0;
    short* start = &test;
    short* numberOfSequences = &(actualSet->numberOfSequences);
    float* backgroundProbabilitys = actualSet->backgroundProbability;
    short** backgroundFrequency = actualSet->backgroundFrequency;

    short motfiBackgroundFrequency[4] = {0, 0, 0, 0};
    double pwm[*lenghtOfMotif][4];

    // Filling of the PWM with the site specifif count.
    for(c1 = 0; c1 < *lenghtOfMotif; c1++) {
        for(c2 = 0; c2 < 4; c2++)
            pwm[c1][c2] = backgroundFrequency[c1 + *start][c2];
            motfiBackgroundFrequency[c2] += backgroundFrequency[c1 + *start][c2];
    }

    // Pseudocount calculation.
    double pseudoFI[4] = {0, 0, 0, 0};
    double pseudoF = 0;
    for(c1 = 0; c1 < *lenghtOfMotif; c1++) {
        // fi pseudo = alpha * fi
        pseudoFI[c1] = 0.0001 * motfiBackgroundFrequency[c1];
        // f pseudo = sum (fi pseudo)
        pseudoF += pseudoFI[c1];
    }
    for(c1 = 0; c1 < *lenghtOfMotif; c1++) {
        for(c2 = 0; c2 < 4; c2++)
                // pij = (fij + fi pseudo) / (N + f pseudo)
                pwm[c1][c2] = (pwm[c1][c2] + pseudoFI[c2]) / ((*numberOfSequences * actualSet->lenghtOfSequences) + pseudoF);
    }

    // PWM and PWMS calculation.
    double actualSpace;
    double pwms = 0;
    for(c1 = 0; c1 < *lenghtOfMotif; c1++) {
        for(c2 = 0; c2 < 4; c2++) {
            actualSpace = pwm[c1][c2];
            // pic = fic / N
            actualSpace /= *numberOfSequences;
            // pic / pc
            actualSpace = (double) actualSpace / (double) backgroundProbabilitys[c2];
            // log ( pic / pc)
            actualSpace = log2(actualSpace);
            pwm[c1][c2] = actualSpace;
            pwms += actualSpace;
        }
    }
    printf("%f\n\n", pwms);
}
