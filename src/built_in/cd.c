#include "minishell.h"

/**
 * Updates PWD and OLDPWD environment variables after a successful chdir.
 */
void	ft_update_pwd(t_data *data)
{
	char	cwd[4096];
	t_env	*pwd_node;
	char	*old_pwd;

	pwd_node = ft_get_env_node(data->env, "PWD");
	if (pwd_node)
		old_pwd = ft_strdup(pwd_node->value);
	else
		old_pwd = ft_strdup("");
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_set_env(data, ft_strdup("OLDPWD"), old_pwd);
		ft_set_env(data, ft_strdup("PWD"), cwd);
	}
	free(old_pwd);
}

/**
 * Implementation of the cd built-in.
 * Only handles absolute or relative paths.
 */
void	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->args[1])
	{
		ft_putendl_fd("minishell: cd: relative or absolute path only", 2);
		data->exit_code = 1;
		return ;
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		data->exit_code = 1;
		return ;
	}
	path = cmd->args[1];
	if (chdir(path) == 0)
	{
		ft_update_pwd(data);
		data->exit_code = 0;
	}
	else
	{
		perror("minishell: cd");
		data->exit_code = 1;
	}
}
