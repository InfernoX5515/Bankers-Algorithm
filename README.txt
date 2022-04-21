This project reads from system.txt and outputs if a system is safe. system.txt holds Resources, 
Allocation Matrix, Max Matrix, and Available. Each is a list of integers separated by spaced.
Each section is labeled within the file. In Resources, list the number of instances for each
resource. In Allocation Matrix and Max Matrix, each process should have it's own line. For 
Avalable, each int of avaiable resource should be listed.


To compile/run:
g++ Banker.cpp -o Banker.out
./Banker.out


After compiled and run, the program will print if the sequence is safe or not. If it is 
safe, it will print the safe sequence.

An example of the program running with the default data is as follows:
System is safe
Safe sequence: 1 3 4 0 2 
