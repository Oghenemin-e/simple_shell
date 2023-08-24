#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int execute_command(const char **args) {
    pid_t pid;
    int status;

    char *token;  /* Declare token here */

    if (args == NULL || args[0] == NULL) {
        return 0; /* No command to execute, return success */
    }

    if (strchr(args[0], '/') != NULL) {
        /* The command includes a path, execute it directly */
        pid = fork();

        if (pid == -1) {
            perror("fork");
            return -1; /* Fork failed, return error */
        }

        if (pid == 0) {
            /* This is the child process */
            execv(args[0], (char *const *)args);
            perror("execv");
            exit(1); /* Exit the child process with an error */
        } else {
            /* This is the parent process */
            waitpid(pid, &status, 0);
            return WEXITSTATUS(status); /* Get the exit status of the child process */
        }
    } else {
        /* The command does not include a path, search in PATH */
        char *path = getenv("PATH");
        if (path == NULL) {
            fprintf(stderr, "PATH environment variable not set.\n");
            return -1;
        }

        token = strtok(path, ":");
        while (token != NULL) {
            char command_path[1024]; /* Adjust the size as needed */
            snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);

            if (access(command_path, X_OK) == 0) {
                /* The command exists, execute it */
                pid = fork();

                if (pid == -1) {
                    perror("fork");
                    return -1; /* Fork failed, return error */
                }

                if (pid == 0) {
                    /* This is the child process */
                    execv(command_path, (char *const *)args);
                    perror("execv");
                    exit(1); /* Exit the child process with an error */
                } else {
                    /* This is the parent process */
                    waitpid(pid, &status, 0);
                    return WEXITSTATUS(status); /* Get the exit status of the child process */
                }
            }

            token = strtok(NULL, ":");
        }

        fprintf(stderr, "Command not found in PATH: %s\n", args[0]);
        return -1;
    }
}
