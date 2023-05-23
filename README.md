This project focus on building a simple UNIX shell program.
The program is a requirement to implement the knowledge of,
        C programming language and shell basics.
This project contains defined user functions, this functions,
        do similar work compared to the same library function,
        example; copy_string does the work of stcpy.
The project consist of files,all sums up the step by step function,
        of a shell program.
The project shows the basic function of a shell,from infinite prompt,
    to parsing, exexcution of commands and exiting of the shell.
1: This step display a prompt and wait for the user to type a command,
        at this point,it does not handle many attributes of the shell yet.
2: This step Handle command lines with arguments, Unlike the first step,
        that only reads and prints out user input.
3: This step handle the PATH,which is the list of all directories,
        a shell access to execute a particular command.
4: This step implement the exit built-in, that exits the shell,
        from the steps above,the shell can not exit yet.
5: This step implement the env built-in, that prints the current environment,
6: This step, we write a function that reads input from the command line,
        this function doeas the work of the library function 'getline'.
7: This step, we write a function that tokenize input from the command line,
        this function doeas the work of the library function 'strtok'.
8: This step handle arguments for the built-in exit,
        exit status also allowed at this point.
9: This step implement the setenv and unsetenv builtin commands.
10: This step implement the builtin command cd.
11: This step Handle the commands separator ;, which is a sequencing character.
12: This step Handle the && and || shell logical operators.
13: This step implement the alias builtin command.
14: This step Handle variables replacement,Handle the $? variable.
        Handle the $$ variable.
15: This step Handle comments (#).
16: This step handle the usage of simple_shell [filename].
