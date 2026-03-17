#ifndef MINISHELL_H
#define MINISHELL_H

//includes
#include <stdio.h> //printf
#include <stdlib.h> //malloc, free
#include <readline/readline.h> //for read from console
#include <readline/history.h> //for history
#include <signal.h> //for signals
# include <sys/wait.h>
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
 * Struct that will be use in each cmd node
 * in order to avoid overwrite of the redir_in
 * when we have commands like this [cat << A << B]
 * so with this we can  simulate the shell, allowing
 * user type first until A and then again until B
 */
typedef struct s_redirect
{
	t_token_type		type;
	char				*file;
	int					expand;
	struct s_redirect	*next;
}	t_redirect;
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
	t_redirect *redirects;
	struct s_cmd *next; //pointer to the next node (if | is used)
};

//FUNCTIONS IN EACH FILE

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
int ft_check_unclosed_quotes(char *str);

//parse_cmd.c
t_cmd	*ft_generate_cmd();
int	ft_count_args(t_token *head);
void	ft_hanlde_cmd_parse_redirections(t_token **tmp,t_cmd *cmd);
void	ft_fill_up_cmd(t_token **tmp,t_cmd *cmd, int *i);
void	ft_parse_cmd(t_token *head, t_data *data);

//parse_cmd_utils.c
void	ft_add_cmd(t_cmd **head, t_cmd *new_cmd);
void    ft_print_cmds(t_cmd *cmds);
void	ft_add_cmd(t_cmd **head, t_cmd *new_node);
t_redirect	*ft_new_redirect(t_token_type type, char *file, int expand);
void    ft_redir_add_back(t_redirect **head, t_redirect *new_node);

//env_utils.c
t_env	*ft_new_env_node(char *key,char *value);
void	ft_env_add_back(t_env **head, t_env *new_node);
t_env	*ft_copy_env(char  **env);
void	ft_remove_env_node(t_env **head, char *key);
void	ft_set_env(t_data *data, char *key, char *value);
int	ft_env_size(t_env *env);
t_env	*ft_get_env_node(t_env *env, char *key);
char	**ft_env_to_array(t_env *env_list);

//here_doc_handler.c
void	ft_here_doc_store_data(t_data *data, t_redirect *redir, int tmp_fd);
void    ft_here_doc(t_data *data);

//free_helper.c
void    ft_free_tokens(t_token **tokens);
void    ft_free_cmds(t_cmd **cmds);
void    ft_free_data(t_data *data);
void    ft_free_redirects(t_redirect *redir);
void	ft_free_env(t_env **env);

//error_handler.c
void    ft_error(t_data *data);

//expanders.c
void    ft_expanders(t_data *data);
char    *ft_replace_text(char *str, t_data *data, char *dollar_pos);
char    *ft_get_expanded_value(char *dollar_pos, t_data *data);
char	*ft_expand_line(char *line, t_data *data);
char    *find_expandable_dollar(char *str);

//expanders_utils.c
char    *ft_strjoin_three(char *s1, char *s2, char *s3);
char	*get_vrb_value(char *vrb_name, t_data *data);
int		ft_know_vrb_name_size(char *str);
char    *ft_remove_quotes_str(char *str);
int	ft_contains_quotes(char *str);

// BUILT IN FUNCTIONS

//cd.c
void	ft_update_pwd(t_data *data);
void	ft_cd(t_cmd *cmd, t_data *data);

//echo.c
int	is_n_option(char *arg);
void	ft_echo(t_cmd *cmd, t_data *data);

//env.c
void	ft_env(t_data *data);

//exit.c
int	ft_is_numeric(char *str);
void	ft_exit(t_cmd *cmd, t_data *data);

//export.c
void	ft_swap_env(t_env *a, t_env *b);
void ft_print_export_node(t_env *node);
void ft_print_sorted_env(t_data *data);
void	ft_export_arg(char *arg, t_data *data);
void	ft_export(t_cmd *cmd, t_data *data);
void	ft_free_array(char **arr);

//pwd.c
void	ft_pwd(t_data *data);

//unset.c
void	ft_unset(t_cmd *cmd, t_data *data);

//execute_redirect.c
int	ft_handle_input_redir(t_redirect *redir);
int	ft_handle_output_redir(t_redirect *redir);
int	ft_apply_redirections(t_cmd *cmd);

//executor.c
void	ft_execute_multiple(t_data *data);
void	ft_executor_single(t_data *data);
void	ft_executor(t_data *data);
int ft_execute_builtin(t_cmd *cmd, t_data *data);

//execute_external.c
char	**get_path_array(t_data *data);
char	*ft_get_cmd_path(char *cmd, t_data *data);
void	ft_execute_external(t_cmd *cmd, t_data *data);
#endif
