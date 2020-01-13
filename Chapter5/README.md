# Chapter 5

## Question 1
#### Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g.,`x`) and set its value to something (e.g.,`100`). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of `x`?

The initial x value of the child process is the same as the parent process. When changing the value of x, they don't affect each other, since they have their own address space.

## Question 2
#### Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

Both child and parent can access the file descriptor returned by `open()`. They can write things into the same file in an undetermined order,  which depends on the scheduler.

## Question 3
#### Write another program using `fork()`. The child process should print "hello"; the parent process should print "goodbye". You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

My solution is to call `sleep()` in parent process.

## Question 4
#### Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`.  Why do you think there are so many variants of the same basic call?

These are called `exec()` family, which are used to apply to various situations. The rules are summarized as follows.

- Required
    - **l** : list format arguments
    - **v** : vector format arguments

- Optional
    - **p** : don't need to specify path
    - **e** : need environment argument

## Question 5
#### Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

On success, `wait()` returns the process ID of the terminated child; on error, `-1` is returned. When using `wait()` in the child, it ruturns `-1`, which means the call failed and that no waiting needed. This is because child process doesn't have a child.

## Question 6
#### Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

`waitpid()` can be used to:
- support job control
- permit a non-blocking version of the `wait()` function
- To permit a library routine, such as `system()` or `pclose()`, to wait for its children without interfering with other terminated children for which the process has not waited

## Question 7
#### Write a program that creates a child process, and then in the child closes standard output (`STDOUT_FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

After closing standard output, the content of `printf()` won't be shown in the terminal. And if then we open a file descriptor, the content will be written into that place because of the following reansons:
- The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process
- After closing the file descriptor for STDOUT, the subsequent open system call will assign the fd of stdout to the new file

## Question 8
#### Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

[website](https://stackoverflow.com/questions/20187734/c-pipe-to-stdin-of-another-program) that offer hints.