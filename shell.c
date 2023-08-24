#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/* Function to handle the exit command */
void exit_shell() {
    printf("Exiting the shell...\n");
    exit(0);
}

int main() {
    char *input;
    int status;
    const char **args; /* Declare args at the beginning */

    while (1) {
        printf("$ ");
        input = read_input(); /* Assuming you have a read_input function */

        if (input == NULL) {
            printf("\n");
            exit_shell();
        }

        args = parse_input(input); /* Make sure parse_input returns const char** */

        if (args != NULL && args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                exit_shell();
            } else {
                status = execute_command(args);
                if (status == -1) {
                    fprintf(stderr, "Command execution failed.\n");
                }
            }
        }

        free(input);
        free(args);
    }

    return 0;
}
