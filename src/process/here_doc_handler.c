#include "minishell.h"


void    ft_here_doc_store_data(t_redirect *redir, int tmp_file, char *tmp_file_name)
{
    char    *line;
    while(1)
    {
        line = readline("> ");
        if (!line)
        {
            printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", redir->file);
            break;
        }
        if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
        {
            free(line);
            break;
        }
        write(tmp_file, line, ft_strlen(line));
        write(tmp_file, "\n", 1);
        free(line);
    }
    close(tmp_file);
    free(redir->file); // Free the old delimiter
    redir->file = ft_strdup(tmp_file_name); // Replace with the .tmp file!
}

void    ft_here_doc_aux(int *i, t_cmd *tmp)
{
    t_redirect  *redir; // We need a pointer to loop the redirs
    char        *num_str;
    char        *tmp_file_name;
    int         tmp_file;

    redir = tmp->redirects; // Start at the head of the redirections list
    while (redir) // Loop through all redirections for this command
    {
       if(redir->type == HERE_DOC)
      {
        num_str = ft_itoa(*i);
        tmp_file_name = ft_strjoin(".tmp_heredoc_", num_str);
        free(num_str);
        tmp_file = open(tmp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (tmp_file < 0)
        {
           free(tmp_file_name);
           return;
        }
       // Pass the redir node!
       ft_here_doc_store_data(redir, tmp_file, tmp_file_name);
       free(tmp_file_name);
       (*i)++;
      }
      redir = redir->next; // Move to the next redirection
    }
}

void    ft_here_doc(t_data *data)
{
    t_cmd       *tmp;
    int         i;

    tmp = data->cmds;
    i = 0;
    while(tmp)
    {
        ft_here_doc_aux(&i,tmp);
        tmp = tmp->next; // Move to the next command
    }
    //TODO: delete the temporal files
}
