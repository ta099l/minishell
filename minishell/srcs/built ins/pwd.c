#include "../includes/minishell.h"

int builtin_pwd(void)
{
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
        else
                perror("pwd");
        return 0;
}
