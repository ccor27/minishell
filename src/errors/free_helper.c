#include "minishell.h"

void    ft_free_data(t_data *data)
{
    ft_free_tokens(&data->tokens);
    ft_free_cmds(&data->cmds);
}

void    ft_free_tokens(t_token **tokens)
{
    t_token *curr;
    t_token *next;

    curr = *tokens;
    while (curr)
    {
        next = curr->next;
        if (curr->content)
            free(curr->content);
        free(curr);
        curr = next;
    }
    *tokens = NULL;
}

void    ft_free_cmds(t_cmd **cmds)
{
    t_cmd   *curr;
    t_cmd   *next;
    int     i;

    curr = *cmds;
    while (curr)
    {
        next = curr->next;
        if (curr->args)
        {
            i = 0;
            while (curr->args[i])
                free(curr->args[i++]);
            free(curr->args);
        }
        if (curr->redirects)
            ft_free_redirects(curr->redirects);

        if (curr->cmd_path)
            free(curr->cmd_path);

        free(curr);
        curr = next;
    }
    *cmds = NULL;
}

void    ft_free_redirects(t_redirect *redir)
{
    t_redirect *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->file)
            free(redir->file);
        free(redir);
        redir = tmp;
    }
}


