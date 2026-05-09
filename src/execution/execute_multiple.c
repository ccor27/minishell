/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristian <cristian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2026/05/08 12:00:00 by cristian          #+#    #+#             */
/*   Updated: 2026/05/08 12:00:00 by cristian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_child_process(t_cmd *cmd, t_data *data, int *fd, int prev_fd);

void	ft_wait_pipeline(t_data *data, pid_t last_pid);

/**
 * @brief Handles the execution of multiple piped commands.
 * 
 * This function loops through the linked list of commands, creating a pipe
 * and forking a child process for each command. It manages file descriptors
 * to ensure that the output of one command is directed to the input of the 
 * next one.
 * 
 * @param data The main data structure containing command information.
 */
void	ft_execute_multiple(t_data *data)
{
	t_cmd	*tmp;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	ft_exec_signals();
	tmp = data->cmds;
	prev_fd = -1;
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
			ft_handle_child_process(tmp, data, fd, prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (tmp->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		tmp = tmp->next;
	}
	ft_wait_pipeline(data, pid);
	ft_init_signals();
	ft_cleanup_heredocs(data->cmds);
}

/**
 * @brief Waits for all child processes in the pipeline.
 * 
 * Captures the exit status of the last command and stores it in data->exit_code.
 * 
 * @param data The main data structure.
 * @param last_pid The PID of the last command in the pipeline.
 */
void	ft_wait_pipeline(t_data *data, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					printf("\n");
				else if (WTERMSIG(status) == SIGQUIT)
					printf("Quit: 3\n");
				data->exit_code = 128 + WTERMSIG(status);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
}

/**
 * @brief Handles the child process logic in a pipeline.
 * 
 * Sets up the input/output routing using dup2, applies redirections,
 * and executes the command (either built-in or external).
 * 
 * @param cmd The command to execute.
 * @param data The main data structure.
 * @param fd The current pipe file descriptors.
 * @param prev_fd The read end of the previous pipe.
 */
void	ft_handle_child_process(t_cmd *cmd, t_data *data, int *fd, int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (ft_apply_redirections(cmd) != 0)
		exit(1);
	if (cmd->args[0] && cmd->args[0][0])
	{
		if (ft_execute_builtin(cmd, data))
			exit(data->exit_code);
		ft_execute_external(cmd, data);
	}
	exit(data->exit_code);
}
