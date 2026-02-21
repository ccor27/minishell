#ifndef MINISHELL_H
#define MINISHELL_H

//includes
#include <stdio.h> //printf
#include <stdlib.h> //malloc, free
#include <readline/readline.h> //for read from console
#include <readline/history.h> //for history
#include <signal.h> //for signals
#include <fcntl.h>
#include "libft.h"
//structs

typedef struct s_cmd t_cmd;


typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND, // >>
	HERE_DOC //

} t_token_type;
/**
 * Struct to represent a token.
 * This struct will be used to store tokens, that basically
 * are the user's input splited by spaces and separators
 *
 * so the user type ls -la | grep "hola mundo" we'll have
 * 					[ls],[-la],[|],[grep],[hola mundo]
 * and it will work in this case ls|grep a
 * even the word has no spaces, the shell should handle it
 * so we'll have [ls],[|],[grep],[a]
 *
 * After do this will convert the tokens into a real
 * command using the t_cmd struct.
 *
 */
typedef struct s_token
{
	char	*content;
	t_token_type	type;
	struct s_token *next;
} t_token;
/**
 * Nodes to store de data of enviroment we
 * receive in the main, this will be a
 * linked-list
 */
typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
} t_env;
/**
 * Main struct to handle data
 */
typedef struct s_data
{
	t_env *env; //A copy of enviroment variables
	t_cmd *cmds; //The head of the linked-list
	t_token *tokens;//
	int exit_code; //The exit command of the last status (needed for $?)
} t_data;

/**
 * Struct to store data of the commands
 * Basically this will be a linked-list
 */
struct s_cmd
{
	char **args; //the command + flags slpit up. ({"ls","-la",NULL})
	char *cmd_path; //the full path found
	//redirection information
	int  fd_input; //input fd (0 by default)
	int  fd_output;//output fd (1 by default)
	char *redir_in;//name of the file to read from (if < is used)
	char *redir_out;//name of the file to write (if > is used)
	int  is_append;//flag
	int  is_heredoc;//flag
	//the link
	struct s_cmd *next; //pointer to the next node (if | is used)
};

//functions
//minishell.c
void	ft_init_data_struct(t_data *data, char **envp);
//signals.c
void handle_sigint(int sig);
void print_header(void);
//parse_tokens.c
void	ft_parse_and_store(char *cmd, t_data *data);
void	ft_handle_separator(int *i, char *cmd, t_data *data);
void	ft_handle_word(int *i, char *cmd, t_data *data);
int	ft_handle_quotes(char *cmd, int i,char quote);
t_token_type	ft_know_type(char separator);
//parse_token_utils.c
void	ft_add_token(t_token **head, t_token *token);
void	ft_print_tokens(t_token **head);
t_token *generate_token(char *content, t_token_type type);
int is_separator(char c);
//parse_cmd.c
t_cmd	*ft_generate_cmd();
int	ft_count_args(t_token *head);
void	ft_hanlde_cmd_parse_redirections(t_token **tmp,t_cmd *cmd);
void	ft_fill_up_cmd(t_token **tmp,t_cmd *cmd, int *i);
void	ft_parse_cmd(t_token *head, t_data *data);
//parse_cmd_utils.c
void	ft_add_cmd(t_cmd **head, t_cmd *new_cmd);
void    ft_print_cmds(t_cmd *cmds);
//env_utils.c
t_env	*ft_new_env_node(char *key,char *value);
void	ft_env_add_back(t_env **head, t_env *new_node);
t_env	*ft_copy_env(char  **env);
int	ft_env_size(t_env *env);
char	**ft_env_to_array(t_env *env_list);
//here_doc_handler.c
void	ft_here_doc_store_data(t_cmd *node,int tmp_file,char *tmp_file_name);
void    ft_here_doc(t_data *data);
//free_helper.c
void    ft_free_tokens(t_token **tokens);
void    ft_free_cmds(t_cmd **cmds);
void    ft_free_data(t_data *data);
//error_handler.c
void    ft_error(t_data *data);
#endif
