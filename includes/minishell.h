#ifndef MINISHELL_H
#define MINISHELL_H

//includes
#include <stdio.h> //printf
#include <stdlib.h> //malloc, free
#include <readline/readline.h> //for read from console
#include <readline/history.h> //for history
#include <signal.h> //for signals
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
 * Main struct to handle data
 */
typedef struct s_data
{
	char **env; //A copy of enviroment variables
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
//parse_utils.c
void	ft_add_token(t_token **head, t_token *token);
void	ft_print_tokens(t_token **head);
t_token *generate_token(char *content, t_token_type type);
int is_separator(char c);
#endif
