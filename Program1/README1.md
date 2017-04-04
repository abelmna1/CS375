Compilation & execution steps:
 - type in "make" to generate executable named "program1"

 - to run the program, 4 arguments are required:
    ./program1 fileX.txt fileY.txt output.txt

 - fileX.txt and fileY.txt need to be provided by the user and are in the SAME DIRECTORY as the executable
 - if output.txt doesn't exist, it will be appear in the directory after execution

Data Structures and classes:
    struct node:
      - used as an entry of the LCS solution table discussed in class
      - node has value (int) and direction (enum) data members
      - value is used to specify the current numerical value of entry in the table
      - direction is used to specify the direction of the arrow of an entry in the table

    table:
      - multidimensional struct node array used to represent the LCS solution table
      - initially empty, the table is populated throughout the course of execution
      - After execution, the value at each entry is printed to output.txt if string
        sizes are less than 10
      - The value in the bottom right corner of the table will be the length of the LCS

    struct timeVal:
      - predefined struct from sys/time.h
      - used to measure duration of programs through the start time, end Time, and the difference
        between the two
      - the functions that implement timeVal struct variables are defined in "timer.c"

    str1 and str2:
      - char arrays that contain the strings streamed from fileX.txt and fileY.txt

Computation time:
    The overall runtime of this program's implementation of the LCS algorithm should be faster than the
    recursive implementation(question 2). The runtime should also approximate a memoized implementation
    (question 3).
