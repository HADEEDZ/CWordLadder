/*-------------------------------------------
Program 3: Build a Word Ladder - ding dong done
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Hadeed
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//------------------------------------------------------------
// Task I: Count the number of character differences between 
// two strings (including extra characters in the longer string)
//------------------------------------------------------------
int diffCount(const char *firstStr, const char *secondStr) {
    int diff = 0;
    while (*firstStr != '\0' && *secondStr != '\0') {
        if (*firstStr != *secondStr) {
            diff++;
        }
        firstStr++;
        secondStr++;
    }
    while (*secondStr != '\0') {
        diff++;
        secondStr++;
    }
    while (*firstStr != '\0') {
        diff++;
        firstStr++;
    }
    return diff;
}

//------------------------------------------------------------
// Task II: Return the index of the first difference between 
// two strings. If none, then the index equals the string length.
//------------------------------------------------------------
int firstMismatchIndex(const char *firstStr, const char *secondStr) {
    int index = 0;
    while (*firstStr != '\0' && *secondStr != '\0') {
        if (*firstStr == *secondStr) {
            index++;
            firstStr++;
            secondStr++;
        } else {
            break;
        }
    }
    return index;
}

//------------------------------------------------------------
// Task III: Append a new word to a dynamically growing array 
// of strings. If the array is full, double its capacity.
//------------------------------------------------------------
void appendWord(char ***wordArray, int *wordCount, int *capacity, const char *newToken) {
    if (*wordCount + 1 > *capacity) {
        *capacity *= 2;
        char **tempArray = (char **)malloc(sizeof(char *) * (*capacity));
        for (int j = 0; j < *wordCount; j++) {
            tempArray[j] = (*wordArray)[j];
        }
        free(*wordArray);
        *wordArray = tempArray;
    }
    (*wordArray)[*wordCount] = (char *)malloc(sizeof(char) * (strlen(newToken) + 1));
    strcpy((*wordArray)[*wordCount], newToken);
    (*wordCount)++;
}

//------------------------------------------------------------
// Task V: Search for a word in the dictionary array and return
// its index. Return -1 if the word is not found.
//------------------------------------------------------------
int searchDictionary(char **dictArray, int dictSize, const char *targetWord) {
    for (int i = 0; i < dictSize; i++) {
        if (strcmp(dictArray[i], targetWord) == 0) {
            return i;
        }
    }
    return -1;
}

//------------------------------------------------------------
// Task VI: Check whether the entered word is valid for the 
// word ladder. It must be in the dictionary, have a proper length, 
// and differ by exactly one character from the previous word.
//------------------------------------------------------------
bool isValidWord(char **dictArray, int dictSize, char **ladderChain, int chainLength, const char *candidate) {
    if (searchDictionary(dictArray, dictSize, candidate) == -1 ||
        !(strlen(candidate) > 2 && strlen(candidate) < 20)) {
        printf("Entered word NOT in dictionary. Try again...\n");
        return false;
    }
    // Check if the candidate word is a one-character change from the previous word
    for (int i = 0; i < dictSize; i++) {
        if (diffCount(dictArray[i], candidate) == 0 || diffCount(dictArray[i], candidate) > 1) {
            printf("Entered word is NOT a one-character change from ");
            printf("the previous word. Try again...\n");
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------
// Task VII: Determine if the word ladder is complete by 
// comparing the last word in the ladder with the final word.
//------------------------------------------------------------
bool isLadderComplete(char **ladderChain, int chainLength, const char *finalToken) {
    if (strcmp(ladderChain[chainLength - 1], finalToken) == 0) {
        return true;
    }
    return false;
}

//------------------------------------------------------------
// Task IX: Display the incomplete ladder (with three "..." lines
// at the top) from the last word (at the bottom) to the first.
//------------------------------------------------------------
void printIncompleteLadder(char **ladderChain, int chainLength) {
    for (int i = 0; i < 3; i++) {
        printf("  ...\n");
    }
    for (int i = chainLength - 1; i >= 0; i--) {
        printf("  %s\n", ladderChain[i]);
    }
}

//------------------------------------------------------------
// Task X: Display the complete ladder with a caret (^) 
// between successive words to indicate the change.
//------------------------------------------------------------
void printCompleteLadder(char **ladderChain, int chainLength) {
    for (int i = chainLength - 1; i >= 0; i--) {
        printf("  %s\n", ladderChain[i]);
        if (i > 0) {
            printf("    ^\n");
        }
    }
}

int main(int argc, char *argv[]) {
    printf("\nProcessing command-line arguments...\n");

    int desiredWordLen = 0;
    int maxChainHeight = 1;
    char dictionaryFile[100] = "notAfile";
    char initialWord[30] = "notAword";
    char targetWord[30] = "notValid";

    printf("Interactively (re)setting invalid parameters:\n");

    while (desiredWordLen < 2 || desiredWordLen > 20) {
        printf("Invalid word length = %d\n", desiredWordLen);
        printf("Enter a valid word length (must be 2-20): ");
        scanf("%d", &desiredWordLen);
        printf("\n");
    }

    if (maxChainHeight < 2) {
        printf("Invalid max ladder height = %d\n", maxChainHeight);
        printf("Enter a valid max ladder height (must be >1): ");
        scanf("%d", &maxChainHeight);
        printf("\n");
    }

    FILE *fpDict = fopen(dictionaryFile, "r");
    while (fpDict == NULL) {
        printf("Dictionary file %s not found...\n", dictionaryFile);
        printf("Enter filename for dictionary: ");
        scanf("%s", dictionaryFile);
        printf("\n");
        fpDict = fopen(dictionaryFile, "r");
    }
    fclose(fpDict);

    int totalDictWords = 0;
    int currentCapacity = 4;
    char tempBuffer[100];
    char **dictWords = (char **)malloc(currentCapacity * sizeof(char *));

    // Read the dictionary file and only store words with the correct length
    FILE *dictStream = fopen(dictionaryFile, "r");
    while (!feof(dictStream)) {
        fscanf(dictStream, "%s", tempBuffer);
        if (strlen(tempBuffer) == desiredWordLen) {
            tempBuffer[strlen(tempBuffer)] = '\0';
            appendWord(&dictWords, &totalDictWords, &currentCapacity, tempBuffer);
        }
    }
    fclose(dictStream);

    printf("The dictionary contains %d words of length %d.\n", totalDictWords, desiredWordLen);
    printf("Max size of the dynamic words array is %d.\n\n", currentCapacity);

    if (totalDictWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n", dictionaryFile, desiredWordLen);
        printf("Terminating program...\n");
        return -1;
    }

    while (searchDictionary(dictWords, totalDictWords, initialWord) == -1) {
        printf("Start word %s is not valid...\n", initialWord);
        printf("Enter a valid start word: ");
        scanf("%s", initialWord);
        printf("\n");
    }

    while (searchDictionary(dictWords, totalDictWords, targetWord) == -1) {
        printf("Final word %s is not valid...\n", targetWord);
        printf("Enter a valid final word: ");
        scanf("%s", targetWord);
        printf("\n");
    }

    printf("\nWelcome to the CS 211 Word Ladder Builder!\n\n");
    printf("Your goal is to make a word ladder between two %d-letter words:\n  %s -> %s\n\n", desiredWordLen, initialWord, targetWord);

    char **wordChain = (char **)malloc(maxChainHeight * sizeof(char *));
    int chainLength = 0;

    appendWord(&wordChain, &chainLength, &maxChainHeight, initialWord);

    char nextWord[30] = "XYZ";
    printf("\n");

    // Loop until the ladder is complete, the user enters "DONE", or the maximum ladder height is reached.
    while ((!isLadderComplete(wordChain, chainLength, targetWord)) &&
           (chainLength < (maxChainHeight - 1) && strcmp(nextWord, "DONE") != 0)) {
        printf("The goal is to reach the final word: %s\n", targetWord);
        printf("The ladder is currently: \n");
        printIncompleteLadder(wordChain, chainLength);
        printf("Current ladder height: %d\n", chainLength);
        printf("Maximum ladder height: %d\n", maxChainHeight);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s", nextWord);
        printf("\n");

        while (!isValidWord(dictWords, totalDictWords, wordChain, chainLength, nextWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s", nextWord);
            printf("\n");
        }

        if (strcmp(nextWord, "DONE") != 0) {
            appendWord(&wordChain, &chainLength, &maxChainHeight, nextWord);
        }
        printf("\n");
    }

    if (isLadderComplete(wordChain, chainLength, targetWord)) {
        printf("Word Ladder complete!\n");
        printCompleteLadder(wordChain, chainLength);
        printf("Word Ladder height = %d.\n", chainLength);
        printf("Can you find a shorter Word Ladder next time???\n");
    } else {
        if (chainLength == maxChainHeight)
            printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        printIncompleteLadder(wordChain, chainLength);
        printf("Word Ladder height = %d.\n", chainLength);
        printf("Can you complete the Word Ladder next time???\n");
    }

    return 0;
}
