#include "minishell.h"

/**
 * Function to store in a temporal file
 * the user input (for the here_doc)
 */
void	ft_here_doc_store_data(t_data *data, t_redirect *redir, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-doc delimited by EOF\n", 1);
			break ;
		}
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (redir->expand)
			line = ft_expand_line(line, data);
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}

/**
 * Auxiliar function handle here_doc
 * basically create a temporal file to store
 * user input
 */
void	ft_here_doc_aux(t_data *data, int *i, t_cmd *tmp)
{
	t_redirect	*redir;
	char		*num_str;
	char		*tmp_name;
	int			tmp_fd;

	redir = tmp->redirects;
	while (redir)
	{
		if (redir->type == HERE_DOC)
		{
			num_str = ft_itoa((*i)++);
			tmp_name = ft_strjoin(".tmp_heredoc_", num_str);
			free(num_str);
			tmp_fd = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (tmp_fd >= 0)
			{
				ft_here_doc_store_data(data, redir, tmp_fd);
				free(redir->file);
				redir->file = tmp_name;
			}
		}
		redir = redir->next;
	}
}

/**
 * Function to handle the here docs
 * commands before execute all commands
 */
void	ft_here_doc(t_data *data)
{
	t_cmd	*tmp;
	int		i;

	tmp = data->cmds;
	i = 0;
	while (tmp)
	{
		ft_here_doc_aux(data, &i, tmp);
		tmp = tmp->next;
	}
}

/**
 * @brief Deletes temporary files created for here-docs.
 * 
 * @param cmds Linked list of commands.
 */
void	ft_cleanup_heredocs(t_cmd *cmds)
{
	t_cmd		*tmp_cmd;
	t_redirect	*tmp_redir;

	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		tmp_redir = tmp_cmd->redirects;
		while (tmp_redir)
		{
			if (tmp_redir->type == HERE_DOC)
				unlink(tmp_redir->file);
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
