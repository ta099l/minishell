#include "../includes/minishell.h"

int builtin_echo(char **args)
{
        int i = 1;
        while (args[i])
        {
                printf("%s", args[i]);
                if (args[i + 1])
                        printf(" ");
                i++;
        }
        printf("\n");
        return 0;
}
