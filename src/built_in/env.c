#include "minishell.h"

/**
 * Implementation of the env built-in.
 * Displays the current environment variables.
 * Note: Per subject, env with no options or arguments.
 */
void	ft_env(t_data *data)
{
	t_env	*tmp;

	if (!data || !data->env)
		return ;
	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
	data->exit_code = 0;
}
