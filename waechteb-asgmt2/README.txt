Brad Waechter
CSC 139
Assignment 2 - Scheduling

input.1 is the sample input file used to test accuracy

proj2.c is the code written in c

proj2 is the compiled code

To recompile, move to directory in Putty and type 
gcc -o proj2 proj2.c

To run, type
proj2 [inpute file name, no more than 8 characters] ["FCFS" || "SRTF" || "RR"] [Any number so long as "RR" was selected. Leave blank if another job selected]

EXAMPLES:
proj2 input.1 FCFS

proj2 input.2 SRTF

proj2 input.3 RR 7

proj2 input.1 RR 2

Note that input.2 and input.3 are not included and are only examples  