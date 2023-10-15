/// @file syscpy.cpp
/// @brief - Copies a file on the user's computer using system calls.
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#include <unistd.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[]) 
{
    if(argc != 3)
  {
    const char *errorMessage1 = "Incorrect number of arguments.";
    syscall(SYS_write, STDOUT_FILENO, errorMessage1, strlen(errorMessage1));
    return 1;
  }
    
    const char *inputName = argv[1];
    int input = syscall(SYS_open, inputName, O_RDONLY);

    if(input == -1)
    {
        const char *errorMessage2 = "Input file doesn't exist.";
        syscall(SYS_write, STDOUT_FILENO, errorMessage2, strlen(errorMessage2));
        return 1;
    }

    const char *outputName = argv[2];
    int output = syscall(SYS_open, outputName, O_RDONLY);
    
    if(output != -1)
    {
        const char *errorMessage3 = "Output file already exists.";
        syscall(SYS_write, STDOUT_FILENO, errorMessage3, strlen(errorMessage3));
        return 1;
    }

    output = syscall(SYS_open, outputName,
				                        O_WRONLY | O_CREAT,
				                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    char buffer;
    while(syscall(SYS_read, input, &buffer, 1))
    {
        syscall(SYS_write, output, &buffer, 1);
    }

    const char *successMessage = "Success!";
    syscall(SYS_write, STDOUT_FILENO, successMessage, strlen(successMessage));

    syscall(SYS_close, input);
    syscall(SYS_close, input);
}


