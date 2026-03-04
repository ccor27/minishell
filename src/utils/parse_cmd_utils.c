#include "minishell.h"

/**
 * Function to add a new command to the
 * linked-list
 */
void	ft_add_cmd(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

/**
 * Function to create a new node of redirection
 */
t_redirect  *ft_new_redirect(t_token_type type, char *file)
{
    t_redirect *node;

    node = malloc(sizeof(t_redirect));
    if (!node)
        return (NULL);
    node->type = type;
    node->file = ft_strdup(file);
    node->next = NULL;
    return (node);
}

/**
 * Function to add in the back/end a new node of redirection
 */
void    ft_redir_add_back(t_redirect **head, t_redirect *new_node)
{
    t_redirect *tmp;

    if (!*head)
    {
        *head = new_node;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void	ft_print_cmds(t_cmd *cmds)
{
	t_cmd		*current;
	int			i;
	int			cmd_count;
	t_redirect	*redir;

	current = cmds;
	cmd_count = 1;
	printf("\n--- COMMAND LIST DEBUG ---\n");
	if (!current)
		printf("(List is empty)\n");
	while (current)
	{
		printf(" [CMD %d]\n", cmd_count++);
		// 1. Print Arguments (Command + Flags)
		printf("   Args: ");
		if (current->args && current->args[0])
		{
			i = 0;
			printf("[");
			while (current->args[i])
			{
				printf("'%s'", current->args[i]);
				if (current->args[i + 1])
					printf(", ");
				i++;
			}
			printf("]");
		}
		else
			printf("(None)");
		printf("\n");
		// 2. Print Redirections
		redir = current->redirects;
		if (!redir)
			printf("   Redirections: (None)\n");
		else
		{
			printf("   Redirections:\n");
			while (redir)
			{
				if (redir->type == HERE_DOC)
					printf("     - HEREDOC (Delimiter: '%s')\n", redir->file);
				else if (redir->type == REDIRECT_IN)
					printf("     - INPUT < ('%s')\n", redir->file);
				else if (redir->type == REDIRECT_OUT)
					printf("     - OUTPUT > ('%s')\n", redir->file);
				else if (redir->type == APPEND)
					printf("     - APPEND >> ('%s')\n", redir->file);
				redir = redir->next;
			}
		}
		// 3. Print Pipe status
		if (current->next)
			printf("   Next: PIPE ->\n");
		else
			printf("   Next: NULL (End)\n");
		printf("--------------------------\n");
		current = current->next;
	}
	printf("--- END DEBUG ---\n\n");
}
