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
		return;//TODO: handle error
	cmd->args=NULL;
	cmd->cmd_path=NULL;
	cmd->fd_input=-1;
	cmd->fd_output= -1;
	cmd->redir_in=NULL;
	cmd->redir_out=NULL;
	cmd->is_append=0;
	cmd->is_heredoc=0;
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
		if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
			|| tmp->type == HERE_DOC || tmp->type == APPEND)
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

//TODO: pass the data in order to free in case of error
void	ft_hanlde_cmd_parse_redirections(t_token *tmp,t_cmd *cmd)
{
	if(tmp->next && tmp->next->type==WORD)
	{
		if(tmp->type == REDIRECT_IN)
			cmd->redir_in = ft_strdup(tmp->next->content);
		else if (tmp->type == REDIRECT_OUT)
			cmd->redir_out = ft_strdup(tmp->next->content);
		else if (tmp->type == APPEND)
		{
			cmd->redir_out = ft_strdup(tmp->next->content);
			cmd->is_append = 1;
		}
		else
		{
		//HERE_DOC
			cmd->redir_in = ft_strdup(tmp->next->content);
			cmd->is_heredoc = 1;
		}
		tmp=tmp->next->next;//skip the redirection and the filename
	}
	else//handle possible error
		return;
}

//TODO: pass the data in order to free in case of error
void	ft_fill_up_cmd(t_token *tmp,t_cmd *cmd, int *i)
{
			while (tmp && tmp->type != PIPE)
		{
			// skip the redirection symbols
			if (tmp->type >= REDIRECT_IN && tmp->type <= HERE_DOC )
				ft_hanlde_cmd_parse_redirections(tmp,cmd);
			else
			{
				cmd->args[(*i)++] = ft_strdup(tmp->content);
				tmp = tmp->next;
			}
		}
}

void	ft_parse_cmd(t_token *head, t_data *data)
{
	int		num_args;
	t_token	*tmp;
	int		i;
	t_cmd *cmd;

	num_args = 0;
	tmp = head;
	while (tmp)
	{//here we have to create the cmd nodes
		//crete the cmd node
		cmd = ft_generate_cmd();
		num_args = ft_count_args(tmp);
		cmd->args = malloc((num_args + 1) * sizeof(char *));
		if (!cmd->args)
			return ; // TODO: handle errors
		i = 0;
		ft_fill_up_cmd(tmp,cmd,&i);
		cmd->args[i] = NULL;
		ft_add_cmd(&data->cmds,cmd);
		//if the token is a PIPE will move past
		if(tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
	/**
	 * TODO:
	 * 		- split into functions
	 * 		- create a function to print the cmds
	 * 		- test code
	 */
}
