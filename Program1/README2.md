Compilation & execution steps:
 - type in "make" to generate executable named "program2"

 - to run the program, 4 arguments are required:
    ./program2 fileX.txt fileY.txt output.txt

 - fileX.txt and fileY.txt need to be provided by the user and are in the SAME DIRECTORY as the executable
 - if output.txt doesn't exist, it will be appear in the directory after execution

Data structures and classes:
    struct timeVal:
      - predefined struct from sys/time.h
      - used to measure duration of programs through the start time, end Time, and the difference
        between the two
      - the functions that implement timeVal struct variables are defined in "timer.c"

    str1 and str2:
      - char arrays that contain the strings streamed from fileX.txt and fileY.txt

Computation time:
    This program's LCS computation method has the longest overall runtime in this assignment.
