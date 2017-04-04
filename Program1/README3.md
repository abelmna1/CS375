Compilation & execution steps:
 - type in "make" to generate executable named "program3"

 - to run the program, 4 arguments are required:
    ./program3 fileX.txt fileY.txt output.txt

 - fileX.txt and fileY.txt need to be provided by the user and are in the SAME DIRECTORY as the executable
 - if output.txt doesn't exist, it will be appear in the directory after execution

 Data Structures and classes:
     struct node:
       - used as an entry of the LCS solution table discussed in class
       - node has one int data member: value
       - value is used to specify the current numerical value of an entry in the table

     table:
     - multidimensional struct node array used to represent a LCS solution table
     - initially empty, some of the table's entries are populated throughout the course of execution
     - After execution, one entry's value will contain the the length of the LCS

     str1 and str2:
       - char arrays that contain the strings streamed from fileX.txt and fileY.txt

     struct timeVal:
        - predefined struct from sys/time.h
        - used to measure duration of programs through the start time, end Time, and the difference
           between the two
        - the functions that implement timeVal struct variables are defined in "timer.c"

Computation time:
        The overall runtime of this program's implementation of the LCS algorithm should be faster than the
        recursive implementation (question 2). The runtime should also approximate a bottom-up implementation
        (question 1).
