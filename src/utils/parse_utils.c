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
 * Function to add a new command to the
 * linked-list
 */
void	ft_add_cmd(t_cmd **head, t_cmd *new_node)
{
	t_cmd *temp;

    if (!*head)
    {
        *head = new_node;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
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
