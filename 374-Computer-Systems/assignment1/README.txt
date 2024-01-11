C programming (20 Points):
These two files need a main() to run their functions insertionSort() and mergeSortWrapper(). 
Then all three C files need a header file to inform them of what the others have that they need, including Node.h which defines the data-structure. 
Please finish both the main.c and headers.h

Please make print() print the whole linked list.
For headers.h, not everything needs to be shared.
    main() needs insertionSort() and mergeSortWrapper()
    Both insertionSort() and mergeSortWrapper() need print().
Otherwise, it is best not to share too much, kind of like keeping methods and members private in C++ and Java.


Timing: Part 1 (20 Points):
Compile and run the program without any extra optimizations, but with profiling for timing:
    gcc -c -pg -O0 main.c
    gcc -c -pg -O0 mergeSort.c
    gcc -c -pg -O0 insertionSort.c
    gcc main.o mergeSort.o insertionSort.o -pg -O0 -o assign1-0
Run the program twice timing it both times, and answer the following:
    How many self seconds did insertionSort() take?
    How many self seconds did mergeSort() take?


Timing: Part 2 (20 Points):
Compile and run the program with optimization, but with profiling for timing:
    gcc -c -pg -O2 main.c
    gcc -c -pg -O2 mergeSort.c
    gcc -c -pg -O2 insertionSort.c
    gcc main.o mergeSort.o insertionSort.o -pg -O2 -o assign1-2
Run the program twice timing it both times, and answer the following:
    How many self seconds did insertionSort() take?
    How many self seconds did mergeSort() take?


Human vs. Compiler Optimization (10 Points):
Which is faster:
    A bad algorithm and data-structure optimized with -O2
    A good algorithm and data-structure optimized with -O0


Parts of an executable (Points 20):
Please find the following inside of assign1-0 by using objdump.
If it can be found then both
    a. Give the objdump command, and
    b. Show the objdump result
If it cannot be found then tell why not. Where in the memory of the runtime process is it?
Look for:
    a. Global integer numNumbers in main.c
    b. The string constant in main()
    c. The code for print()
    d. The int variable choice in main()


Compiler optimizations (Points 10):
Look at the assembly code of assign1-0 and assign1-2. Find and show at least 2 optimizations that the compiler did in either assign1-2 or assign1-0.