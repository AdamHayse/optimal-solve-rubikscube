# Optimally Solving the Rubik's Cube with Pattern Databases

This is the repository for source code and documents for my Artificial Intelligence project.

## License

There is no license.

## Getting Started

Start by cloning the repository and installing a C++ compiler if necessary.  Navigate to the directory where the respository is located and execute the following command:

```
$ make all
```

If you do not have make installed, you can compile separately with the following commands:

```
gcc -D TRACKED_EDGES=6 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o testscrambles6
gcc -D TRACKED_EDGES=7 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o testscrambles7
gcc -D TRACKED_EDGES=8 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o testscrambles8
gcc generateCDB.c moves.c cdatabase.c mymath.c database.c -std=c99 -O2 -o generateCDB
gcc -D HALF=1 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB1_6
gcc -D HALF=2 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB2_6
gcc -D HALF=1 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB1_7
gcc -D HALF=2 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB2_7
gcc -D HALF=1 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB1_8
gcc -D HALF=2 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB2_8
gcc -D TRACKED_EDGES=6 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o IDAstar6
gcc -D TRACKED_EDGES=7 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o IDAstar7
gcc -D TRACKED_EDGES=8 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c -std=c99 -O2 -o IDAstar8
```

Multi-threading can be used to speed up the edge database generation by defining NUM_THREADS in the compile.  For example:

```
$ gcc -D NUM_THREADS=4 -D HALF=1 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c -std=c99 -O2 -o generateEDB1_8
```

## Generating the Pattern Databases

Once everything is compiled, generate the pattern databases next.  Start with generating the corners database by running the following command:

```
$ ./generateCDB
```

The generation will appear to slow down as it finishes because unseen cases become more and more rare.  The corners database should take less than 5 minutes to generate, and it will take up about 44 MB.  Multi-threading is not available for the corners database.

Next, generate the edge databases.  I recommend starting with the 2 6 edge databases, which will take up about 21 MB each.  You can open up two separate terminals and run these commands alongside each other to save some time:

```
$ ./generateEDB1_6
$ ./generateEDB2_6
```

  The 7 and 8 edge databases take up about 255 MB and 2.55 GB each respectively.  If you want to use 8 edge databases for the fastest search, it will require about 5.3 GB of RAM.  The generation of the 8 edge databases also take up to 10 hours each depending on the speed of the computer and the number of threads used.

## Finding Scrambles and their Optimal Solutions

Once the databases have been generated, the next step is to generate scrambles.  If you don't want to generate scrambles, you can use the scrambles I already found.  The following command takes the scrambles in the 11.txt file from the scrambles directory, finds optimal solutions, and then writes the results to the file named 11_6.txt located in the results directory:

```
$ ./IDAstar6 scrambles/11.txt results/11_6.txt
```

If you want to generate your own scrambles, you can use the -g option with the IDAstar program.  This will cause the program to generate random scrambles whose optimal solutions are the same length.  For example:

```
$ ./IDAstar6 -g scrambles/11.txt 11 1000
```

This command uses the corners database and the 2 6 edge databases along with the search algorithm to look for 11 move scrambles with 11 move optimal solutions.  It will generate 1000 of these scrambles and write them to the 11.txt file in the scrambles directory to be used.  I recommend generating these scrambles with the 2 8 edge databases because the program will be able to check them faster.

I would also like to note that this strategy for generating scrambles whose solutions have the same number of moves is not feasible for finding 19 and 20 move scrambles that have 19 and 20 move solutions.  19 move scrambles have about a 3.4% chance to have a 19 move optimal solution, and 20 move scrambles have about a 1.12E-09% chance to have a 20 move solution.

## Testing Scrambles

The testscrambles program was mostly used for debugging, but it can also be used to view scrambles as well as heuristic values in an ASCII representation.  Run the following command:

```
$ ./testscrambles6
```

Once the program is running, you can type a scramble and hit Enter to see the resulting scramble as well as some additional information.  The scrambles must be upper case.  They can include parenthesis and square brackets.  The only recognized turns are U, U2, U', F, F2, F', L, L2, L', B, B2, B', R, R2, R', D, D2, D'.

## See the Benefits of a Better Heuristic

One fun experiment to try is to run IDAstar searches alongside each other.  Run these two commands in two separate terminals and watch them race each other:

```
$ ./IDAstar6 scrambles/11.txt results/11_6.txt
$ ./IDAstar7 scrambles/11.txt results/11_7.txt
```

IDAstar7 uses larger databases, so it has a better heuristic to guide its search.  The databases may take a longer time to load into memory, so IDAstar6 will start quickly.  However, once IDAstar7 starts up it will quickly overtake IDAstar6.  This demonstrates how a better heuristic can dampen the horrible time efficiency of an exponential search.
