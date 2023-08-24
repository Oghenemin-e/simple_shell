#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int set_environment_variable(const char *name, const char *value) {
    int result;

    if (name == NULL || value == NULL) {
        return -1; /* Invalid input, return error */
    }

    result = setenv(name, value, 1);

    if (result == -1) {
        perror("setenv");
        return -1; /* Error setting environment variable, return error */
    }

    return 0; /* Environment variable set successfully, return success */
}
