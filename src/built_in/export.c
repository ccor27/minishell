#include "minishell.h"

/**
 * Checks if a string is a valid identifier.
 */
int	ft_is_valid_identifier(char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Handles each argument of export.
 */
void	ft_export_arg(char *arg, t_data *data)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	value = NULL;
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		key = ft_substr(arg, 0, equal_pos - arg);
	else
		key = ft_strdup(arg);
	if (!ft_is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		data->exit_code = 1;
		if (key)
			free(key);
		if (value)
			free(value);
		return ;
	}
	if (equal_pos)
	{
		value = ft_strdup(equal_pos + 1);
		ft_set_env(data, key, value);
		free(value);
	}
	else
	{
		if (!ft_get_env_node(data->env, key))
			ft_env_add_back(&data->env, ft_new_env_node(ft_strdup(key), NULL));
		free(key);
	}
}

/**
 * Implementation of the export built-in.
 */
void	ft_export(t_cmd *cmd, t_data *data)
{
	int	i;

	if (!cmd->args[1])
	{
		ft_print_sorted_env(data);
		data->exit_code = 0;
		return ;
	}
	i = 1;
	data->exit_code = 0;
	while (cmd->args[i])
	{
		ft_export_arg(cmd->args[i], data);
		i++;
	}
}

/**
 * Swaps two nodes data for the sorting.
 */
void	ft_swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
