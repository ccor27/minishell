#include "minishell.h"

/**
 * Checks if a string is a valid numeric argument.
 */
int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Implementation of the exit built-in.
 */
void	ft_exit(t_cmd *cmd, t_data *data)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 1);
	if (cmd->args[1])
	{
		if (!ft_is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			ft_free_data(data);
			exit(2);
		}
		if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			data->exit_code = 1;
			return ;
		}
		exit_code = ft_atoi(cmd->args[1]);
		data->exit_code = (int)(exit_code % 256);
	}
	ft_free_data(data);
	exit(data->exit_code);
}
