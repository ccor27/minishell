#include "minishell.h"

/**
 * Implementation of the pwd built-in.
 * Displays the current working directory.
 */
void	ft_pwd(t_data *data)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		data->exit_code = 0;
	}
	else
	{
		perror("pwd");
		data->exit_code = 1;
	}
}
