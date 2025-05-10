#include "../includes/minishell.h"

int builtin_exit(char **args)
{
        int exit_code = 0;
        if (args[1])
                exit_code = atoi(args[1]);
        exit(exit_code);
}
