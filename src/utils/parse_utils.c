#include "minishell.h"

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
int is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

/**
 * Function to create a new token
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
