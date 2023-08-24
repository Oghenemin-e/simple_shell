#ifndef SHELL_H
#define SHELL_H

int execute_command(const char **args);
char *parse_input(const char *input);
int set_environment_variable(const char *name, const char *value);

#endif /* SHELL_H */
