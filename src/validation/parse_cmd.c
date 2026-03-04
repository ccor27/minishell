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

//TODO: pass the data in order to free in case of error
void    ft_hanlde_cmd_parse_redirections(t_token **tmp, t_cmd *cmd)
{
    t_redirect *new_redir;

    if((*tmp)->next && (*tmp)->next->type == WORD)
    {
        new_redir = ft_new_redirect((*tmp)->type, (*tmp)->next->content);
        ft_redir_add_back(&cmd->redirects, new_redir);
        (*tmp) = (*tmp)->next->next;
    }
    else //handle possible error
    {
        if(*tmp)
            *tmp=(*tmp)->next;
    }
}

//TODO: pass the data in order to free in case of error
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
