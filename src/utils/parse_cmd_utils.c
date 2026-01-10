#include "minishell.h"

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