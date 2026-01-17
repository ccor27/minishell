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

void    ft_print_cmds(t_cmd *cmds)
{
    t_cmd   *current;
    int     i;
    int     cmd_count;

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
        if (current->redir_in)
        {
            if (current->is_heredoc)
                printf("   Input: HEREDOC (Delimiter: '%s')\n", current->redir_in);
            else
                printf("   Input: FILE ('%s')\n", current->redir_in);
        }

        if (current->redir_out)
        {
            if (current->is_append)
                printf("   Output: APPEND >> ('%s')\n", current->redir_out);
            else
                printf("   Output: TRUNCATE > ('%s')\n", current->redir_out);
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
