#include "minishell.h"

//TODO: test this
int ft_env(t_data *data)
{
    t_env   *tmp;

    if (!data || !data->env)
        return (1);

    tmp = data->env;
    while (tmp)
    {
        // Only print if there is a value attached!
        if (tmp->value)
        {
            printf("%s=%s\n", tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
    return (0); // Success
}
