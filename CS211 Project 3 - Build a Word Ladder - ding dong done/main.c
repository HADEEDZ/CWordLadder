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


//-------------------------------------------------------------------
// TODO - Task I: write the strNumMods() function, which returns the
//      count of character differences between two strings, including
//      extra characters in longer string if different lengths
// Exs: str1 = magic, str2 = magic, returns 0
//      str1 = wands, str2 = wants, returns 1
//      str1 = magic, str2 = wands, returns 4
//      str1 = magic, str2 = mag, returns 2
//      str1 = magic, str2 = magicwand, returns 4
//      str1 = magic, str2 = darkmagic, returns 8
//-------------------------------------------------------------------
int strNumMods(char* str1, char* str2) {
    int counter = 0;
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            counter++;
        }
        str1++; 
        str2++;
    }     
    

    while (*str2 != '\0') { 
        counter++;
        str2++; 
    }

    while (*str1 != '\0') {  
        counter++;
        str1++; 
    }
    return counter; 
}

//-------------------------------------------------------------------
// TODO - Task II: write the strDiffInd() function, which returns the
//      index of the character where the two strings first differ;
//      returns strlen(str1) = strlen(str2) if no differences
// Exs: str1 = magic, str2 = magic, returns 5
//      str1 = wands, str2 = wants, returns 3
//      str1 = magic, str2 = wands, returns 0
//      str1 = magic, str2 = mag, returns 3
//      str1 = magic, str2 = magicwand, returns 5
//      str1 = magic, str2 = darkmagic, returns 0
//-------------------------------------------------------------------
int strDiffInd(char* str1, char* str2) {
    int sameCharCounter = 0;
    while (*str1 != '\0' && *str2 != '\0') {

        if (*str1 == *str2) { 
            str1++;
            str2++;
            sameCharCounter++;
        }

        if (*str1 != *str2) {
            break;
        }
    }
    return sameCharCounter;
}

//-------------------------------------------------------------------
// TODO - Task III: write addWord() function, which adds a new word to
//      a dynamic heap-allocated array of C-strings; heap-space must  
//      be allocated for the new word inside this function, then copy  
//      the chars from [newWord] to the newly allocated heap-space;
//      if adding the new word pushes numWords above [maxWords], then 
//      realloate the [words] array with double the capacity
//      parameter: 
//          char*** words - array of C-strings passed-by-pointer
//              note: *words is an array of pointers
//                    **words is an array of chars
//                    ***words is a char  
//                    (*words)[0] is the 1st C-string in the array
//                    (*words)[1] is the 2nd C-string in the array
//                    (*words)[0][0] is 1st char of 1st C-string
//                    (*words)[1][2] is 3rd char of 2nd C-string
//                    etc.
//          [numWords] - current # of words in [words] array
//               note: [numWords] will increase by 1 here, 
//                     so it is passed-by-pointer
//          [maxWords] - current capacity of *words array
//               note: [maxWords] may increase by x2 here, 
//                     so it is passed-by-pointer
//          [newWord] - C-string word to be added to [words]
//               note: [newWord] is a C-string, naturally a pointer
//-------------------------------------------------------------------
void addWord(char*** words, int* numWords, int* maxWords, char* newWord) {

    if (*numWords + 1 > *maxWords) {

        *maxWords = *maxWords * 2;
        char** tempArrayOfWords = (char**)malloc(sizeof(char*) * (*maxWords));

        for (int i = 0; i < *numWords; i++) { 
            tempArrayOfWords[i] = (*words)[i];
        }

        free(*words);
        *words = tempArrayOfWords;
    }
 
    (*words)[*numWords] = (char*)malloc(sizeof(char) * (strlen(newWord+1)));
    strcpy((*words)[*numWords], newWord);

    
    (*numWords)++; 
}


//-------------------------------------------------------------------
// TODO - Task V: write the findWord() function, which returns the
//      index in the [words] C-string array where a match to the 
//      C-string [aWord] is found, using a linear search; 
//      return -1 if no match to [aWord] is found in [words] array;
//      note: [words] is an array of pointers to [numWords] C-strings 
//-------------------------------------------------------------------
int findWord(char** words, int numWords, char* aWord) { // TODO

    for (int i = 0; i < numWords; i++) {
        if (strcmp(words[i], aWord) == 0) {
            return i;
        }
    }

    return -1; 
}

//-------------------------------------------------------------------
// TODO - Task VI: write the validWordCheck() function, which checks 
//      if [aWord] is valid for the next word in the word ladder;
//
//      return FALSE for the following cases:
//        - [aWord] is invalid because it is not in the words array,  
//              i.e. either not in dictionary OR wrong word length;
//              before returning FALSE, first print: 
//                  "Entered word NOT in dictionary. Try again..."
//        - [aWord] is invalid because it is NOT a single-char 
//              difference from the previous word in the ladder; 
//              e.g. previous word is "code" and [aWord] is "cave";
//              e.g. previous word is "code" and [aWord] is "code";
//              before returning FALSE, first print: 
//                  "Entered word is NOT a one-character change from the previous word. Try again..."
//
//      return TRUE for the following cases:
//        - [aWord] is "DONE" beacuse the user wants to stop;
//              before returning TRUE, first print: 
//                  "Stopping with an incomplete word ladder..."
//        - [aWord] is valid and will be added to the word ladder
//              before returning TRUE, first print: 
//                  "Entered word is valid and will be added to the word ladder."
//
//      [words] is an array of [numWords] C-strings that contains all 
//              words in the dictionary of the correct word length
//      [ladder] is an array of [ladderHeight] C-strings that 
//              represents an incomplete word ladder
//      [aWord] is a C-string that must be checked for validity here
//
//  HINT: call findWord(), strNumMods(), & string.h function(s)
//-------------------------------------------------------------------
bool validWordCheck(char** words, int numWords, char** ladder, int ladderHeight, char* aWord) { 
    for (int i = 0; i < numWords; i++) {

        if ((findWord(words, numWords, aWord) == -1) ||
            !(strlen(aWord) > 2 && strlen(aWord) < 20)) {
            printf("Entered word NOT in dictionary. Try again...\n");
            return false;
        }


            if ((strNumMods(words[i], aWord) == 0) || (strNumMods(words[i], aWord) > 1)) { 
                printf("Entered word is NOT a one-character change from ");
                printf("the previous word. Try again...\n");
                return false;
            }
        }
    return true; 
}

//-------------------------------------------------------------------
// TODO - Task VII: write the ladderComplete() Boolean function, 
//      which should simply check for a completed word ladder, i.e.
//      return true if the final word in [ladderWords] is a match to 
//      [finalWord]; otherwise, return false; the number of words in
//      the word ladder is [n]
//-------------------------------------------------------------------
bool ladderComplete(char** ladderWords, int n, char* finalWord) {
    if (strcmp(ladderWords[n-1], finalWord) == 0) { 
        return true;
    }
    return false;
}

//-------------------------------------------------------------------
// TODO - Task IX: write the displayIncompleteLadder() function, 
//      which should display the [n] C-strings in the [ladderWords] 
//      array with the first word at the bottom of the ladder, and 
//      each successive C-string one rung higher on the ladder. To 
//      signify the ladder as incomplete, display three lines of  
//      "..." at the top of the ladder. The ladder must be displayed 
//      with an indentation of two whitespaces on every line;
//      Ex: if the start word is "data" and final word is "code" and
//          the incomplete ladder is data->date->gate->gave, then the
//          output display should be as follows (where the quotation  
//          marks are NOT a part of the actual display):
//              "  ..."
//              "  ..."
//              "  ..."
//              "  gave"
//              "  gate"
//              "  date"
//              "  data" 
//-------------------------------------------------------------------
void displayIncompleteLadder(char** ladderWords, int n) {

}

//-------------------------------------------------------------------
// TODO - Task X: write the displayCompleteLadder() function, 
//      which should display the C-strings in the [ladderWords] array 
//      with the first word at the bottom of the ladder, and each 
//      successive C-string one rung higher on the ladder. In between
//      each ladder rung, display the symbol '^' to signify the 
//      character that changes between the two rungs of the ladder. 
//      The ladder should be displayed with an indentation of two 
//      whitespaces to the left of every word;
//      Ex: if the start word is "data" and final word is "code" 
//          then the output display for a complete ladder should be  
//          as follows (where the quotation marks are NOT a part of  
//          the actual display):
//              "  code"
//              "    ^ "
//              "  cove"
//              "   ^  "
//              "  cave"
//              "  ^   "
//              "  gave"
//              "    ^ "
//              "  gate"
//              "  ^   "
//              "  date"
//              "     ^"
//              "  data" 
//-------------------------------------------------------------------
void displayCompleteLadder(char** ladderWords, int n) {

}

int main(int argc, char* argv[]) {
    
    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 

    //-------------------------------------------------------------------
    // TODO - Task XII: handle command-line arguments
    // command-line arguments:
    //  [-n wordLen] = sets word length for word ladder;
    //                 if [wordLen] is not a valid input 
    //                 (cannot be less than 2 or greater than 20),
    //                 or missing from command-line arguments, 
    //                 then let user set it using interactive user input
    // [-m maxLadder] = sets maximum word ladder height;
    //                  [maxLadder] must be at least 2;
    //                  if [maxLadder] is invalid or missing from 
    //                  command-line arguments, then let user set it 
    //                  using interactive user input
    // [-d dictFile] = sets dictionary file;
    //                 if [dictFile] is invalid (file not found) or 
    //                 missing from command-line arguments, then let
    //                 user set it using interactive user input
    // [-s startWord] = sets the starting word;
    //                  if [startWord] is invalid 
    //                  (not in dictionary or incorrect length) or 
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-f finalWord] = sets the final word;
    //                  if [finalWord] is invalid  
    //                  (not in dictionary or incorrect length) or 
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    //-------------------------------------------------------------------


    printf("Interactively (re)setting invalid parameters:\n");

    while (wordLen < 2 || wordLen > 20) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        scanf("%d",&wordLen);
        printf("\n");
    }

    if (maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        scanf("%d",&maxLadder);
        printf("\n");
    }
    

    FILE* fileTry = fopen(dict,"r");
    while (fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    


    int numWords = 0;
    int maxWords = 4;
    char newWord[100];
    char** words = (char**)malloc(maxWords*sizeof(char*));
    
    //-------------------------------------------------------------------
    // TODO - Task IV: file-read the word list from the dictionary file 
    //                 [dict], storing only words of length set by 
    //                 [wordLen] in [words], which is a dynamically 
    //                 growing heap-allocated array of C-strings:
    //                      - the word list should be a dynamic array of 
    //                        pointers, initially with capacity (i.e. 
    //                        maximum size) 4; the capacity doubles 
    //                        whenever more space is needed
    //                      - each element of the word list array should 
    //                        point to a heap-allocated C-string that 
    //                        can store a word containing exactly 
    //                        [wordLen] lower-case letters; don't forget
    //                        that there must be a single char at the 
    //                        end of the C-string for the null character
    //
    //                 HINT: open the file; loop to read words from the
    //                 file and check if the word has the correct length;
    //                 if so, add the word to the array using a call to 
    //                 addWord(); lastly, close the file after all words 
    //                 have been scanned
    //-------------------------------------------------------------------
    FILE* newFile = fopen(dict,"r");
    while (!feof(newFile)) { 
        fscanf(newFile, "%s", newWord); 

        if (strlen(newWord) == wordLen) {

            newWord[strlen(newWord)] = '\0'; 
            addWord(&words, &numWords, &maxWords, newWord);
        }
    } 
    fclose(newFile);

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    while (findWord(words,numWords,startWord) == -1) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        scanf("%s", startWord);
        printf("\n");
    }

    while (findWord(words,numWords,finalWord) == -1) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        scanf("%s", finalWord);
        printf("\n");
    }


    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; 
    
    addWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");


    //-------------------------------------------------------------------
    // TODO - Task VIII: modify the while loop condition such that the 
    //          word ladder building process continues only if ALL of  
    //          the following conditions are met:
    //              1. the ladder still has at least one available rung
    //                 before reaching the maximum allowed height
    //              2. the user is NOT attempting to stop the word ladder
    //                 building process, which occurs if the entered word 
    //                 [aWord] from the last iteration is "DONE"
    //              3. the ladder is still incomplete; i.e. the last word
    //                 added to ladder is not the final word; 
    //                 note: this should user a call to ladderComplete() 
    //-------------------------------------------------------------------
    while ((ladderComplete(ladder, ladderHeight, finalWord) == false
           && (ladderHeight < (maxLadder - 1) && strcmp(aWord, "DONE") != 0))) { 
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        while (!validWordCheck(words, numWords, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        if (strcmp(aWord,"DONE") != 0) {
            addWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");

    }
    
    if (ladderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
    


    return 0;
}