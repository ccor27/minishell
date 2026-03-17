#include "minishell.h"

/**
 * make a loop through the tokens
 * calculate the size of the args
 * while the tokens' content is not a PIPE,
	store them in args or in the redirect
 * each time we find a PIPE, we do another cmd node
 */

t_cmd	*ft_generate_cmd()
{
	t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return (NULL);//TODO: handle error
    cmd->args=NULL;
    cmd->cmd_path=NULL;
    cmd->redirects = NULL;
    cmd->next=NULL;
    return (cmd);
}

/**
 * Function to know how many arguments a command
 * will have
 */
int	ft_count_args(t_token *head)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		// skip the redirection symbols
		if (tmp->type >= REDIRECT_IN && tmp->type <= HERE_DOC)
		{
			// to skip the filename
			if (tmp->next)
				tmp = tmp->next;
		}
		else
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/**
 * Parses a redirection and its target (file or delimiter), evaluates
 * here-doc expansion rules, and adds it to the command's redirect list.
 */
void	ft_hanlde_cmd_parse_redirections(t_token **tmp, t_cmd *cmd)
{
	t_redirect	*new_redir;
	char		*delimiter;
	int			expand;

	if ((*tmp)->next && (*tmp)->next->type == WORD)
	{
		delimiter = ft_strdup((*tmp)->next->content);
		expand = 1;
		if ((*tmp)->type == HERE_DOC)
		{
			if (ft_contains_quotes(delimiter))
				expand = 0;
			delimiter = ft_remove_quotes_str(delimiter);
		}
		new_redir = ft_new_redirect((*tmp)->type, delimiter, expand);
		free(delimiter);
		ft_redir_add_back(&cmd->redirects, new_redir);
		(*tmp) = (*tmp)->next->next;
	}
	else if (*tmp)
		*tmp = (*tmp)->next;
}

/**
 * Function to fill up a command node from a token
 * node
 */
void	ft_fill_up_cmd(t_token **tmp,t_cmd *cmd, int *i)
{
			while (*tmp && (*tmp)->type != PIPE)
		{
			if ((*tmp)->type >= REDIRECT_IN && (*tmp)->type <= HERE_DOC )
				ft_hanlde_cmd_parse_redirections(tmp,cmd);
			else
			{
				cmd->args[(*i)++] = ft_strdup((*tmp)->content);
				(*tmp) = (*tmp)->next;
			}
		}
}

/**
 * Function to convert the tokens into commands
 */
void	ft_parse_cmd(t_token *head, t_data *data)
{
	int		num_args;
	t_token	*tmp;
	int		i;
	t_cmd *cmd;

	num_args = 0;
	tmp = head;
	while (tmp)
	{
		cmd = ft_generate_cmd();
		num_args = ft_count_args(tmp);
		cmd->args = malloc((num_args + 1) * sizeof(char *));
		if (!cmd->args)
			return ; // TODO: handle errors
		i = 0;
		ft_fill_up_cmd(&tmp,cmd,&i);
		cmd->args[i] = NULL;
		ft_add_cmd(&data->cmds,cmd);
		if(tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
}
