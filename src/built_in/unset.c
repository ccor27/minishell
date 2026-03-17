#include "minishell.h"

/**
 * Implementation of the unset built-in.
 * Removes environment variables.
 */
void	ft_unset(t_cmd *cmd, t_data *data)
{
	int	i;

	if (!cmd || !cmd->args || !data)
		return ;
	i = 1;
	while (cmd->args[i])
	{
		ft_remove_env_node(&data->env, cmd->args[i]);
		i++;
	}
	data->exit_code = 0;
}
