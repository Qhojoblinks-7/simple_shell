```markdown
# 0x16. C - Simple Shell

## Project Overview

This project is a simple Unix shell implementation created in C. The goal is to provide an interactive user interface for interacting with a Linux operating system.

### Auther

- Immanuel Eshun Quansah

## How to add Author file
Bash script for generating the list of authors in git repo

#!/bin/sh

git shortlog -se \
  | perl -spe 's/^\s+\d+\s+//' \
  | sed -e '/^CommitSyncScript.*$/d' \
  > AUTHORS

## Learning Objectives

After completing this project, you should be able to:

- Explain the design and implementation of the original Unix operating system.
- Identify the original author of the first version of the UNIX shell.
- Understand the history of the B programming language, the predecessor to the C programming language.
- Explain the contributions of Ken Thompson.
- Describe how a shell works.
- Define "pid" and "ppid."
- Manipulate the environment of the current process.
- Differentiate between a function and a system call.
- Create processes.
- Understand the three prototypes of the main function.
- Explain how the shell uses the PATH to find programs.
- Execute another program using the execve system call.
- Suspend the execution of a process until one of its children terminates.
- Define "EOF" (end-of-file).

# files
- README.md - description about the project repo
- man_1_simple_shell - is the man page for the shell we are going to write.
- AUTHORS - file at the root of your repository, listing all individuals having contributed content to the repository.
- main.h - is the header file which contains the standared header file and prototype of o function used in the program.
- main.c - initialize the program with infinite loop by call the prompt function
- prompt.c - it use getline system call to read the input from the user and run infinite loop with fork to keep prompt going.
- special_character - It identiies if the special inputs such as if the frist input is slash,the user typed exit or env...
- string.c -it handles the strings(string length, write string,find string in directory,concatane strings....)
- cmd.c - it finds the command the user entered.
- execute.c - execute the command.

### General

- Allowed editors: vi, vim, emacs
- Compilation: `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
- Files should end with a new line.
- A README.md file is mandatory.
- Code should follow the Betty style.
- No memory leaks are allowed.
- No more than 5 functions per file.
- All header files should be include-guarded.
- Use system calls only when necessary.

## Usage

To compile the shell, use the provided compilation command. The shell program can be executed as `./hsh`.

### Example:

```shell
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
$ ./hsh
```

## Output

Unless specified otherwise, the shell program should have the exact same output as `/bin/sh`, including error output. When printing an error, the name of the program must be equivalent to `arguments[0]`.

## List of Allowed Functions and System Calls

- access
- chdir
- close
- closedir
- execve
- exit
- _exit
- fflush
- fork
- free
- getcwd
- getline
- getpid
- isatty
- kill
- malloc
- open
- opendir
- perror
- read
- readdir
- signal
- stat (__xstat)
- lstat (__lxstat)
- fstat (__fxstat)
- strtok
- wait
- waitpid
- wait3
- wait4
- write
```
