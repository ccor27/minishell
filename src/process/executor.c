#include "minishell.h"

/**
 * Function to execute the correct builtin command
 */
int ft_execute_builtin(t_cmd *cmd, t_data *data)
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
        return (0); // Not a built-in
    return (1); // It was a built-in and executed successfully
}

/**
 * Fuction to execute n commands
 */
void	ft_execute_multiple(t_data *data)
{
	(void)data;
	// multiple commands
    // 1. Loop through all data->cmds
    // 2. For each command: Create a pipe() and fork() a child
    // 3. Inside Child: Wire the pipes, apply redirections, and execute!
    // 4. Inside Parent: Close the pipe ends.
    // 5. After the loop: Parent waits for all children (waitpid)
}

/**
 * Function to execute just a single command
 */
void	ft_executor_single(t_data *data)
{
	int original_stdin;
    int original_stdout;

    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);

    if (ft_apply_redirections(data->cmds) == 0)
    {
        if (ft_execute_builtin(data->cmds, data) == 0)
            ft_execute_external(data->cmds, data);
    }
    // 4. Restore the original STDIN and STDOUT using dup2()
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    // Always close the duplicated FDs when you are done with them!
    close(original_stdin);
    close(original_stdout);
}

/**
 * Function to execute commands
 */
void	ft_executor(t_data *data)
{
    if (!data->cmds)
        return;
    //validate if there are more than one command
    if (data->cmds->next == NULL)
		ft_executor_single(data);
    else
		ft_execute_multiple(data);
}
