#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <ctype.h> /* Include ctype.h for isspace */

char *parse_input(const char *input) {
    int start = 0;
    int end;

    char *parsed_input; /* Declare parsed_input here */

    if (input == NULL || input[0] == '\0') {
        return NULL; /* No input to parse, return NULL */
    }

    /* Trim leading and trailing whitespace */
    while (isspace(input[start])) {
        start++;
    }

    end = strlen(input) - 1;
    while (end >= 0 && isspace(input[end])) {
        end--;
    }

    if (end < start) {
        return NULL; /* Input contains only whitespace, return NULL */
    }

    /* Extract and return the trimmed input */
    parsed_input = strndup(input + start, end - start + 1);
    return parsed_input;
}
