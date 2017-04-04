#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.c"

//Finds and returns the larger of two ints
//Compares the two ints and returns the larger value
//ints x and y are provided as parameters
int maxLCS(int x, int y){
   if(x > y) return x;
   else return y;
}

//recurively computes and returns the length of the LCS of two strings
//goes through every letter of each string and increases the length of the return value
      //if two letters are equal
//when either of the strings are entirely searched, the function exits
//if two letters aren't equal, then the maximum length of 2 different subproblems is returned
      //the 2 subproblems reduce the index of one of the strings to recursively search lower indeces
//char pointers X and Y represent the strings, ints i and j are the indeces of each string
int findLCS(char * X, char * Y, int i, int j){
    if(i < 0 || j < 0){
        return 0;
    }
    else if(X[i] == Y[j]){
        return findLCS(X, Y, i-1, j-1)+1;
    }
    else{
	      return maxLCS(findLCS(X,Y,i,j-1), findLCS(X,Y,i-1,j));
    }
}

int main(int argc, char ** argv){
    //timeval variables used to compute the runtime of a program
    //tvStart holds the start time, tvEnd holds the end time, and tvDiff the difference between the two
    struct timeval tvDiff, tvStart, tvEnd;
    int i,j;    //used to index
    if(argc != 4){
       fprintf(stderr, "%s", "4 arguments required\n");
       exit(1);
    }
    //three file variables used to access fileX.txt, fileY.txt, and output.txt, respectively
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char str1[100];  //stores string from fileX.txt
    char str2[100];  //stores string from fileY.txt
    fp1 = fopen(argv[1], "r");
    if(fp1 == NULL){
       fprintf(stderr, "%s\n", "filex not provided");
       exit(1);
    }
    fp2 = fopen(argv[2], "r");
    if(fp2 == NULL){
       fprintf(stderr, "%s\n", "filey not provided");
       exit(1);
    }
    if(fscanf(fp1, "%s", str1) == -1){
       fprintf(stderr, "%s\n", "contents can't be read from filex");
       exit(1);
    }
    if(fscanf(fp2, "%s", str2) == -1){
       fprintf(stderr, "%s\n", "contents can't be read from filey");
       exit(1);
    }
    fclose(fp1); fclose(fp2);
    int xLength = strlen(str1);  //length of string from fileX
    int yLength = strlen(str2);  //length of string from fileY
    //starts the timer
    startTimer(&tvDiff, &tvStart, &tvEnd);
    int retVal = findLCS(str1, str2, xLength-1, yLength-1);  //the length of the LCS
    fp3 = fopen(argv[3], "w");
    fprintf(fp3, "%d\n", retVal);
    //ends the timer and prints the runtime to the file
    endTimer(&tvDiff, &tvStart, &tvEnd, fp3);


    fclose(fp3);

    return 0;
}
