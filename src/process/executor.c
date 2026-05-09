#include "minishell.h"

/**
 * Function to execute the correct builtin command
 */
int	ft_execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ft_echo(cmd, data);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd, data);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(cmd, data);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		ft_unset(cmd, data);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd, data);
	else
		return (0);
	return (1);
}

/**
 * Function to execute just a single command
 */
void	ft_executor_single(t_data *data)
{
	int		orig_in;
	int		orig_out;
	pid_t	pid;
	int		status;

	if (!data->cmds)
		return ;
	orig_in = dup(STDIN_FILENO);
	orig_out = dup(STDOUT_FILENO);
	if (ft_apply_redirections(data->cmds) == 0)
	{
		if (!data->cmds->args || !data->cmds->args[0]
			|| data->cmds->args[0][0] == '\0')
			data->exit_code = 0;
		else if (ft_execute_builtin(data->cmds, data) == 0)
		{
			ft_exec_signals();
			pid = fork();
			if (pid == 0)
				ft_execute_external(data->cmds, data);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
			ft_init_signals();
		}
	}
	else
		data->exit_code = 1;
	dup2(orig_in, STDIN_FILENO);
	dup2(orig_out, STDOUT_FILENO);
	close(orig_in);
	close(orig_out);
}

/**
 * Function to execute commands
 */
void	ft_executor(t_data *data)
{
	if (!data->cmds)
		return ;
	if (data->cmds->next == NULL)
		ft_executor_single(data);
	else
		ft_execute_multiple(data);
}
