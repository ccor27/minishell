#include "minishell.h"

/**
 * Handles < and << (Input Redirections)
 */
int	ft_handle_input_redir(t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/**
 * Handles > and >> (Output Redirections)
 */
int	ft_handle_output_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == REDIRECT_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/**
 * Loops through the linked list of redirections and applies them.
 * Returns 0 on success, 1 on failure (file not found).
 */
int	ft_apply_redirections(t_cmd *cmd)
{
	t_redirect	*redir;

	if (!cmd || !cmd->redirects)
		return (0);
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIRECT_IN || redir->type == HERE_DOC)
		{
			if (ft_handle_input_redir(redir) == 1)
				return (1);
		}
		else if (redir->type == REDIRECT_OUT || redir->type == APPEND)
		{
			if (ft_handle_output_redir(redir) == 1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
