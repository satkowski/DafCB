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
    short backgroundProbability[4];
    short backgroundSum[4] = {0, 0, 0, 0} //{a, c, g, t}

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
    sequence actualSequence[numberOfSequences];
    char actualSequenceString[lenghtOfSequences];

    for(c1 = 0; c1 < numberOfSequences; c1++) {
        for(c2 = 0; c2 < lenghtOfSequences - 1; c2++) {
            returnValue = fscanf(input, "%c", &actualSequenceString[c2]);
            if(returnValue <= 0) {
                printf("There are to less Sequences in you file, only %hd!\n\n", c1);
                exit(1);
            }
            if(actualSequenceString[c2] == '\n') {
                printf("The sequence %hd is too short!\n\n", c1 + 1);
                exit(1);
            }
            switch(actualSequenceString[c2]) {
                case 'a':   backgroundSum[0]++;
                            break;
                case 'c':   backgroundSum[1]++;
                            break;
                case 'g':   backgroundSum[2]++;
                            break;
                case 't':   backgroundSum[3]++;
                            break;
            }
        }
        fscanf(input, "%c", &lastChar);
        if(lastChar != '\n') {
            printf("The sequence %hd is too long!\n\n", c1 + 1);
            exit(1);
        }
        actualSequence[c1].sequenceContent = actualSequenceString;
        actualSequence[c1].motifStart = -1;
    }

    actualSet.lenghtOfMotif = lenghtOfMotif;
    actualSet.lenghtOfSequences = lenghtOfSequences;
    actualSet.numberOfSequences = numberOfSequences;
    actualSet.setOfSequenes = actualSequence;

    return 0;
}
