
#ifndef MINISHELL_H
#define MINISHELL_H
//include library
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "../libft/libft.h"

typedef struct s_envp {
    char **tmp_envp;  
    int counter;   
} t_envp;

typedef enum e_types {
    WORD = 1,      
    PIPE = 2,    
    REDIR = 3,     
    HEREDOC = 4 
   
} t_types;
typedef struct s_tmptoken{
    char *value;
    int start;
    int end;
 
} t_tmptoken;

typedef struct s_token{
    char *value;
    t_types type;
    struct s_token *prev;
   struct s_token *next;
}t_token;


typedef struct s_all{
    struct s_token *token;
    struct s_tmptoken *tmp;
    struct s_command *cmd;
    struct s_envp *cp_envp;
    char *var_value;


}t_all;

typedef struct s_command
{
    char **args;   // array of arguments
    char *infile;  // file to read from
    char *outfile; // file to write to
    int append;    // 0 for >, 1 for >>
    struct s_command *next;
} t_command;

t_command *new_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->next = NULL;
    return cmd;
}

//nodes
t_token	*find_last_node(t_token *token);
int	add_node(t_token **token, char *input);
int toknize(char* input, t_all *as);
//init
t_all *init_strcuts(t_all *as);
void	init_token(t_tmptoken *tmptoken);
//split.c
int	is_parameter(char c);
int	parameter_token(char *input, int i, t_tmptoken *tmp, t_token **token);

//split.c
int split_input(char* input,t_token **token, t_tmptoken *tmp);
void	print_list(t_token *head);
//free
void free_all(t_all *as);
void free_tokens(t_token *token);
int clean(t_all *as);
int clean_all(t_all *as);
int free_envp(t_envp *cp_envp);
//qoutes
int closing_qoutes(char *input, int i);
int find_closing_quote(char *input, int i, int flag, char quote_type);
int	handle_quotes(char *input, int i, t_tmptoken *tmp, t_token **token);
void replace_qoutes(t_token *token, int i, int j, int q);
void remove_quotes(t_token *token);

//splits 2
int closing_qoutes(char *input, int i);
int	str(char *input, int i, t_tmptoken *tmp, t_token **token);
void token_types(t_token *token);


//env
t_envp *copy_envp(char **envp, t_all *as);
void print_envp(t_envp *cp_envp);
char *expand_variables(char *input, t_all *as);

int var_length(char *var, int len, t_envp *cp_envp, t_all *as);
char *expand_variables(char *input, t_all *as);

//exec
char *find_path(t_envp *cp_envp, char *cmd);
char *get_full_path(char *dir, char *cmd);

#endif
