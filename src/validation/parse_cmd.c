#include "minishell.h"

/**
 * make a loop through the tokens
 * calculate the size of the args
 * while the tokens' content is not a PIPE,
	store them in args or in the redirect
 * each time we find a PIPE, we do another cmd node
 */

t_cmd	*ft_generate_cmd(t_token *token)
{
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

void	ft_parse_cmd(t_token *head, t_data *data)
{
	int		num_args;
	t_token	*tmp;
	char	**args;
	int		i;

	num_args = 0;
	tmp = head;
	while (tmp)
	{
		num_args = ft_count_args(tmp);
		args = malloc((num_args + 1) * sizeof(char *));
		if (!args)
			return ; // TODO: handle errors
		i = 0;
		while (tmp && tmp->type != PIPE)
		{
			// skip the redirection symbols
			if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == HERE_DOC || tmp->type == APPEND)
			{
				/**
				 * validate if the next node is a word, if it so,
				 * validate if the current node is a specific type
				 * (redirect_in/out, here_doc, append) and indicate
				 * it in the cmd node
				 */
				if (tmp->next)
					tmp = tmp->next;
				else
					break ;
			}
			else
			{
				args[i++] = ft_strdup(tmp->content);
				tmp = tmp->next;
			}
		}
		args[i] = NULL;
		//if the token is a PIPE will move past
		if(tmp && tmp->type == PIPE)
			tmp = tmp->next;
		//generate the cmd and add it to data's cmds
	}
}
