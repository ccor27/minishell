#include "minishell.h"

/**
 * Function to get the value form an env variable
 */
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
        value = ft_strdup("");

    return (value);
}

/**
 * Function to replace the text of the env name
 * for its value
 */
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

/**
 * Auxiliar function to expand variable from env
 */
char	*ft_expand_line(char *line, t_data *data)
{
	char	*dollar_pos;

	dollar_pos = find_expandable_dollar(line);
	while (dollar_pos)
	{
		line = ft_replace_text(line, data, dollar_pos);
		dollar_pos = find_expandable_dollar(line);
	}
	return (line);
}

/**
 * Function to expand the value of a
 * env variable
 */
void	ft_expanders(t_data *data)
{
	t_cmd	*tmp;
	int		i;

	tmp = data->cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			tmp->args[i] = ft_expand_line(tmp->args[i], data);
			tmp->args[i] = ft_remove_quotes_str(tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

/**
 * Function to find the position of $
 * only if it is not inside single quotes
 */
char    *find_expandable_dollar(char *str)
{
    int in_sq = 0;
    int in_dq = 0;
    int i = 0;

    while (str && str[i])
    {
        if (str[i] == '\'' && !in_dq)
            in_sq = !in_sq;
        else if (str[i] == '\"' && !in_sq)
            in_dq = !in_dq;

        else if (str[i] == '$' && !in_sq)
        {
            if (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
                return (&str[i]);
        }
        i++;
    }
    return (NULL);
}
