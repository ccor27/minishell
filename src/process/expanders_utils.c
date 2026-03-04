#include "minishell.h"

char    *ft_strjoin_three(char *s1, char *s2, char *s3)
{
    char    *temp;
    char    *final_str;

    temp = ft_strjoin(s1, s2);
    final_str = ft_strjoin(temp, s3);
    free(temp);

    return (final_str);
}

char	*get_vrb_value(char *vrb_name, t_data *data)
{
	char *vrb_value;
	t_env *head;
	int vrb_name_size;

	vrb_value = NULL;
	if(!vrb_name || !data->env)
		return (NULL);
	head = data->env;
	vrb_name_size = ft_strlen(vrb_name);
	while(head)
	{
		if(ft_strncmp(vrb_name,head->key,vrb_name_size) == 0 &&
			head->key[vrb_name_size] == '\0')
		{
			vrb_value = ft_strdup(head->value);
			break;
		}
		head = head->next;
	}
	return (vrb_value);
}

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
// Finds a '$' ONLY if it is not inside single quotes.
char    *find_expandable_dollar(char *str)
{
    int in_sq = 0; // 1 if inside single quotes ('')
    int in_dq = 0; // 1 if inside double quotes ("")
    int i = 0;

    while (str && str[i])
    {
        // Toggle quote states
        if (str[i] == '\'' && !in_dq)
            in_sq = !in_sq;
        else if (str[i] == '\"' && !in_sq)
            in_dq = !in_dq;

        // If we find a $ and we are NOT inside single quotes
        else if (str[i] == '$' && !in_sq)
        {
            // Make sure it is a valid variable name next (or ?)
            if (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
                return (&str[i]);
        }
        i++;
    }
    return (NULL);
}

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
