#include "minishell.h"

void	ft_here_doc_store_data(t_cmd *node,int tmp_file,char *tmp_file_name)
{
    char    *line;

    while(1)
    {
        line = readline("> ");
        if (!line)
        {
            printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", node->redir_in);
            break;
        }
        if (ft_strncmp(line, node->redir_in, ft_strlen(node->redir_in) + 1) == 0)
        {
            free(line);
            break;
        }
        write(tmp_file, line, ft_strlen(line));
        write(tmp_file, "\n", 1);
        free(line);
    }
    close(tmp_file);
    free(node->redir_in);
    node->redir_in = ft_strdup(tmp_file_name);
}

//TODO: fix  the number of lines
void    ft_here_doc(t_data *data)
{
    t_cmd   *tmp;
    int     tmp_file;
    int     i;
    char    *tmp_file_name;
    char    *num_str;

    tmp = data->cmds;
    i = 0;
    while(tmp)
    {
        if(tmp->is_heredoc == 1)
        {
            num_str = ft_itoa(i);
            tmp_file_name = ft_strjoin(".tmp_heredoc_", num_str);
            free(num_str);
            tmp_file = open(tmp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (tmp_file < 0)
            {
                free(tmp_file_name);
                return; //TODO: think how handle errors here
            }
            ft_here_doc_store_data(tmp, tmp_file, tmp_file_name);
            free(tmp_file_name);
            i++;
        }
        tmp = tmp->next;
    }
}
