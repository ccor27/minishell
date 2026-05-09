# SYSTEM INSTRUCTIONS: STRICT 42 NORMINETTE
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables).
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function. No inline initialization.
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.

# YOUR TASK: EXACT BUG FIXES
You must apply the following 2 exact code replacements to fix the double free memory crash and the redirection bypass bug. Do not alter the architecture. Output ONLY the 2 updated `.c` files.

### 1. Fix Export Double Free (`src/built_in/export.c`)
The `ft_set_env` function already frees or consumes `key`. Calling `free(key)` indiscriminately afterwards causes a double free.
Replace `ft_export_arg` with this exact implementation:
```c
void	ft_export_arg(char *arg, t_data *data)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	value = NULL;
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		key = ft_substr(arg, 0, equal_pos - arg);
	else
		key = ft_strdup(arg);
	if (!ft_is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		data->exit_code = 1;
		if (key)
			free(key);
		if (value)
			free(value);
		return ;
	}
	if (equal_pos)
	{
		value = ft_strdup(equal_pos + 1);
		ft_set_env(data, key, value);
		free(value);
	}
	else
	{
		if (!ft_get_env_node(data->env, key))
			ft_env_add_back(&data->env, ft_new_env_node(ft_strdup(key), NULL));
		free(key);
	}
}
```

### 2. Fix Empty Command Redirections (`src/process/executor.c`)
The early return guard for empty strings bypasses `ft_apply_redirections`, causing `> outfile` to fail.
Replace `ft_executor_single` with this exact implementation that applies redirections first:
```c
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
		if (!data->cmds->args || !data->cmds->args[0] || data->cmds->args[0][0] == '\0')
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
```

Output ONLY the full code for `export.c` and `executor.c`.
