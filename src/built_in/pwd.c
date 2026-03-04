#include "minishell.h"

//TODO: test this
int	ft_pwd(t_cmd *cmd)
{
	char    *cwd;

    (void)cmd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("minishell: pwd");
        return (1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
