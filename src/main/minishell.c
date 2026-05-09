#include "minishell.h"

/**
 * @brief Reads input from stdin.
 * Handles interactive mode with readline and non-interactive mode with gnl.
 * Strips the trailing newline from gnl output to avoid parsing errors.
 *
 * @return char* The input string or NULL on EOF.
 */
static char	*ft_get_input(void)
{
	char	*input;
	int		len;

	if (isatty(STDIN_FILENO))
		return (readline("minishell$> "));
	input = get_next_line(STDIN_FILENO, 0);
	if (!input)
		return (NULL);
	len = ft_strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	return (input);
}

/**
 * Function to initialize  the data struct
 * and the first node of the linked-list
 */
void	ft_init_data_struct(t_data *data, char **envp)
{
	data->env = ft_copy_env(envp);
	data->cmds = NULL;
	data->tokens = NULL;
	data->exit_code = 0;
}

/**
 * @brief Main loop for processing user input.
 *
 * @param data Main data structure.
 */
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

/**
 * @brief Entry point for the minishell.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variables.
 * @return int Final exit code.
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_init_signals();
	if (isatty(STDIN_FILENO))
		print_header();
	ft_init_data_struct(&data, envp);
	ft_main_loop(&data);
	ft_free_env(&data.env);
	if (!isatty(STDIN_FILENO))
		get_next_line(STDIN_FILENO, 1);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	return (data.exit_code);
}
