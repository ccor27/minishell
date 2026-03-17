#include "minishell.h"

/**
 * Function to join three strings into one
 */
char    *ft_strjoin_three(char *s1, char *s2, char *s3)
{
    char    *temp;
    char    *final_str;

    temp = ft_strjoin(s1, s2);
    final_str = ft_strjoin(temp, s3);
    free(temp);

    return (final_str);
}

/**
 * Auxiliar function to get the value of an env variable
 */
char	*get_vrb_value(char *vrb_name, t_data *data)
{
	char	*vrb_value;
	t_env	*head;
	int		vrb_name_size;

	vrb_value = NULL;
	if (!vrb_name || !data)
		return (NULL);
	if (ft_strncmp(vrb_name, "?", 2) == 0)
		return (ft_itoa(data->exit_code));
	if (!data->env)
		return (NULL);
	head = data->env;
	vrb_name_size = ft_strlen(vrb_name);
	while (head)
	{
		if (ft_strncmp(vrb_name, head->key, vrb_name_size) == 0 &&
			head->key[vrb_name_size] == '\0')
		{
			vrb_value = ft_strdup(head->value);
			break ;
		}
		head = head->next;
	}
	return (vrb_value);
}

/**
 * Function to know env variable name size
 */
int		ft_know_vrb_name_size(char *str)
{
	int len;

	if(str[0] == '?')
		return (1);

	len = 0;
	while(str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return(len);
}

/**
 * Function to know if a string
 * contains quotes
 */
int	ft_contains_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

/**
 * Function to remove quotes from a string
 */
//TODO: fix this, we have 5 variables!
char    *ft_remove_quotes_str(char *str)
{
    int     in_sq = 0;
    int     in_dq = 0;
    int     i = 0;
    int     j = 0;
    char    *new_str;

    if (!str)
        return (NULL);
    new_str = malloc(ft_strlen(str) + 1); // Max possible length
    if (!new_str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '\'' && !in_dq)
            in_sq = !in_sq;
        else if (str[i] == '\"' && !in_sq)
            in_dq = !in_dq;
        else
            new_str[j++] = str[i]; // Only copy normal characters
        i++;
    }
    new_str[j] = '\0';
    free(str); // Free the old string with quotes!
    return (new_str);
}
