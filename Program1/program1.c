#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.c"

//represents the possible directions pointed by an arrow in a LCS solution table entry
enum Direction{
     UP, LEFT, DIAGONAL, NONE
};

//represents an entry in the solution table
typedef struct node{
     int value;   //contains an entry to correspond to the value stored in the solution table
     enum Direction direct;  //direction pointed by arrow in entry
} node;


//finds and prints the LCS to a FILE
//recursively travels through the solution table starting at the bottom right entry
//if an entry's direction is diagonal, prints the char shared by both strings
   //this char corresponds to the table entry pointed by a diagonal arrow
//if an entry's direction is upward, visit the entry directly above, but don't print to file
//otherwise, visit the entry to the left, but don't print to file
//array represents the multidimensional LCS solution table, str represents the string from
  //fileX.txt, ints i and j are used to index through the solution table, and fp represents output.txt
void printLCS(node ** array, char * str, int i, int j, FILE * fp){
    if(i == 0 || j == 0){
       return;
    }
    if(array[i][j].direct == DIAGONAL){
       printLCS(array, str, i-1, j-1, fp);
       fprintf(fp, "%c", str[i-1]);
    }
    else if(array[i][j].direct == UP){
       printLCS(array, str, i-1, j, fp);
    }
    else{
       printLCS(array, str, i, j-1, fp);
    }
}



int main(int argc, char ** argv){
  //timeval variables used to compute the runtime of a program
  //tvStart holds the start time, tvEnd holds the end time, and tvDiff the difference between the two
    struct timeval tvDiff, tvStart, tvEnd;
    int i, j;  //used to index through the LCS solution table
    if(argc != 4){
   	fprintf(stderr, "%s\n", "4 arguments required");
        exit(1);
    }
    //three file variables used to access fileX.txt, fileY.txt, and output.txt, respectively
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char str1[100];   //stores string from fileX.txt
    char str2[100];   //stores string from fileY.txt
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

    int xLength = strlen(str1);   //length of string from fileX
    int yLength = strlen(str2);   //length of string from fileY
    int rows = xLength+1;         //the number of rows in the table
    int columns = yLength+1;      //the number of columns in the table

    //multidimensional node array of size rows*columns
    node ** table = malloc(rows * sizeof(node*));
    if(table == NULL){
      fprintf(stderr, "%s\n", "allocation failed");
      exit(1);
    }
    for(i = 0; i < rows; i++){
       table[i] = malloc(columns * sizeof(node));
       if(table[i] == NULL){
          fprintf(stderr, "%s\n", "allocation failed");
          exit(1);
       }
    }

    startTimer(&tvDiff, &tvStart, &tvEnd);  //start timer
    for(i = 1; i < rows; i++){  //initialize all edge entries with no direction and value of 0
       table[i][0].value = 0;
       table[i][0].direct = NONE;
    }
    for(i = 0; i < columns; i++){
       table[0][i].value = 0;
       table[0][i].direct = NONE;
    }
    for(i = 1; i < rows; i++){
       for(j = 1; j < columns; j++){
           if(str1[i-1] == str2[j-1]){  //if two chars are the same, update value and set direction to diagonal
              table[i][j].value = ((table[i-1][j-1]).value)+1;
              table[i][j].direct = DIAGONAL;
           }
           else if((table[i-1][j]).value >= (table[i][j-1]).value){
              //if the value at above entry is greater than value of entry to the left,
                //store value from above entry and make the arrow point upward
              table[i][j] = table[i-1][j];
              table[i][j].direct = UP;
           }
           else{
             //otherwise, store value from entry to the left and make arrow point in that direction
              table[i][j] = table[i][j-1];
              table[i][j].direct = LEFT;
           }
       }
    }

    fp3 = fopen(argv[3], "w");
    //if both strings are smaller than 10 characters, store the LCS solution table, the LCS, and algorithm's
      // runtime in output.txt
    if(xLength < 10 && yLength < 10){
        for(i = 0; i < rows; i++){
          for(j = 0; j < columns; j++){
            fprintf(fp3, "%d", (table[i][j]).value);
          }
          fprintf(fp3, "\n");
        }
        printLCS(table, str1, rows-1, columns-1, fp3);
        fprintf(fp3, "\n");
        endTimer(&tvDiff, &tvStart, &tvEnd, fp3);
    }
    //otherwise, store the length of the LCS and the algorithm's runtime
    else if(xLength > 10 || yLength > 10){
        fprintf(fp3, "%d\n", (table[rows-1][columns-1]).value);
        endTimer(&tvDiff, &tvStart, &tvEnd, fp3);
    }
    fclose(fp3);


    return 0;
}
