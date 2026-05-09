#include "minishell.h"

/**
 * Helper function to safely fetch and split the PATH variable.
 * Returns a char** array of folders, or NULL if PATH is missing.
 */
char	**get_path_array(t_data *data)
{
	t_env	*path_node;

	path_node = ft_get_env_node(data->env, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	return (ft_split(path_node->value, ':'));
}

/**
 * Searches for the correct executable path.
 * If the user typed an absolute path (e.g., /bin/ls), it returns it.
 * Otherwise, it tests every folder in the PATH variable.
 */
char	*ft_get_cmd_path(char *cmd, t_data *data)
{
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_path_array(data);
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
		{
			ft_free_array(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

/**
 * Executes the external command.
 * If called within a child process, it doesn't need to fork again.
 */
void	ft_execute_external(t_cmd *cmd, t_data *data)
{
	char	**envp;

	if (access(cmd->args[0], F_OK) == 0 && ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->args[0]);
			exit(126);
		}
	}
	cmd->cmd_path = ft_get_cmd_path(cmd->args[0], data);
	if (!cmd->cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(127);
	}
	envp = ft_env_to_array(data->env);
	execve(cmd->cmd_path, cmd->args, envp);
	perror("minishell");
	exit(126);
}
