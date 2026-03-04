#include "minishell.h"

char    *ft_get_expanded_value(char *dollar_pos, t_data *data)
{
    char    *vrb_name;
    char    *value;
    int     vrb_len;

    vrb_len = ft_know_vrb_name_size(dollar_pos + 1);
    vrb_name = ft_substr(dollar_pos + 1, 0, vrb_len);
    value = get_vrb_value(vrb_name, data);
    free(vrb_name);

    if (!value)
        value = ft_strdup(""); // Replace with empty string if not found

    return (value);
}

char    *ft_replace_text(char *str, t_data *data, char *dollar_pos)
{
    char    *str_first_part;
    char    *str_second_part;
    char    *vrb_name;
    char    *str_replaced;

    if (!str || !data->env)
        return (NULL);

    str_first_part = ft_substr(str, 0, dollar_pos - str);
    vrb_name = ft_get_expanded_value(dollar_pos, data);
    str_second_part = ft_strdup(dollar_pos + 1 + ft_know_vrb_name_size(dollar_pos + 1));
    str_replaced = ft_strjoin_three(str_first_part, vrb_name, str_second_part);

    free(str_first_part);
    free(str_second_part);
    free(vrb_name);
    free(str);

    return (str_replaced);
}

void    ft_expanders(t_data *data)
{
    t_cmd *tmp;
    int i;
    char *dollar_symbol_pos;

    tmp = data->cmds;
    while (tmp)
    {
        i = 0;
        while (tmp->args && tmp->args[i])
        {
            // Find the pointer to the '$'
            dollar_symbol_pos = find_expandable_dollar(tmp->args[i]);
            // Note: We use a while loop here in case there are MULTIPLE $ in one string!
            // (e.g., "echo $USER lives in $PWD")
            while (dollar_symbol_pos)
            {
                tmp->args[i] = ft_replace_text(tmp->args[i], data, dollar_symbol_pos);
                // Search for the next '$' in the newly updated string!
                dollar_symbol_pos = find_expandable_dollar(tmp->args[i]);
            }
			tmp->args[i] = ft_remove_quotes_str(tmp->args[i]);
            i++;
        }
        tmp = tmp->next;
    }
}
