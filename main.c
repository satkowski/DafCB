#include "EM.h"

int main(void) {
    short returnValue;
    short c1, c2;

    char fileName[32];
    char inputString[38] = "Input/";

    trainingSet actualSet;
    short lenghtOfMotif; // K
    short numberOfSequences; // N
    short lenghtOfSequences; // L
    float backgroundProbabilitys[4];
    short backgroundSum = 0;
    short backgroundSums[4] = {0, 0, 0, 0}; //{a, c, g, t}

    // Creates the inputString for the files in the .../Input/ Directory.
    printf("What is the name of the input file?\n");
    fgets(fileName, 32, stdin);
    for(c1 = 0; c1 < 32; c1++) {
        if(fileName[c1] == '\n')
            break;
        inputString[c1 + 6] = fileName[c1];
    }

    // Creates a new FILE and its stream.
    FILE *input;
    input = fopen(inputString, "r");
    if(input == NULL) {
       printf("There is no such file!\n\n");
       exit(1);
    }

    // Reading of the File.
    // Here: Reads the first line with its values.
    returnValue = fscanf(input, "K=%hd N=%hd L=%hd\n", &lenghtOfMotif, &numberOfSequences, &lenghtOfSequences);
    if(returnValue <= 0) {
        printf("There are no value at the beginning of the file!\n\n");
        exit(1);
    }

    char lastChar;
    sequence actualSequences[numberOfSequences];
    char actualSequenceStrings[lenghtOfSequences];

    for(c1 = 0; c1 < numberOfSequences; c1++) {
        for(c2 = 0; c2 < lenghtOfSequences - 1; c2++) {
            returnValue = fscanf(input, "%c", &actualSequenceStrings[c2]);
            if(returnValue <= 0) {
                printf("There are to less Sequences in you file, only %hd!\n\n", c1);
                exit(1);
            }
            if(actualSequenceStrings[c2] == '\n') {
                printf("The sequence %hd is too short!\n\n", c1 + 1);
                exit(1);
            }
            switch(actualSequenceStrings[c2]) {
                case 'A':
                case 'a':   backgroundSums[0]++;
                            break;
                case 'C':
                case 'c':   backgroundSums[1]++;
                            break;
                case 'G':
                case 'g':   backgroundSums[2]++;
                            break;
                case 'T':
                case 't':   backgroundSums[3]++;
                            break;
                default:    printf("There are false letters in your %hd Sequence, column %hd!\n\n", c1 + 1, c2 + 1);
                            break;
            }
        }
        fscanf(input, "%c", &lastChar);
        if(lastChar != '\n') {
            printf("The sequence %hd is too long!\n\n", c1 + 1);
            exit(1);
        }
        actualSequences[c1].sequenceContent = actualSequenceStrings;
        actualSequences[c1].motifStart = -1;
    }
    for(c1 = 0; c1 < 4; c1++)
        backgroundSum += backgroundSums[c1];
    for(c1 = 0; c1 < 4; c1++)
        backgroundProbabilitys[c1] = backgroundSums[c1] / backgroundSum;


    actualSet.lenghtOfMotif = lenghtOfMotif;
    actualSet.lenghtOfSequences = lenghtOfSequences;
    actualSet.numberOfSequences = numberOfSequences;
    actualSet.setOfSequenes = actualSequences;
    actualSet.backgroundProbability = backgroundProbabilitys;

    return 0;
}
