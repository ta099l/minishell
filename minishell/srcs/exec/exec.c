#include "../includes/minishell.h"

void execute_commands(t_command *cmd_list, t_env *env)
{
        int i;
        int num_commands = 0 t_command *cmd = cmd_list;

        i = 0;
        while (cmd)
        // iterate through the command list
        {
                // Execute each command
                pid_t pid = fork();
                if (pid == -1)
                {
                        perror("fork mesh nafe3");
                        return;
                }
                if (pid == 0)
                // if child process
                // calls execve() with arguments
                {
                        // Redirect input/output if needed
                        if (cmd->infile)
                        {
                                int fd_in = open(cmd->infile, O_RDONLY);
                                if (fd_in == -1)
                                {
                                        perror("open infile");
                                        exit(EXIT_FAILURE);
                                }
                                dup2(fd_in, STDIN_FILENO);
                                close(fd_in);
                        }

                        if (cmd->outfile)
                        {
                                int fd_out;
                                if (cmd->append)
                                        fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644); // here we give it permissins so when it is created it know what permissions to give it otherwise there will be a permission denied error
                                else
                                        fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                                if (fd_out == -1)
                                {
                                        perror("open outfile");
                                        exit(EXIT_FAILURE);
                                }
                                dup2(fd_out, STDOUT_FILENO);
                                close(fd_out);
                        }

                        if (execve(cmd->args[0], cmd->args, env->envp) == -1)
                        {
                                perror("execve");
                                exit(EXIT_FAILURE);
                        }

                        // if built in cmd
                        char *path = find_last_node(env, args[0]);
                        execv(path, args);
                }
                num_commands++;
                cmd = cmd->next;
        }
        // Wait for all child processes to finish
        while (i < num_commands)
        {
                wait(&status);
                // waits for any child process to terminate and stores it exit status
                // ensures no zombie processes are left
                i++;
        }
}
// execve() works only with absolute paths like bin/ls
//  need to add path to the command PATH

/*
-Redirect stdin fd[0] if cmd->infile is not NULL
-Redirect stdout fd[1] if cmd->outfile is not NULL (in append or truncate mode)
*/