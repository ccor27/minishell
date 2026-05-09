#include "minishell.h"

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
    ft_free_array(env_arr);
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
    ft_free_env(&sorted);
}
