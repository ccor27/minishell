#include "minishell.h"

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

void ft_print_export_node(t_env *node)
{
    ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd(node->key, 1);
    if (node->value)
    {
        ft_putstr_fd("=\"", 1);
        ft_putstr_fd(node->value, 1);
        ft_putstr_fd("\"", 1);
    }
    ft_putendl_fd("", 1);
}
/**
 * Prints the environment sorted alphabetically.
 */
void ft_print_sorted_env(t_data *data)
{
    t_env   *sorted;
    char    **env_arr;
    t_env   *i;
    t_env   *j;

    env_arr = ft_env_to_array(data->env);
    sorted = ft_copy_env(env_arr);
    ft_free_array(env_arr); // FIX 1: Free the double array!
    i = sorted;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strncmp(i->key, j->key, ft_strlen(i->key) + 1) > 0)
                ft_swap_env(i, j);
            j = j->next;
        }
        ft_print_export_node(i);
        i = i->next;
    }
    ft_free_env(&sorted); // FIX 2: Free the temporary sorted list!
}

/**
 * Handles each argument of export.
 */
void	ft_export_arg(char *arg, t_data *data)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
		ft_set_env(data, key, value);
		free(value);
	}
	else
	{
		if (!ft_get_env_node(data->env, arg))
			ft_env_add_back(&data->env, ft_new_env_node(ft_strdup(arg), NULL));
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
	while (cmd->args[i])
	{
		ft_export_arg(cmd->args[i], data);
		i++;
	}
	data->exit_code = 0;
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

