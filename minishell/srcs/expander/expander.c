#include "../includes/minishell.h"

// Get length of a variable's value and store its pointer in `as->var_value`
int var_length(char *var, int len, t_envp *cp_envp, t_all *as)
{
        int j = 0;
        as->var_value = "";

        while (cp_envp->tmp_envp[j])
        {
                if (ft_strncmp(cp_envp->tmp_envp[j], var, len) == 0 &&
                    cp_envp->tmp_envp[j][len] == '=')
                {
                        as->var_value = cp_envp->tmp_envp[j] + len + 1;
                        break;
                }
                j++;
        }

        // if (!as->var_value)
        // {
        // return 0;
        // }
        return ft_strlen(as->var_value);
}

// Expand $VAR in the input string using environment in `as->cp_envp`
char *expand_variables(char *input, t_all *as)
{
        int i = 0;
        char *result = malloc(1);
        if (!result)
                return 0;
        result[0] = '\0';

        while (input[i])
        {
                if (input[i] == '$')
                {
                        i++;
                        int var_start = i;
                        int j = 0;

                        while (ft_isalnum(input[i]))
                        {
                                j++;
                                i++;
                        }

                        char *var = malloc(j + 1);
                        if (!var)
                                return 0;
                        ft_strlcpy(var, input + var_start, j + 1);

                        (void)var_length(var, j, as->cp_envp, as); // get var value pointer in `as`

                        if (as->var_value)
                        {
                                char *tmp = result;
                                result = ft_strjoin(tmp, as->var_value);
                                free(tmp);
                        }

                        free(var);
                }
                else
                {
                        char tmp[2] = {input[i], '\0'};
                        char *old = result;
                        result = ft_strjoin(old, tmp);
                        free(old);
                        i++;
                }
        }

        return result;
}