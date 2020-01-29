# Chapter 14

## Question 1
#### First, write a simple program called `null.c` that creates a pointer to an integer, sets it to `NULL`, and then tries to dereference it. Compile this into an executable called `null`. What happens when you run this program?

Steps:
 ```shell
 $ gcc main.c -o main
 $ ./main
 ```

Result:
```shell
[1]    2477 segmentation fault (core dumped)  ./main
```

## Question 2
#### Next, compile this program with symbol information included (with the `-g` flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing `gdb null` and then, once `gdb` is running, typing `run`. What does gdb show you?

Steps:
 ```shell
 $ gcc main.c -o main -g
 $ gdb main
 (gdb) run
 ```

Result:
```shell
Starting program: /home/doris/c/OSTEP-homework/Chapter14/Question1-3/main 

Program received signal SIGSEGV, Segmentation fault.
0x000000000800069e in main () at main.c:6
6           printf("%d\n", *p);
```

## Question 3
#### Finally, use the `valgrind` tool on this program. We’ll use the `memcheck` tool that is a part of `valgrind` to analyze what happens.  Run this by typing in the following: `valgrind --leak-check=yes null`. What happens when you run this? Can you interpret the output from the tool?

Steps:
 ```shell
 $ valgrind --leak-check=yes ./main
 ```

Result:
```shell
==2731== Memcheck, a memory error detector
==2731== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2731== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==2731== Command: ./main
==2731== 
==2731== error calling PR_SET_PTRACER, vgdb might block
==2731== Invalid read of size 4
==2731==    at 0x10869E: main (main.c:6)
==2731==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==2731== 
==2731== 
==2731== Process terminating with default action of signal 11 (SIGSEGV)
==2731==  Access not within mapped region at address 0x0
==2731==    at 0x10869E: main (main.c:6)
==2731==  If you believe this happened as a result of a stack
==2731==  overflow in your program's main thread (unlikely but
==2731==  possible), you can try to increase the size of the
==2731==  main thread stack using the --main-stacksize= flag.
==2731==  The main thread stack size used in this run was 8388608.
==2731== 
==2731== HEAP SUMMARY:
==2731==     in use at exit: 0 bytes in 0 blocks
==2731==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==2731== 
==2731== All heap blocks were freed -- no leaks are possible
==2731== 
==2731== For counts of detected and suppressed errors, rerun with: -v
==2731== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
[1]    2731 segmentation fault (core dumped)  valgrind --leak-check=yes ./main
```
This means that the address haven't been assigned. ([website](https://stackoverflow.com/questions/23791398/is-not-stackd-mallocd-or-recently-freed-when-all-the-variables-is-used/23802904) that offer detailed explanation)

## Question 4
#### Write a simple program that allocates memory using `malloc()` but forgets to free it before exiting. What happens when this program runs? Can you use `gdb` to find any problems with it? How about `valgrind`(again with the `--leak-check=yes` flag)?

Nothing goes wrong in the first two cases, but valgrind gives hints of the error message:
```shell
==3839== Memcheck, a memory error detector
==3839== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3839== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3839== Command: ./main
==3839== 
==3839== error calling PR_SET_PTRACER, vgdb might block
==3839== 
==3839== HEAP SUMMARY:
==3839==     in use at exit: 4 bytes in 1 blocks
==3839==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==3839== 
==3839== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==3839==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3839==    by 0x10865B: main (main.c:4)
==3839== 
==3839== LEAK SUMMARY:
==3839==    definitely lost: 4 bytes in 1 blocks
==3839==    indirectly lost: 0 bytes in 0 blocks
==3839==      possibly lost: 0 bytes in 0 blocks
==3839==    still reachable: 0 bytes in 0 blocks
==3839==         suppressed: 0 bytes in 0 blocks
==3839== 
==3839== For counts of detected and suppressed errors, rerun with: -v
==3839== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
This means that 4 bytes are allocated but not freed, thus are lost.

## Question 5
#### Write a program that creates an array of integers called `data` of size 100 using `malloc`; then, set `data[100]` to zero. What happens when you run this program? What happens when you run this program using `valgrind`? Is the program correct?

Nothing goes wrong in the first case, but valgrind gives hints of the error message:
```shell
==4405== Memcheck, a memory error detector
==4405== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4405== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==4405== Command: ./main
==4405== 
==4405== error calling PR_SET_PTRACER, vgdb might block
==4405== Invalid write of size 4
==4405==    at 0x1086AA: main (main.c:5)
==4405==  Address 0x522d1d0 is 0 bytes after a block of size 400 alloc'd
==4405==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4405==    by 0x10869B: main (main.c:4)
==4405== 
==4405== 
==4405== HEAP SUMMARY:
==4405==     in use at exit: 0 bytes in 0 blocks
==4405==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==4405== 
==4405== All heap blocks were freed -- no leaks are possible
==4405== 
==4405== For counts of detected and suppressed errors, rerun with: -v
==4405== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
This means that we shouldn't access address 0x522d1d0, which is after the allocated 400 bytes.

#### Question 6
#### Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use `valgrind` on it?

Nothing goes wrong in the first case, but valgrind gives hints of the error message:
```shell
==683== Memcheck, a memory error detector
==683== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==683== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==683== Command: ./main
==683== 
==683== error calling PR_SET_PTRACER, vgdb might block
==683== Invalid read of size 4
==683==    at 0x108706: main (main.c:7)
==683==  Address 0x522d108 is 200 bytes inside a block of size 400 free'd
==683==    at 0x4C30D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==683==    by 0x1086FB: main (main.c:6)
==683==  Block was alloc'd at
==683==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==683==    by 0x1086EB: main (main.c:5)
==683== 
0
==683== 
==683== HEAP SUMMARY:
==683==     in use at exit: 0 bytes in 0 blocks
==683==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==683== 
==683== All heap blocks were freed -- no leaks are possible
==683== 
==683== For counts of detected and suppressed errors, rerun with: -v
==683== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
This means that we shouldn't access address 0x522d108, which is inside the freed 400 bytes.

#### Question 7
#### Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

An error would be reported as follows. We don't need tools to find the problem.
```shell
free(): invalid pointer
[1]    1166 abort (core dumped)  ./main
```

#### Question 8
#### Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use `realloc()` to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use `realloc()` to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use `valgrind` to help you find bugs.

TODO

#### Question 9
#### Spend more time and read about using `gdb` and `valgrind`. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.