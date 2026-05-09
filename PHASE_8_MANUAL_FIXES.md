# SYSTEM INSTRUCTIONS: STRICT 42 NORMINETTE
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables).
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function. No inline initialization.
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.

# YOUR TASK: EXACT BUG FIXES
You must apply the following 4 exact code replacements to fix compilation errors and edge cases. Do not alter the architecture. Output ONLY the 4 updated `.c` files.

### 1. Fix Compilation & Newline (`src/main/minishell.c`)
Replace `ft_get_input` and `ft_main_loop` with this exact logic to remove the invalid `0` from `get_next_line` and fix the prompt echo:
```c
static char	*ft_get_input(void)
{
	char	*input;
	int		len;

	if (isatty(STDIN_FILENO))
		return (readline("minishell$> "));
	input = get_next_line(STDIN_FILENO);
	if (!input)
		return (NULL);
	len = ft_strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	return (input);
}

static void	ft_main_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = ft_get_input();
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			ft_parse_and_store(input, data);
			ft_parse_cmd(data->tokens, data);
			ft_here_doc(data);
			ft_expanders(data);
			ft_executor(data);
			ft_cleanup_heredocs(data->cmds);
			ft_free_data(data);
		}
		free(input);
	}
}
```
### 2. Fix Exit Signs (src/built_in/exit.c)
Replace the ft_is_numeric function completely with this version to handle signs:

```C
int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
```
### 3. Fix Export Double Free (src/built_in/export.c)
Add this validation function to the top of the file:

```C
int	ft_is_valid_identifier(char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
```
Inside ft_export_arg, immediately after extracting the variable key, add this guard to print the error and return ; safely without freeing things twice:

```C
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
```
### 4. Fix Empty String Crash (src/process/executor.c)
Inject this exact guard clause at the very beginning of ft_executor_single to prevent crashes when $EMPTY is passed:

```C
	if (!data->cmds || !data->cmds->args || !data->cmds->args[0]
		|| data->cmds->args[0][0] == '\0')
	{
		data->exit_code = 0;
		return ;
	}
```
Output only the full code for minishell.c, exit.c, export.c, and executor.c.
