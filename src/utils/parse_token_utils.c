#include "minishell.h"

/**
 * Function to add a token to the linked-list
 * the new token will be added to the end of the list
 */
void	ft_add_token(t_token **head, t_token *new_token)
{
	t_token *tmp;

	if(!new_token)
		return;
	if(!*head)
	{
		*head = new_token;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

/**
 * Auxiliary function to print the linked-list
 * of tokens,this is  just to know if I was
 * storing the data correctly
 */
void	ft_print_tokens(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	while (tmp)
	{
		printf("token: [%s]\n",tmp->content);
		tmp = tmp->next;
	}
}

/**
 * Function to validate if  a character is a separator
 */
int is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

/**
 * Function to create a new token.
 */
t_token *generate_token(char *content, t_token_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if(!token)
		return(NULL); //TODO: hanlde errors
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}

/**
 * Function to validate if there are any quote
 * unclosed
 */
int ft_check_unclosed_quotes(char *str)
{
    int i;
    int in_sq;
    int in_dq;

    i = 0;
    in_sq = 0;
    in_dq = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !in_dq)
            in_sq = !in_sq;
        else if (str[i] == '\"' && !in_sq)
            in_dq = !in_dq;
        i++;
    }
    if (in_sq || in_dq)
        return (1);
    return (0);
}
