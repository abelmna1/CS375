#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.c"


//represents an entry in the solution table
//contains an entry to correspond to the value stored in the solution table
typedef struct node{
     //numerical entry in the solution table
     int value;
} node;

//adds or updates a value in a solution table entry
//array represents the solution table, ints i and j are used as indices
//v is the value that will be stored as an entry
void addElement(node ** array, int i, int j, int v){
  array[i][j].value = v;
}

//Finds and returns the larger of two ints
//Compares the two ints and returns the larger value
//ints x and y are provided as parameters
int maxLCS(int x, int y){
   if(x > y) return x;
   else return y;
}

//recurively computes and returns the length of the LCS of two strings through memoization
//goes through every letter of each string and potentially increases the length of the return value
//if the value of an entry is -1, it is unknown if the LCS length will be increased after visiting that entry
   //therefore, the solution of the subproblem involving that entry will be solved and the numerical value
   //will be updated
//when either of the strings are entirely searched, the function exits
//if two letters aren't equal, then the maximum length of 2 different subproblems is returned
      //the 2 subproblems reduce the index of one of the strings to recursively search lower indeces
//char pointers X and Y represent the strings, ints i and j are the indeces of each string
int findLCS(char * X, char * Y, int i, int j, node ** array){
    if(i < 0 || j < 0){
        return 0;
    }
    else if(X[i] == Y[j]){
        if(array[i][j].value == -1){
            addElement(array, i+1, j+1, findLCS(X,Y,i-1,j-1, array)+1);
        }
        else return findLCS(X, Y, i-1, j-1, array)+1;
    }
    else if(X[i] != Y[j]){
        if(array[i][j].value == -1){
           addElement(array, i+1, j+1, (maxLCS(findLCS(X,Y,i,j-1, array), findLCS(X,Y,i-1,j, array))) );
        }
	      else return maxLCS(findLCS(X,Y,i,j-1, array), findLCS(X,Y,i-1,j, array));
    }
}

int main(int argc, char ** argv){
   //timeval variables used to compute the runtime of a program
   //tvStart holds the start time, tvEnd holds the end time, and tvDiff the difference between the two
    struct timeval tvDiff, tvStart, tvEnd;

    int i, j;  //used to index through the LCS table
    if(argc != 4){
    fprintf(stderr, "%s\n", "4 arguments required");
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
      fprintf(stderr, "%s", "filex not provided\n");
      exit(1);
    }
    fp2 = fopen(argv[2], "r");
    if(fp2 == NULL){
     fprintf(stderr, "%s", "filey not provided\n");
      exit(1);
    }
    if(fscanf(fp1, "%s", str1) == -1){
      fprintf(stderr, "%s\n", "contents can't be read from file");
      exit(1);
    }
    if(fscanf(fp2, "%s", str2) == -1){
      fprintf(stderr, "%s\n", "contents can't be read from file");
      exit(1);
    }
    fclose(fp1);
    fclose(fp2);

    int xLength = strlen(str1);  //length of string from fileX
    int yLength = strlen(str2);  //length of string from fileY
    int rows = xLength+1;        //number of rows in the table
    int columns = yLength+1;     //number of columns in the table

    node ** table = malloc(rows * sizeof(node*));  //multidimensional node array of size rows*columns
    if(table == NULL){
      fprintf(stderr, "%s\n", "allocation failed");
      exit(1);
    }
    for(i = 0; i < rows; i++){
       table[i] = malloc(columns * sizeof(node));  //allocating proper space for table's columns
       if(table[i] == NULL){
          fprintf(stderr, "%s\n", "allocation failed");
          exit(1);
       }
    }
    //initialize all values with -1 value and edges to 0
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            if(i == 0){
                //printf("i=%d\n", i);
                table[i][j].value = 0;
            }
            else if(i >= 1 && j == 0){
              table[i][j].value = 0;
            }
            else table[i][j].value = -1;
        }
    }
    //starts the timer
    startTimer(&tvDiff, &tvStart, &tvEnd);
    int retVal = findLCS(str1, str2, xLength-1, yLength-1, table);  //length of the LCS
    fp3 = fopen(argv[3], "w");
    fprintf(fp3, "%d\n", retVal);
    endTimer(&tvDiff, &tvStart, &tvEnd, fp3);  //ends timer and places the result in the output file

    /*for(i = 0; i < rows; i++){   **prints table ***
      for(j = 0; j < columns; j++){
        fprintf(fp3, "%d", (table[i][j]).value);
      }
      fprintf(fp3, "\n");
    }*/
    fclose(fp3);





    return 0;
}
